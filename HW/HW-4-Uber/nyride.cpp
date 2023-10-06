#include <list>
#include <iostream>
#include <fstream>
#include <regex>
#include <cmath>
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


bool isPhoneNumber(const string &num) {
	// regex pattern: follows xxx-xxx-xxxx digits only format
	regex pattern("^\\d{3}-\\d{3}-\\d{4}$");
    return regex_match(num, pattern);
}


bool searchDriverByNumber(const string &num, list<Driver*>* &driverList, Driver* &dFound) {
	// what to return here
	// dont return anything
	// call function on the iter that is found!!!
	list<Driver*>::const_iterator it;
	for (it = driverList->begin(); it!=driverList->end(); it++) {
		if ((*it)->getPhoneNumber() == num) {
			break;
		}
	}
	if (it!=driverList->end()) {
		cout << "Found the driver: " << (*it)->getFirstName() << endl;
		return true;
	} else {
		cout << "Not in drivers\n";
		return false;
	}
	
}


bool searchRiderByNumber(const string &num, list<Rider*>* &riderList, Rider* &rFound) {
	// loop over elements. break once found
	list<Rider*>::iterator it;
	for (it = riderList->begin(); it!=riderList->end(); it++) {
		if ((*it)->getPhoneNumber() == num) {
			break;
		}
	}
	if (it!=riderList->end()) {
		cout << "Found the rider: " << (*it)->getFirstName() << endl;
		return true;
	} else {
		cout << "Not in riders\n";
		return false;
	}
	// do stuff with it now
}


void writeDriverFound(ofstream &out, Rider* &rider, Driver* &driver) {
	// Ride requested for user Rebecca, looking for an Economy vehicle.
 	// Pick Up Location: Williamsburg, Drop Off Location: Statue_of_Liberty.
	// We have found the closest driver Elena(4.7) for you.
	// Elena is now 7.9 miles away from you.

	// get distance

	out << "Ride requested for user " << rider->getFirstName() << ", looking for an " << rider->getVehiclePreference() << " vehicle.\n";
	out << "Pick Up Location: " << rider->getPickupLocationName() << ", Drop off Location: " << rider->getDropoffLocationName() << ".\n";
	out << "We have found the closest driver " << endl;
}


void writeDrivers(ofstream &out, list<Driver*>* &driverList) {

	
	return;
}


int main(int argc, char* argv[]) {
	// command:
	// valgrind -s --leak-check=full ./run.exe drivers.txt riders.txt output0.txt output1.txt output2.txt 737-781-9718 request
	// g++ -g nyride.cpp Driver.cpp Rider.cpp -Wall -Wextra -o run.exe
	if (argc>8 || argc<8) {
		cerr << "ERROR: WRONG INPUT SIZE" << endl;
		exit(1);
	}

	// allocate lists onto heap containing riders and drivers also on the heap
	list<Rider*> *riders = new list<Rider*>;
	list<Driver*> *drivers = new list<Driver*>;

	ifstream driverInFile(argv[1]);
	ifstream riderInFile(argv[2]);
	ofstream output0(argv[3]);
	ofstream output1(argv[4]);
	ofstream output2(argv[5]);
	string inNum = argv[6];
	string requestType = argv[7];

	// checks if input and output files are able to be opened
	if (!driverInFile.good()) {
	    std::cerr << "Can't open " << argv[1] << " to read.\n";
	    exit(1);
	} if (!riderInFile.good()) {
    	std::cerr << "Can't open " << argv[2] << " to write.\n";
    	exit(1);
    } if (!output0.good()) {
    	std::cerr << "Can't open " << argv[3] << " to write.\n";
    	exit(1);
    } if (!output1.good()) {
    	std::cerr << "Can't open " << argv[4] << " to write.\n";
    	exit(1);
    } if (!output2.good()) {
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

    Rider* riderFound;
    Driver* driverFound;

    bool found = false;
    if (isPhoneNumber(inNum)) {
    	// is request?
    	cout << "valid" << endl;
    	if (requestType=="request") {
    		// assuming all phone numbers are unique
    		// would need diff logic if drivers and riders had crossover
    		cout << "request\n";
    		cout << "checking rider:\n";

    		bool foundRider = searchRiderByNumber(inNum, riders, riderFound);
    		if (!foundRider) {
    			cout << "checking driver:\n";
    			bool foundDriver = searchDriverByNumber(inNum, drivers, driverFound);
    		}
    		// check the driver and rider lists
    		// searchDriverByNumber(inNum, drivers);
    	} else if (requestType=="cancel") {
    		// check from drivers
    		searchDriverByNumber(inNum, drivers, driverFound);
    	} else {
    		cerr << "ERROR: Invaid ride type - " << requestType << endl;
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