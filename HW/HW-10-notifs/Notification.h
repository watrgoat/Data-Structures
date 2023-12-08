#ifndef NOTIFICATION_H
#define NOTIFICATION_H

#include <string>
#include <iostream>

class UserSettings {
public:
    // default constructor
    UserSettings() : likes(true), tags(true), comments(true), newFollowers(true), messageRequests(true) {}

    UserSettings(bool likes, bool tags, bool comments, bool newFollowers, bool messageRequests)
        : likes(likes), tags(tags), comments(comments), newFollowers(newFollowers), messageRequests(messageRequests) {}

    // copy constructor
    UserSettings(const UserSettings& other);

    // copy assignment operator
    UserSettings& operator=(const UserSettings& other) {
        likes = other.likes;
        tags = other.tags;
        comments = other.comments;
        newFollowers = other.newFollowers;
        messageRequests = other.messageRequests;
        return *this;
    }

    bool getLikes() const { return likes; }
    bool getTags() const { return tags; }
    bool getComments() const { return comments; }
    bool getNewFollowers() const { return newFollowers; }
    bool getMessageRequests() const { return messageRequests; }

protected:
    bool likes;
    bool tags;
    bool comments;
    bool newFollowers;
    bool messageRequests;
};

class Notification {
public:
    Notification() {}
    virtual ~Notification() {}
    
    virtual std::string getText() const { return text; };

protected:
    std::string text;
};

class Like : public Notification {
public:
    Like(const std::string& user) {
        text = user + " liked your post.";
    }

    std::string getType() const { return "Like"; }
};

class Tag : public Notification {
public:
    Tag(const std::string& user){
        text = user + " tagged you in a post.";
    }

    std::string getType() const { return "Tag"; }
};

class Comment : public Notification {
public:
    Comment(const std::string& user){
        text = user + " commented on your post.";
    }

    std::string getType() const { return "Comment"; }
};

class Follow : public Notification {
public:
    Follow(const std::string& user){
        text = user + " started following you.";
    }

    std::string getType() const { return "Follow"; }
};

class Message : public Notification {
public:
    Message(const std::string& user){
        text = user + " wants to send you a message.";
    }

    std::string getType() const { return "Message"; }
};

std::ostream& operator<<(std::ostream& os, const Notification& notification);

#endif
