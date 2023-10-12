#ifndef NODE_H
#define NODE_H

#include <string>

class Node {
public:
    // Constructor
    Node(std::string name, int age, std::string gender, std::string phoneNumber, std::string profession,
         std::string school, double currentLatitude, double currentLongitude, 
         bool isPremiumUser, int minAge, int maxAge, int maxDistance, 
         std::string interestedGender, std::string likedUsers);

    // Member functions
    void insertAfter(Node* newNode);
    void removeNode();

    // Accessors and mutators
    std::string getName() const;
    int getAge() const;
    std::string getGender() const;
    std::string getPhoneNumber() const;
    std::string getProfession() const;
    std::string getSchool() const;
    double getCurrentLatitude() const;
    double getCurrentLongitude() const;
    bool getIsPremiumUser() const;
    int getMinAge() const;
    int getMaxAge() const;
    int getMaxDistance() const;
    std::string getInterestedGender() const;
    std::string getLikedUsers() const;

    void setLikedUsers(std::string likedUsers);

    Node* getNext() const;
    Node* getPrev() const;

private:
    // User data
    std::string name;
    int age;
    std::string gender;
    std::string phoneNumber;
    std::string profession;
    std::string school;
    double currentLatitude;
    double currentLongitude;
    bool isPremiumUser;
    int minAge;
    int maxAge;
    int maxDistance;
    std::string interestedGender;
    std::string likedUsers;

    // Pointers for doubly linked list
    Node* next;
    Node* prev;
};

#endif // NODE_H