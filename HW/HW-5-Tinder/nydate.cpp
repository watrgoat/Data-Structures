#include <iostream>
#include <fstream>
#include <string>
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
    string name, age, gender, phoneNumber, profession, school, currentLatitude, currentLongitude, isPremiumUser, minAge, maxAge, maxDistance, interestedGender, likedUsers;
    while (file >> name >> age >> gender >> phoneNumber >> profession >> school >> currentLatitude >> currentLongitude >> isPremiumUser >> minAge >> maxAge >> maxDistance >> interestedGender >> likedUsers) {
        Node* node = new Node();
        node->phoneNumber = phoneNumber;
        node->next = nullptr;
        node->prev = tail;
        tail->next = node;
        tail = node;
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

int main(int argc, char* argv[]) {

    Node* head = new Node();
    head->data = "Hello";
    Node* tail = new Node();
    tail->data = "World";
    head->next = tail;
    head->prev = nullptr;
    tail->next = nullptr;
    tail->prev = head;

    cout << *head << ", " << *head->next << endl;

    delete head;
    delete tail;

    return 0;
}