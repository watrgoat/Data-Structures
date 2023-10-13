#ifndef NODE_H
#define NODE_H

class Node {
public:
    // Default constructor
    Node();

    // Constructor
    Node(std::string name, int age, std::string gender, std::string phoneNumber, std::string profession,
         std::string school, double currentLatitude, double currentLongitude, 
         bool isPremiumUser, int minAge, int maxAge, int maxDistance, 
         std::string interestedGender, std::string likedUsers);

    // Copy constructor
    Node(const Node& other);

    // Member functions
    void insertAfter(Node* newNode);
    void removeNode();

    // Getters
    std::string getName() const { return this->name; };
    int getAge() const { return this->age; };
    std::string getGender() const { return this->gender; };
    std::string getPhoneNumber() const { return this->phoneNumber; };
    std::string getProfession() const { return this->profession; };
    std::string getSchool() const { return this->school; };
    double getCurrentLatitude() const { return this->currentLatitude; };
    double getCurrentLongitude() const { return this->currentLongitude; };
    bool getIsPremiumUser() const { return this->isPremiumUser; };
    int getMinAge() const { return this->minAge; };
    int getMaxAge() const { return this->maxAge; };
    int getMaxDistance() const { return this->maxDistance; };
    std::string getInterestedGender() const { return this->interestedGender; };
    std::string getLikedUsers() const { return this->likedUsers; };

    // Setters
    void setLikedUsers(std::string likedUsers) { this->likedUsers = likedUsers; };

    // Getters for doubly linked list
    Node* getNext() const { return this->next; };
    Node* getPrev() const { return this->prev; };

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

std::ostream& operator<<(std::ostream& os, const Node& node);

#endif // NODE_H