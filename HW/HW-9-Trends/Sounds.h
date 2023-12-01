// Sounds.h
#ifndef SOUNDS_H
#define SOUNDS_H

#include <string>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include "Video.h"

/*
print the top 10 trending sounds, and then for each sound, print 3 videos 
which use this sound. If a sound is used in 100 videos, select the 3 (out of these 100) 
most viewed videos. Print the most viewed video first, and then print the next most 
viewed video, and then the third most viewed video.

Definition of the top 10 trending sounds: this should be the based on the total 
view count of the videos which use this sound. If there is a tie, break the tie 
by the music id - the one with the smaller music id will be displayed first. (Note: 
use the comparison operators (<, <=, >, >=) directly on these two std::string objects 
to decide which one is smaller.)*/

class Sounds {
private:
    // video comparison functor
    class VideoCompare {
    public:
        bool operator()(const Video& a, const Video& b) const;
    };

    std::priority_queue<Video, std::vector<Video>, VideoCompare> soundQueue;

public:
    // def constructor
    Sounds() {}

    int size() const { return soundQueue.size(); }

    void addVideo(const std::string& coverUrl,
                  const std::string& webVideoUrl,
                  const std::unordered_set<std::string>& videoHashtags,
                  int videoViews, const std::string& soundId) { 
        soundQueue.emplace(coverUrl, webVideoUrl, videoHashtags, videoViews, soundId);
    }

    // Method to get top 10 trending sounds and 3 videos for each sound
    std::unordered_map<std::string, std::vector<Video> > getTopVideosForMusicIds(const std::unordered_set<std::string>& musicIds);
};

#endif // SOUNDS_H
