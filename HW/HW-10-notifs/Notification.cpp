#include "Notification.h"

UserSettings::UserSettings(const UserSettings& other) {
    likes = other.likes;
    tags = other.tags;
    comments = other.comments;
    newFollowers = other.newFollowers;
    messageRequests = other.messageRequests;
}

std::ostream& operator<<(std::ostream& os, const Notification& notification) {
    os << notification.getText();
    return os;
}