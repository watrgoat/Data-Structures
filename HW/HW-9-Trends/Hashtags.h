// hashtag queue:
// organize by hashtag popularity, then views
// each video can have multiple hashtags
// so we need to point to same video under that hashtage using pair

class Hashtags {
private:
    std::unordered_map<std::string, std::priority_queue<Video, std::vector<Video>, Compare>> hashtagToVideosMap;

public:
    void addVideo(const Video& video) {
        for (const std::string& hashtag : video.getHashtags()) {
            hashtagToVideosMap[hashtag].push(video);
        }
    }

    // Method to get top videos for a hashtag, etc.
};
