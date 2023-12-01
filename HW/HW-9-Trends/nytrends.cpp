#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <utility>
#include <regex>
#include "Sounds.h"
// #include "Hashtags.h"

class compareSoundViews {
public:
    bool operator()(const std::pair<int, std::string>& a, const std::pair<int, std::string>& b) {
        return a.first < b.first; // Sort by views in descending order
    }
};

unsigned long extractPlayCount(const std::string& json) {
    std::regex playCountRegex("\"playCount\":\\s*(\\d+),");
    std::smatch matches;

    if (std::regex_search(json, matches, playCountRegex) && matches.size() > 1) {
        try {
            return std::stoul(matches[1].str());
        } catch (const std::exception& e) {
            std::cerr << "Error converting play count: " << e.what() << std::endl;
        }
    }

    return 0;
}

std::string extractString(const std::string& json, const std::string& key) {
    std::regex pattern("\"" + key + "\":\\s*\"([^\"]*)\"");
    std::smatch matches;
    if (std::regex_search(json, matches, pattern) && matches.size() > 1) {
        return matches[1].str();
    }
    return "";
}

void ingestSounds(std::ifstream &file, 
                  std::priority_queue<std::pair<unsigned long, std::string>, std::vector<std::pair<unsigned long, std::string>>, compareSoundViews>& soundID_views, 
                  std::unordered_map<std::string, std::pair<std::string, std::string>>& soundID_data, 
                  Sounds &sounds) {
    std::unordered_map<std::string, unsigned long> viewCounts;
    std::string line;
    while (std::getline(file, line)) {
        // extract data
        std::string cover_url = extractString(line, "coverUrl");
        std::string web_video_url = extractString(line, "webVideoUrl");
        unsigned long views = extractPlayCount(line);
        std::string song_id = extractString(line, "musicId");

        // update viewCounts map
        viewCounts[song_id] += views;

        // update soundID_data if not already in map
        if (soundID_data.find(song_id) == soundID_data.end()) {
            std::string song_name = extractString(line, "musicName");
            std::string artist_name = extractString(line, "musicAuthor");
            soundID_data[song_id] = std::make_pair(song_name, artist_name);
        }

        std::unordered_set<std::string> hashtags;
        std::string text = extractString(line, "text");
        std::string hashtag = "";

        // find every substring that starts with # and ends with a space, add to hashtags
        for (char ch : text) {
            if (ch == '#') {
                hashtag = "#";
            } else if (ch == ' ') {
                if (!hashtag.empty()) {
                    hashtags.insert(hashtag);
                }
                hashtag.clear();
            } else {
                hashtag += ch;
            }
        }
        if (!hashtag.empty() && hashtag[0] == '#') {
            hashtags.insert(hashtag);
        }

        sounds.addVideo(cover_url, web_video_url, hashtags, views, song_id);
    }

    for (const std::pair<std::string, unsigned long> item : viewCounts) {
        soundID_views.push(std::make_pair(item.second, item.first));
    }
}

void getTop10TrendingSounds(std::priority_queue<std::pair<unsigned long, std::string>, std::vector<std::pair<unsigned long, std::string>>, compareSoundViews> soundID_views,
                            std::vector<std::string>& music_ids) {
    while (!soundID_views.empty() && music_ids.size() < 10) {
        music_ids.push_back(soundID_views.top().second);
        soundID_views.pop();
    }
}

void printTopSongs(std::ofstream& file, std::unordered_map<std::string, std::pair<std::string, std::string>>& soundID_data,
                   std::unordered_map<std::string, std::vector<Video> >& top_videos_for_ids,
                   std::priority_queue<std::pair<unsigned long, std::string>, std::vector<std::pair<unsigned long, std::string>>, compareSoundViews>& soundID_views,
                   std::vector<std::string>& music_ids) {
    file << "trending sounds:" << std::endl;
    file << std::endl;
    std::string line = "========================";

    for (const std::string& music_id : music_ids) {
        file << line << std::endl;
        file << soundID_data[music_id].first << std::endl;
        // get total views for music id from soundID_views

        // top of top_videos_for_ids is most viewed video
        file << soundID_views.top().first << " views" << std::endl;
        soundID_views.pop();

        file << soundID_data[music_id].second << std::endl;
        file << "music id: " << music_id << std::endl;

        file << std::endl;
        for (const Video& video : top_videos_for_ids[music_id]) {
            file << "cover url: " << video.getCoverUrl() << std::endl;
            file << "web video url: " << video.getWebVideoUrl() << std::endl;
        }
        file << line << std::endl;
    }
}

// input cla should be: nytrends <input_file> <output_file> <hashtag|sound>
int main(int argc, char* argv[]) {
    // check if input is valid
    if (argc != 4) {
        std::cerr << "Invalid input" << std::endl;
        return 1;
    }

    // check if input is hashtag or sound
    std::string input_type = argv[3];
    if (input_type != "hashtag" && input_type != "sound") {
        std::cerr << "Invalid input type" << std::endl;
        return 1;
    }

    // check if input file is valid
    std::ifstream input_file(argv[1]);
    if (!input_file) {
        std::cerr << "Invalid input file" << std::endl;
        return 1;
    }

    // check if output file is valid
    std::ofstream output_file(argv[2]);
    if (!output_file) {
        std::cerr << "Invalid output file" << std::endl;
        return 1;
    }

    // ingest input file
    if (input_type == "hashtag") {
        // ingestHashtags(input_file);
    } else {
        Sounds sounds;
        std::priority_queue<std::pair<unsigned long, std::string>, std::vector<std::pair<unsigned long, std::string>>, compareSoundViews> soundID_views;
        std::unordered_map<std::string, std::pair<std::string, std::string>> soundID_data;
        
        ingestSounds(input_file, soundID_views, soundID_data, sounds);


        // get top 10 trending sounds and 3 videos for each sound
        std::vector<std::string> music_ids;
        getTop10TrendingSounds(soundID_views, music_ids);


        std::unordered_map<std::string, std::vector<Video> > top_videos_for_ids = sounds.getTopVideosForMusicIds(std::unordered_set<std::string>(music_ids.begin(), music_ids.end()));
        
        // print top 10 trending sounds and 3 videos for each sound
        printTopSongs(output_file, soundID_data, top_videos_for_ids, soundID_views, music_ids);
    }

    return 0;
}