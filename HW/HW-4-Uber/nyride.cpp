#include <list>
#include <iostream>
#include <fstream>
#include "Rider.h"
#include "Driver.h"

using namespace std;

// main uber functions
// what is it asking for?
// large file outline?
// what order should this be done
// efficiency?
// how to use std::list in this?
void readRiderFile(ifstream &file, list<Rider> &inRiders) {
	string word;

	int i = 0;
	while (file >> word) {
		Rider curr;
		switch (i) {
		case 0: curr.setFirstName(string(word));
		case 1: curr.setLastName(string(word));
		case 2: curr.setGender(string(word));
		case 3: curr.setAge(int(word));
		case 4: curr.setPhoneNumber(string(word));
		case 5: curr.setRating(string(word));
		case 6: curr.setPickupLocationName(string(word));
		case 7: curr.setPickupLatitude(double(word));
		case 8: curr.setPickupLongitude(double(word));
		case 9: curr.setDropoffLocationName(string(word));
		case 10: curr.setDropoffLatitude(double(word));
		case 11: curr.setDropoffLongitude(double(word));
		case 12: curr.setVehiclePreference(string(word));
		case 13: curr.setCurrentState(string(word));
		case 14: curr.setDriverFirstName(string(word));
		case 15: curr.setDriverLastName(string(word));
		case 16: curr.setDriverPhoneNumber(string(word));
		}
		i++;
		inRiders.push_back(curr);
	}
}


int main(int argc, char* argv[]) {
	// do stuff
	if (argc > 8 || argc < 8) {
		cerr << "ERROR: WONG INPUT SIZE" << endl;
		exit(1);
	}

	list<Rider> riders;
	list<Driver> drivers;

	return 0;
}