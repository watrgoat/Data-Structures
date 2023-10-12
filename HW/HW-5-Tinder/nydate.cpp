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
    head = new Node(name, stoi(age), gender, phoneNumber, profession, school, stod(currentLatitude), stod(currentLongitude), (isPremiumUser == "true"), stoi(minAge), stoi(maxAge), stoi(maxDistance), interestedGender, likedUsers);
    while (file >> name >> age >> gender >> phoneNumber >> profession >> school >> currentLatitude >> currentLongitude >> isPremiumUser >> minAge >> maxAge >> maxDistance >> interestedGender >> likedUsers) {
        cout << name << age << gender << phoneNumber << profession << school << currentLatitude << currentLongitude << isPremiumUser << minAge << maxAge << maxDistance << interestedGender << likedUsers << endl;
        if (head==nullptr) {
            // assigne head values
            Node* head = new Node(name, stoi(age), gender, phoneNumber, profession, school, stod(currentLatitude), stod(currentLongitude), (isPremiumUser == "true"), stoi(minAge), stoi(maxAge), stoi(maxDistance), interestedGender, likedUsers);

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

int main(int argc, char* argv[]) {
    // check if the number of command-line arguments is correct
    if (argc < 5 || argc > 6) {
        cout << "Usage: ./nydate <input_file> <output_file> <phone_number> <command> <optional_phone_number>" << endl;
        return 1;
    }

    Node* head = nullptr;
    Node* tail = nullptr;

    // open the input file
    ifstream inFile(argv[1]);
    if (!inFile) {
        cout << "Error: cannot open file '" << argv[1] << "'." << endl;
        return 1;
    }

    // ingest the data from the input file
    ingest(inFile, head, tail);

    // close the input file
    inFile.close();

    // check if the command is valid
    string command = string(argv[4]);
    if (command != "profile" && command != "match" && command != "like" && command != "unmatch") {
        cout << "Error: unknown command '" << argv[4] << "'." << endl;
        return 1;
    }

    // do main function calls here
    // ...

    // open the output file
    ofstream outFile(argv[2]);
    if (!outFile) {
        cout << "Error: cannot open file '" << argv[2] << "'." << endl;
        return 1;
    }

    // write to output file
    // ...

    return 0;
}