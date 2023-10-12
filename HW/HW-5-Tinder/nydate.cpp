#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <cmath>
#include "Node.h"

using namespace std;

// assumes all input phone numbers are valid and have an acct

/*
User's name
User's age
User's gender
User's phone number
User's profession: A user can choose not to disclose their profession, and if so, this field will be Undisclosed.
User's school: A user can choose not to disclose his/her school, and if so, this field will be Undisclosed.
User's current latitude
User's current longitude
Is Premium User or not: this field will be either true or false.
User's preference on age: minimum age
User's preference on age: maximum age
User's preference on max distance (in miles). Note: this is an integer number.
User's preference on interested gender: this field can be one of these three: Male, Female, Both.
Users whom this user liked 
*/


void ingest(ifstream &file, Node* &head, Node* &tail) {
    string name, age, gender, phoneNumber, profession, school;
    string currentLatitude, currentLongitude, isPremiumUser, minAge, maxAge;
    string maxDistance, interestedGender, likedUsers;

    while (file >> name >> age >> gender >> phoneNumber >> profession 
           >> school >> currentLatitude >> currentLongitude >> isPremiumUser 
           >> minAge >> maxAge >> maxDistance >> interestedGender >> likedUsers) {
        
        // remove underscores from profession and school
        replace(profession.begin(), profession.end(), '_', ' ');
        replace(school.begin(), school.end(), '_', ' ');

        Node* curr = new Node(
            name,
            stoi(age),
            gender,
            phoneNumber,
            profession,
            school,
            stod(currentLatitude),
            stod(currentLongitude),
            (isPremiumUser == "true"),
            stoi(minAge),
            stoi(maxAge),
            stoi(maxDistance),
            interestedGender,
            likedUsers);

        if (head == nullptr) {
            head = curr;
            tail = head;
        } else {
            tail->insertAfter(curr);
            tail = curr;
        }
    }
}

// calculate the distance between two coordinates using Haversine formula
double calculateDistance(double lat1, double lon1, double lat2, double lon2) {
    const double radiusOfEarth = 6371.0; // Earth's radius in kilometers

    // convert latitude and longitude from degrees to radians
    lat1 *= M_PI / 180.0;
    lon1 *= M_PI / 180.0;
    lat2 *= M_PI / 180.0;
    lon2 *= M_PI / 180.0;

    // Haversine formula
    double dLat = lat2 - lat1;
    double dLon = lon2 - lon1;
    double a = sin(dLat / 2.0) * sin(dLat / 2.0) + cos(lat1) * cos(lat2) * sin(dLon / 2.0) * sin(dLon / 2.0);
    double c = 2.0 * atan2(sqrt(a), sqrt(1.0 - a));
    // distance in kilometers
    double distanceKM = radiusOfEarth * c;
    // convert it to distance in miles
    double distanceMiles = distanceKM * 0.621371;

    return distanceMiles;
}

bool isWithinDistance(Node* user1, Node* user2) {
    // calculate distance between two users
    double distance = calculateDistance(user1->getCurrentLatitude(), user1->getCurrentLongitude(), 
                                        user2->getCurrentLatitude(), user2->getCurrentLongitude());

    // returns true if both users are within each others max distance
    return distance <= user1->getMaxDistance();
}

void deallocate(Node* head) {
    Node* curr = head;
    while (curr) {
        Node* next = curr->getNext();
        delete curr;
        curr = next;
    }
}

// print out the profiles of all the users in the list starting from input node
void printProfiles(ostream &out, Node* &head) {
    Node* curr = head;
    while (curr) {
       out << *curr << endl;
       curr = curr->getNext();
    }
}

// insert node into already sorted list by phone number
void sortedInsert(Node* &sortedHead, Node* &newNode) {
    // check if new node should be inserted before head
    if (sortedHead->getPhoneNumber() >= newNode->getPhoneNumber()) {
        // insert head after newNode and set newNode as head
        newNode->insertAfter(sortedHead);
        sortedHead = newNode;
    } else {
        // find the node that the new node should be inserted after
        Node* current = sortedHead;
        // while not at the end and the next nodes phone number is less than the new node's phone number
        while (current->getNext() != nullptr && current->getNext()->getPhoneNumber() < newNode->getPhoneNumber()) {
            current = current->getNext();
        }
        current->insertAfter(newNode);
    }
}

Node* searchUsers(Node* head, Node* tail, const string &num) {
    Node* forward = head;
    Node* backward = tail;

    // search from both ends of the list until pointers meet in the middle
    while (forward && backward && forward != backward && (forward->getNext() != backward)) {
        if (forward->getPhoneNumber() == num) {
            return forward;
        }

        if (backward->getPhoneNumber() == num) {
            return backward;
        }

        forward = forward->getNext();
        backward = backward->getPrev();
    }

    // check for pointers meeting in the middle
    if (forward && forward->getPhoneNumber() == num) {
        return forward;
    }
    if (backward && backward->getPhoneNumber() == num) {
        return backward;
    }

    return nullptr;
}

