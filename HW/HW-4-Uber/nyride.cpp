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

void readDriverFile(ifstream &file, list<Drivers> &inDrivers) {
	string word;

	int i = 0;
	// loop over driver text
	// assign values to temp Driver obj then adds to list
	while (file >> word) {
		Driver curr;
		switch (i) {
		case 0:
			curr.setFirstName(word);
			break;
		case 1:
			curr.setLastName(word);
			break;
		case 2:
			curr.setGender(word);
			break;
		case 3:
			curr.setAge(stoi(word));
			break;
		case 4:
			curr.setPhoneNumber(word);
			break;
		case 5:
			curr.setRating(word);
			break;
		case 6:
			curr.setCurrentLatitude(stod(word));
			break;
		case 7:
			curr.setCurrentLongitude(stod(word));
			break;
		case 8:
			curr.setVehicleType(word);
			break;
		case 9:
			curr.setCurrentState(word);
			break;
		case 10:
			curr.setRiderFirstName(word);
			break;
		case 11:
			curr.setRiderLastName(word);
			break;
		case 12:
			curr.setRiderPhoneNumber(word);
			break;
		}
		i++;
		if (i>12) {
			i=0;
			inDrivers.push_back(curr);
		}
	}
}

void readRiderFile(ifstream &file, list<Rider> &inRiders) {
	string word;

	int i = 0;
	while (file >> word) {
		Rider curr;
		switch (i) {
		case 0:
			curr.setFirstName(word);
			break;
		case 1:
			curr.setLastName(word);
			break;
		case 2:
			curr.setGender(word);
			break;
		case 3:
			curr.setAge(stoi(word));
			break;
		case 4:
			curr.setPhoneNumber(word);
			break;
		case 5:
			curr.setRating(word);
			break;
		case 6:
			curr.setPickupLocationName(word);
			break;
		case 7:
			curr.setPickupLatitude(stod(word));
			break;
		case 8:
			curr.setPickupLongitude(stod(word));
			break;
		case 9:
			curr.setDropoffLocationName(word);
			break;
		case 10:
			curr.setDropoffLatitude(stod(word));
			break;
		case 11:
			curr.setDropoffLongitude(stod(word));
			break;
		case 12:
			curr.setVehiclePreference(word);
			break;
		case 13:
			curr.setCurrentState(word);
			break;
		case 14:
			curr.setDriverFirstName(word);
			break;
		case 15:
			curr.setDriverLastName(word);
			break;
		case 16:
			curr.setDriverPhoneNumber(word);
			break;
		}
		i++;
		if (i>16) {
			i=0;
			inRiders.push_back(curr);
		}
	}
}

bool checkPhoneNumber(const string &num) {
	if (num.length()==10 && ) {

	} else {
		return false;
	}
}

int main(int argc, char* argv[]) {
	// do stuff
	if (argc>8 || argc<8) {
		cerr << "ERROR: WRONG INPUT SIZE" << endl;
		exit(1);
	}

	list<Rider> riders;
	list<Driver> drivers;



	return 0;
}