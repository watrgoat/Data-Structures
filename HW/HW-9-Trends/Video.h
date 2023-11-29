
class Video {
private:
    std::string cover_url;
    std::string web_video_url;
    std::unordered_set<std::string> hashtags;
    unsigned long views;
    std::string sound;

public:
    // Constructor
    Video(std::string coverUrl, std::string webVideoUrl, std::unordered_set<std::string> videoHashtags, int videoViews, std::string soundId) {
        cover_url = coverUrl;
        web_video_url = webVideoUrl;
        hashtags = videoHashtags;
        views = videoViews;
        sound = soundId;
    }

    // Getters
    std::string getCoverUrl() const {
        return cover_url;
    }

    std::string getWebVideoUrl() const {
        return web_video_url;
    }

    std::unordered_set<std::string> getHashtags() const {
        return hashtags;
    }

    int getViews() const {
        return views;
    }

    std::string getSoundId() const {
        return sound;
    }
};
