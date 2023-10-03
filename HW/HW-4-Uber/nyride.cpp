#include <list>
#include <iostream>
#include <fstream>
#include <regex>
#include "Rider.h"
#include "Driver.h"

using namespace std;

// main uber functions
// what is it asking for?
// large file outline?
// what order should this be done
// efficiency?
// how to use std::list in this?

void readDriverFile(ifstream &file, list<Driver*>* &inDrivers) {
	string word;

	int i = 0;
	// loop over driver text
	// assign values to temp Driver obj then adds to list
	while (file >> word) {
		Driver* curr = new Driver;
		switch (i) {
		case 0:
			(*curr).setFirstName(word);
			break;
		case 1:
			(*curr).setLastName(word);
			break;
		case 2:
			(*curr).setGender(word);
			break;
		case 3:
			(*curr).setAge(stoi(word));
			break;
		case 4:
			(*curr).setPhoneNumber(word);
			break;
		case 5:
			(*curr).setRating(word);
			break;
		case 6:
			(*curr).setCurrentLatitude(stod(word));
			break;
		case 7:
			(*curr).setCurrentLongitude(stod(word));
			break;
		case 8:
			(*curr).setVehicleType(word);
			break;
		case 9:
			(*curr).setCurrentState(word);
			break;
		case 10:
			(*curr).setRiderFirstName(word);
			break;
		case 11:
			(*curr).setRiderLastName(word);
			break;
		case 12:
			(*curr).setRiderPhoneNumber(word);
			break;
		}
		i++;
		if (i>12) {
			i=0;
			inDrivers->push_back(curr);
		}
	}
}

void readRiderFile(ifstream &file, list<Rider*>* &inRiders) {
	string word;

	int i = 0;
	while (file >> word) {
		Rider* curr = new Rider;
		switch (i) {
		case 0:
			(*curr).setFirstName(word);
			break;
		case 1:
			(*curr).setLastName(word);
			break;
		case 2:
			(*curr).setGender(word);
			break;
		case 3:
			(*curr).setAge(stoi(word));
			break;
		case 4:
			(*curr).setPhoneNumber(word);
			break;
		case 5:
			(*curr).setRating(word);
			break;
		case 6:
			(*curr).setPickupLocationName(word);
			break;
		case 7:
			(*curr).setPickupLatitude(stod(word));
			break;
		case 8:
			(*curr).setPickupLongitude(stod(word));
			break;
		case 9:
			(*curr).setDropoffLocationName(word);
			break;
		case 10:
			(*curr).setDropoffLatitude(stod(word));
			break;
		case 11:
			(*curr).setDropoffLongitude(stod(word));
			break;
		case 12:
			(*curr).setVehiclePreference(word);
			break;
		case 13:
			(*curr).setCurrentState(word);
			break;
		case 14:
			(*curr).setDriverFirstName(word);
			break;
		case 15:
			(*curr).setDriverLastName(word);
			break;
		case 16:
			(*curr).setDriverPhoneNumber(word);
			break;
		}
		i++;
		if (i>16) {
			i=0;
			inRiders->push_back(curr);
		}
	}
}

bool isPhoneNumber(const string &num) {
	regex pattern("^\\d{3}-\\d{3}-\\d{4}$");
    return regex_match(num, pattern);
}

int main(int argc, char* argv[]) {
	// do stuff
	if (argc>8 || argc<8) {
		cerr << "ERROR: WRONG INPUT SIZE" << endl;
		exit(1);
	}

	// allocate lists onto heap containing riders and drivers also on the heap
	list<Rider*> *riders = new list<Rider*>();
	list<Driver*> *drivers = new list<Driver*>();

	/*ifstream riderInFile(argv[1]);
	ifstream driverInFile(argv[2]);
	ofstream output1(argv[3]);
	ofstream output2(argv[4]);
	ofstream output3(argv[5]);*/

	// Clean up: makes sure to delete all allocated memory from the list
	
	for (list<Rider*>::iterator it = riders->begin(); it != riders->end(); it++) {
		delete *it;
	}
	delete riders;
	for (list<Driver*>::iterator it = drivers->begin(); it != drivers->end(); it++) {
		delete *it;
	}
	delete drivers;

	return 0;
}