void profileView(ostream &out, Node* &head, Node* &tail, const string &phoneNumber) {
    // find the user
    Node* currUser = searchUsers(head, tail, phoneNumber);

    // check if the user was found
    if (!currUser) {
        cout << "Error: user '" << phoneNumber << "' not found." << endl;
        return;
    }

    // temp list to store matched users
    Node* tempHead = nullptr;
    Node* tempTail = nullptr;

    // search for users that match the current users preferences
    Node* potentialMatch = head;
    while (potentialMatch) {
        if (potentialMatch != currUser && 
        potentialMatch->getAge() >= currUser->getMinAge() && 
        potentialMatch->getAge() <= currUser->getMaxAge() &&
        (potentialMatch->getGender() == currUser->getInterestedGender() || 
        currUser->getInterestedGender() == "Both") &&
        isWithinDistance(currUser, potentialMatch)) {

            // Create a new node with the same data
            Node* newNode = new Node(*potentialMatch);

            // if first match set up temp list head
            if (!tempHead) {
                tempHead = newNode;
                tempTail = tempHead;
            } else {
                // insert node in current order
                tempTail->insertAfter(newNode);
                tempTail = newNode;
            }
        }
        potentialMatch = potentialMatch->getNext();
    }

    // check if there were any matches
    if (!tempHead) {
        out << "There are no users matching with your preference at this moment.\n" << endl;
    } else {
        // output matched profiles
        printProfiles(out, tempHead);
    }
    
    // clean up temp list
    deallocate(tempHead);
}

void matchViewer(ostream &out, Node* &head, Node* &tail, const string &phoneNumber) {
    // find the user
    Node* currUser = searchUsers(head, tail, phoneNumber);

    // check if the user was found
    if (currUser == nullptr) {
        cout << "Error: user '" << phoneNumber << "' not found." << endl;
        return;
    }

    // temp list to store matched users
    Node* tempHead = nullptr;
    Node* tempTail = nullptr;

    // search for users that contain number in likedUsers
    Node* potentialMatch = head;
    // loop through list of users adding matches to temp list in phone number order similar to insertion sort
    
    while (potentialMatch) {
        // if the user is not the current user and the current user is in the potential
        // match's liked list and the potential match is in the current user's liked list
        if (potentialMatch != currUser && 
        potentialMatch->getLikedUsers().find(phoneNumber) != string::npos &&
        currUser->getLikedUsers().find(potentialMatch->getPhoneNumber()) != string::npos) {
            // create a copy of the now confirmed match
            Node* newNode = new Node(*potentialMatch);

            // if first match set up temp list head
            if (!tempHead) {
                tempHead = newNode;
                tempTail = tempHead;
            } else {
                // insert node in sorted order
                sortedInsert(tempHead, newNode);

                // reset tempTail to the end of the list
                if (tempTail->getNext() != nullptr) {
                    tempTail = tempTail->getNext();
                } // otherwise tempTail is already at the end of the list
            }
        }
        potentialMatch = potentialMatch->getNext();
    }

    // check if there were any matches
    if (!tempHead) {
        out << "You do not have any matches at this moment.\n" << endl;
    } else {
        // output matched profiles
        printProfiles(out, tempHead);
    }

    // clean up temp list
    deallocate(tempHead);
}

void likeViewer(ostream &out, Node* &head, Node* &tail, const string &phoneNumber) {
    // find the user
    Node* currUser = searchUsers(head, tail, phoneNumber);

    // check if the user was found
    if (currUser == nullptr) {
        cout << "Error: user '" << phoneNumber << "' not found." << endl;
        return;
    }

    // check if the user is a premium user
    if (!currUser->getIsPremiumUser()) {
        out << "Only premium users can view who liked you.\n" << endl;
        return;
    }

    // temp list to store matched users
    Node* tempHead = nullptr;
    Node* tempTail = nullptr;

    // search for users that contain number in likedUsers
    Node* potentialMatch = head;

    // loop through list of users adding matches to temp list
    while (potentialMatch) {
        // if the user is not the current user and the current user is in the potential match's liked list
        if (potentialMatch != currUser && 
        potentialMatch->getLikedUsers().find(phoneNumber) != string::npos) {
            // create a copy of the now confirmed match
            Node* newNode = new Node(*potentialMatch);

            // if first match set up temp list head
            if (!tempHead) {
                tempHead = newNode;
                tempTail = tempHead;
            } else {
                // insert node 
                tempTail->insertAfter(newNode);
                tempTail = newNode;
            }
        }
        potentialMatch = potentialMatch->getNext();
    }

    // check if there were any matches
    if (!tempHead) {
        out << "You have not received any likes so far.\n" << endl;
    } else {
        // output matched profiles
        printProfiles(out, tempHead);
    }

    // clean up temp list
    deallocate(tempHead);
}

int main(int argc, char* argv[]) {
    // check if the number of command-line arguments is correct
    if (argc < 5 || argc > 6) {
        cout << "Usage: ./nydate <input_file> <output_file> <phone_number> <command> <optional_phone_number>" << endl;
        return 1;
    }

    // open the input file
    ifstream inFile(argv[1]);
    if (!inFile) {
        cout << "Error: cannot open file '" << argv[1] << "'." << endl;
        return 1;
    }

    Node* head = nullptr;
    Node* tail = nullptr;

    // ingest the data from the input file
    ingest(inFile, head, tail);

    // close the input file
    inFile.close();

    // open the output file
    ofstream outFile(argv[2]);
    if (!outFile) {
        cout << "Error: cannot open file '" << argv[2] << "'." << endl;
        return 1;
    }

    string command = string(argv[4]);
    string inNumber = string(argv[3]);
    // check command type
    if (command == "profile") {
        // show all users profiles that match the users preferences
        profileView(outFile, head, tail, inNumber);
    } else if (command == "match") {
        // show matches (phone number in both users liked list)
        matchViewer(outFile, head, tail, inNumber);
    } else if (command == "like") {
        // show users that liked this user
        likeViewer(outFile, head, tail, inNumber);
    } else if (command == "unmatch") {
        // ...
    } else {
        // bad input command
        cout << "Error: unknown command '" << argv[4] << "'." << endl;
        deallocate(head);
        return 1;
    }

    // close the output file
    outFile.close();

    // deallocate memory
    deallocate(head);

    return 0;
}