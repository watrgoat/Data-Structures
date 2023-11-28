// Practice using std::priority_queue.
// Practice using std::unordered_map, std::unordered_set.
// Practice using C++ exceptions.

// need: cover_url, web_video_url, hashtags, views, sound

// seperate sound queue and hashtag queue

// hashtag queue:
// organize by hashtag popularity, then views

// sound queue:
// organize by sound popularity (total views, then music id), then views

// each video can have multiple hashtags
// so we need to point to same video under that hashtage using pair and pointer to video
// each video can have 1 sound
// so we need to point to same video under that sound using pair and pointer to video

// use unordered_map to store video
// video: cover_url, web_video_url, hashtags, views, sound

// use unordered_set to store hashtag
// use priority_queue to store sound and hashtag

// use try catch to catch exception for invalid input

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include "Video.h"
#include "Sounds.h"
#include "Hashtags.h"

// input cla should be: nytrends <input_file> <output_file> <hashtag|sound>
int main(int argc, char* argv[]) {
    // check if input is valid
    if (argc != 4) {
        std::cout << "Invalid input" << std::endl;
        return 1;
    }

    // check if input file is valid
    std::ifstream input_file(argv[1]);
    if (!input_file) {
        std::cout << "Invalid input file" << std::endl;
        return 1;
    }

    // check if output file is valid
    std::ofstream output_file(argv[2]);
    if (!output_file) {
        std::cout << "Invalid output file" << std::endl;
        return 1;
    }

    // check if input is hashtag or sound
    std::string input_type = argv[3];
    if (input_type != "hashtag" && input_type != "sound") {
        std::cout << "Invalid input type" << std::endl;
        return 1;
    }

    // create unordered_map to store video
    std::unordered_map<std::string, Video*> video_map;

    // create unordered_set to store hashtag
    std::unordered_set<std::string> hashtag_set;

    // create priority_queue to store sound and hashtag
    std::priority_queue<Sound*, std::vector<Sound*>, SoundCompare> sound_queue;
    std::priority_queue<Hashtag*, std::vector<Hashtag*>, HashtagCompare> hashtag_queue;

    // read input file
    std::string line;
    while (std::getline(input_file, line)) {
        // split line by comma
        std::vector<std::string> line_vector = split(line, ',');

        // check if line is valid
        if (line_vector.size() != 5) {
            std::cout << "Invalid line" << std::endl;
            return 1;
        }

        // check if views is valid
        if (!is_number(line_vector[3])) {
            std::cout << "Invalid views" << std::endl;
            return 1;
        }

        // check if music id is valid
        if (!is_number(line_vector[4])) {
            std::cout << "Invalid music id" << std::endl;
            return 1;
        }

        // create video
        Video* video = new Video(line_vector[0], line_vector[1], std::stoi(line_vector[3]), std::stoi(line
}