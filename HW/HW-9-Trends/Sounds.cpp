// Sounds.cpp
#include "Sounds.h"

// functor comparison operator
bool Sounds::VideoCompare::operator()(const Video& a, const Video& b) const {
    if (a.getSoundId() == b.getSoundId()) {
        return a.getViews() < b.getViews();
    }
    return a.getSoundId() < b.getSoundId();
}

std::unordered_map<std::string, std::vector<Video>> Sounds::getTopVideosForMusicIds(const std::unordered_set<std::string>& musicIds) {
    std::unordered_map<std::string, std::vector<Video>> topVideosForIds;
    std::priority_queue<Video, std::vector<Video>, VideoCompare> tempQueue = soundQueue; // Create a temporary copy

    while (!tempQueue.empty()) {
        Video video = tempQueue.top();
        tempQueue.pop();

        if (musicIds.find(video.getSoundId()) != musicIds.end()) {
            std::vector<Video>& videosForId = topVideosForIds[video.getSoundId()];
            if (videosForId.size() < 3) {
                videosForId.push_back(video);
            }
        }
    }

    return topVideosForIds;
}
