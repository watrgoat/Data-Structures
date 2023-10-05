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
	Driver curr;
	while (file >> word) {
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
			Driver* d = new Driver(curr);
			inDrivers->push_back(d);
			Driver curr;
		}
	}
}

void readRiderFile(ifstream &file, list<Rider*>* &inRiders) {
	string word;

	int i = 0;
	Rider curr;
	while (file >> word) {
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
			Rider* r = new Rider(curr);
			inRiders->push_back(r);
			Rider curr;
		}
	}
}

bool isPhoneNumber(const string &num) {
	// regex pattern: follows xxx-xxx-xxxx digits only format
	regex pattern("^\\d{3}-\\d{3}-\\d{4}$");
    return regex_match(num, pattern);
}

void searchDriverByNumber(const string &num, const list<Driver*>* &drivers) {
	// what to return here
	// dont return anything
	// call function on the iter that is found!!!
	list<Driver*>::const_iterator it;
	for (it = drivers->begin(); it!=drivers->end(); it++) {
		if ((*it)->getPhoneNumber() == num) {
			break;
		}
	}
	cout << "Found the driver: " << (*it)->getFirstName() << endl;
}

void searchRiderByNumber(const string &num, const list<Rider*>* &riders) {
	// loop over elements. break once found
	list<Rider*>::const_iterator it;
	for (it = riders->begin(); it!=riders->end(); it++) {
		if ((*it)->getPhoneNumber() == num) {
			break;
		}
	}
	cout << "Found the rider: " << (*it)->getFirstName() << endl;
	// do stuff with it now
}

int main(int argc, char* argv[]) {

	if (argc>8 || argc<8) {
		cerr << "ERROR: WRONG INPUT SIZE" << endl;
		exit(1);
	}

	// allocate lists onto heap containing riders and drivers also on the heap
	list<Rider*> *riders = new list<Rider*>;
	list<Driver*> *drivers = new list<Driver*>;

	ifstream driverInFile(argv[1]);
	ifstream riderInFile(argv[2]);
	ofstream output1(argv[3]);
	ofstream output2(argv[4]);
	ofstream output3(argv[5]);
	string inNum = argv[6];
	string requestType = argv[7];

	// checks if input and output files are able to be opened
	if (!driverInFile.good()) {
	    std::cerr << "Can't open " << argv[1] << " to read.\n";
	    exit(1);
	} if (!riderInFile.good()) {
    	std::cerr << "Can't open " << argv[2] << " to write.\n";
    	exit(1);
    } if (!output1.good()) {
    	std::cerr << "Can't open " << argv[3] << " to write.\n";
    	exit(1);
    } if (!output2.good()) {
    	std::cerr << "Can't open " << argv[4] << " to write.\n";
    	exit(1);
    } if (!output3.good()) {
    	std::cerr << "Can't open " << argv[5] << " to write.\n";
    	exit(1);
    }

    readRiderFile(riderInFile, riders);
    readDriverFile(driverInFile, drivers);

    // request
    // find number acct
    // not found: bad input
    // found: find driver, change data, output

    // cancel
    // find in rider, driver
    // not found: bad input
    // found: change account info

    if (isPhoneNumber(inNum)) {
    	// is request?
    	if (requestType=="request") {
    		// assuming all phone numbers are unique
    		// would need diff logic if drivers and riders had crossover

    		// check the driver and rider lists
    		searchDriverByNumber()
    	} else if (requestType=="cancel") {
    		// check from drivers
    	} else {
    		cerr << "ERROR: Invaid ride type - " << argv[7] << endl;
    		exit(1)
    	}
    } else {
    	// bad input
    	cout << "Phone number is invalid.\n";
    }


	// drivers can be: 
	// Available (waiting for a request)
	// On the way to a pickup location (request accepted)
	// During a trip

	// riders can be:
	// Ready to request
	// Driver on the way (to pickup)
	// During a trip

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