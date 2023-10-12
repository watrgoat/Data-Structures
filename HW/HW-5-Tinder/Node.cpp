#include <fstream>
#include "Node.h"

// Default constructor
Node::Node(): name(""), age(0), gender(""), phoneNumber(""), profession(""), school(""), currentLatitude(0.0),
            currentLongitude(0.0), isPremiumUser(false), minAge(0), maxAge(0), maxDistance(0), interestedGender(""),
            likedUsers(""), next(nullptr), prev(nullptr) {}

// Constructor
Node::Node(std::string name, int age, std::string gender, std::string phoneNumber, std::string profession,
        std::string school, double currentLatitude, double currentLongitude, 
        bool isPremiumUser, int minAge, int maxAge, int maxDistance, 
        std::string interestedGender, std::string likedUsers) 
        : name(name), age(age), gender(gender), phoneNumber(phoneNumber), profession(profession), 
        school(school), currentLatitude(currentLatitude), currentLongitude(currentLongitude), 
        isPremiumUser(isPremiumUser), minAge(minAge), maxAge(maxAge), maxDistance(maxDistance), 
        interestedGender(interestedGender), likedUsers(likedUsers), next(nullptr), prev(nullptr) {}

void Node::insertAfter(Node* newNode) {
    newNode->next = this->next;
    newNode->prev = this;
    if (this->next) {
        this->next->prev = newNode;
    }
    this->next = newNode;
}

// removed node must be deleted if in heap
void Node::removeNode() {
    // if there exists a node behind this node set its next to this node's next
    if (this->prev) {
        this->prev->next = this->next;
    }
    // if there exists a node in front of this node set its prev to this node's prev
    if (this->next) {
        this->next->prev = this->prev;
    }
    this->prev = nullptr;
    this->next = nullptr;
}

std::ostream& operator<<(std::ostream& out, const Node& node) {
    out << node.getName() << " " << node.getAge() << " " << node.getGender() << " " << node.getPhoneNumber() << " " 
       << node.getProfession() << " " << node.getSchool() << " " << node.getCurrentLatitude() << " " 
       << node.getCurrentLongitude() << " " << node.getIsPremiumUser() << " " << node.getMinAge() << " " 
       << node.getMaxAge() << " " << node.getMaxDistance() << " " << node.getInterestedGender() << " " 
       << node.getLikedUsers();
    return out;
}