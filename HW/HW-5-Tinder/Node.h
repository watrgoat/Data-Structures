#ifndef NODE_H
#define NODE_H

#include <iostream>
#include <fstream>
#include <string>

// string name, age, gender, phoneNumber, profession
// school, currentLatitude, currentLongitude, isPremiumUser, minAge, maxAge, maxDistance, interestedGender, likedUsers;
class Node {
public:
    // std::string name;
    // int age;
    std::string phoneNumber;
    // std::string profession;
    // std::string school;
    // double currentLatitude;
    // double currentLongitude;
    // bool isPremiumUser;
    // int minAge;
    // int maxAge;
    // int maxDistance;
    // std::string interestedGender;
    // std::string likedUsers;

    Node* next;
    Node* prev;
};

std::ostream& operator<<(std::ostream& out, const Node& node) {
    out << node.phoneNumber;
    return out;
}

#endif // NODE_H