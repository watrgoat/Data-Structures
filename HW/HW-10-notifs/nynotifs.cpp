#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_set>
#include <queue>
#include <stack>
#include <regex>
#include "Notification.h"

bool extractBool(const std::string& json, const std::string& key) {
    std::string searchKey = "\"" + key + "\": \"";
    size_t startPos = json.find(searchKey);
    if (startPos != std::string::npos) {
        startPos += searchKey.length();
        if (json[startPos] == 't') {
            return true;
        } else if (json[startPos] == 'f') {
            return false;
        }
    }
    throw std::runtime_error("JSON key not found");
}

std::string extractFirstID(const std::string& json) {
    std::string idKey = "\"id\":\"";
    size_t startPos = json.find(idKey);
    if (startPos != std::string::npos) {
        startPos += idKey.length();
        size_t endPos = json.find("\"", startPos);
        if (endPos != std::string::npos) {
            return json.substr(startPos, endPos - startPos);
        }
    }
    throw std::runtime_error("JSON key not found");
}

std::string extractString(const std::string& json, const std::string& key) {
    std::regex pattern("\"" + key + "\":\\s*\"([^\"]*)\"");
    std::smatch matches;
    if (std::regex_search(json, matches, pattern) && matches.size() > 1) {
        return matches[1].str();
    }
    return "";
}

UserSettings readUserSettings(std::ifstream &file, const std::string &username, bool &pauseAll) {
    std::string line;
    while (std::getline(file, line)) {
        if (line.find(username) != std::string::npos) {
            pauseAll = extractBool(line, "pauseAll");
            bool likes = extractBool(line, "likes");
            bool tags = extractBool(line, "tags");
            bool comments = extractBool(line, "comments");
            bool newFollowers = extractBool(line, "newFollowers");
            bool messageRequests = extractBool(line, "messageRequests");
            return UserSettings(likes, tags, comments, newFollowers, messageRequests);
        }
    }
    throw std::runtime_error("User not found");
}

void readPosts(std::ifstream &file, std::unordered_set<std::string> &posts, const std::string &username) {
    std::string line;
    while (std::getline(file, line)) {
        // check if owner of post is the user
        if (extractString(line, "ownerUsername") == username) {
            posts.insert(extractString(line, "id"));
        }
    }
}

void readNotifications(std::ifstream &file, const std::unordered_set<std::string> &posts, const UserSettings &settings, const std::string &username, std::stack<Notification> &notifications) {
    std::string word1, word2, word3;

    while (file >> word1 >> word2 >> word3 && notifications.size() < 100) {

        if (word2 == "likes" || word2 == "comments") {
            if (posts.find(word3) != posts.end()) {
                if (word2 == "likes" && settings.getLikes()) {
                    notifications.push(Like(word1));

                } else if (word2 == "comments" && settings.getComments()) {
                    notifications.push(Comment(word1));

                }
            }
        } else if (word2 == "tags" && settings.getTags()) {
            if (word3 == username) {
                notifications.push(Tag(word1));

            }
        } else if (word2 == "follows" && settings.getNewFollowers()) {
            if (word3 == username) {
                notifications.push(Follow(word1));

            }
        } else if (word2 == "messageRequests" && settings.getMessageRequests()) {
            if (word3 == username) {
                notifications.push(Message(word1));

            }
        }
    }
}

int main(int argc, char* argv[]) {
    if (argc != 6) {
        std::cerr << "Invalid input" << std::endl;
        return 1;
    }
    
    std::string username = argv[5];
    std::ifstream users(argv[2]);
    if (!users.is_open()) {
        std::cerr << "Could not open users file" << std::endl;
        return 1;
    }

    bool pauseAll = false;
    UserSettings settings;

    try {
        settings = readUserSettings(users, username, pauseAll);
    } catch (std::runtime_error& e) {
        users.close();
        std::cerr << e.what() << std::endl;
        return 1;
    }

    users.close();
    std::ofstream outFile(argv[4]);
    if (!outFile.is_open()) {
        std::cerr << "Could not open output file" << std::endl;
        return 1;
    }

    if (pauseAll) {
        outFile.close();
        return 1;
    }

    std::ifstream posts(argv[1]);
    if (!posts.is_open()) {
        std::cerr << "Could not open posts file" << std::endl;
        return 1;
    }

    std::unordered_set<std::string> post_ids;

    try {
        readPosts(posts, post_ids, username);
    } catch (std::runtime_error& e) {
        posts.close();
        outFile.close();
        std::cerr << e.what() << std::endl;
        return 1;
    }

    posts.close();

    std::ifstream events(argv[3]);
    if (!events.is_open()) {
        std::cerr << "Could not open events file" << std::endl;
        return 1;
    }

    std::stack<Notification> notifications;

    try {
        readNotifications(events, post_ids, settings, username, notifications);
    } catch (std::runtime_error& e) {
        events.close();
        outFile.close();
        std::cerr << e.what() << std::endl;
        return 1;
    }

    events.close();

    while (!notifications.empty()) {
        outFile << notifications.top() << std::endl;
        notifications.pop();
    }

    outFile.close();

    return 0;
}