// sound queue:
// organize by sound popularity (total views, then music id), then views

#include <functional>
#include <queue>
#include <unordered_map>
#include <vector>


class Sounds {
private:
    // Define the type for the comparison function
    using CompareFunction = std::function<bool(const Video&, const Video&)>;

    // Define the comparison function
    CompareFunction compare = [](const Video& a, const Video& b) {
        if (a.getViews() == b.getViews()) {
            return a.getSoundId() < b.getSoundId(); // Break ties by sound ID
        }
        return a.getViews() < b.getViews(); // Order by viewCount in descending order
    };

    // Use CompareFunction in the priority_queue
    std::unordered_map<std::string, std::priority_queue<Video, std::vector<Video>, CompareFunction> > soundToVideosMap;

public:
    Sounds() : soundToVideosMap() {}

    void addVideo(const Video& video) { soundToVideosMap[video.getSoundId()].push(video); }

    // Additional methods...
};