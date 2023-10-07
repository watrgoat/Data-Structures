#include <list>
#include <iostream>
#include <fstream>
#include <regex>
#include <cmath>
#include <iomanip>
#include <limits>
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
		// break statements are required to get no errors
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


void searchDriverByNumber(const string &num, list<Driver*>* &driverList, Driver* &dFound) {
	// what to return here
	// dont return anything
	// call function on the iter that is found!!!
	list<Driver*>::const_iterator it;
	for (it = driverList->begin(); it!=driverList->end(); it++) {
		if ((*it)->getPhoneNumber() == num) {
			dFound = *it;
			break;
		}
	}
	return;
}

Rider* searchRiderByNumber(const string &num, const list<Rider*>& riderList) {
    auto frontIt = riderList.begin();
    auto backIt = riderList.end(); // Note: end() is one past the last element.
    --backIt; // So we start from the actual last element.

    while (frontIt != riderList.end() && backIt != riderList.begin() && frontIt != backIt) {
        if ((*frontIt)->getPhoneNumber() == num) {
            return *frontIt;
        }
        if ((*backIt)->getPhoneNumber() == num) {
            return *backIt;
        }
        
        ++frontIt;
        if (frontIt != backIt) { // Ensure they haven't met yet.
            --backIt;
        }
    }

    // Handle the scenario where there's an odd number of elements, 
    // and frontIt and backIt point to the same element.
    if (frontIt == backIt && (*frontIt)->getPhoneNumber() == num) {
        return *frontIt;
    }

    return nullptr;
}


Rider* searchRiderByNumber(const string &num, const list<Rider*>& riderList) {
	list<Rider*>::iterator it;
    for (it = riderList.begin(); it != riderList.end(); ++it) {
        if ((*it)->getPhoneNumber() == num) {
            return *it;
        }
    }
    return NULL;
}


void findDriverForRider(Rider* &inRider, list<Driver*>* driverList, Driver* &outDriver) {

	list<Driver*>::iterator it;
	double minDist = std::numeric_limits<double>::max();
	double currDist;

	// iterates over list finding the minimum distanced driver to the current requesting rider
	for (it = driverList->begin(); it!=driverList->end(); it++) {
		// if the driver is available
		if ((*it)->getCurrentState() == "Available") {
			// check if driver fits preferred vehicle type
			if ((*it)->getVehicleType() != inRider->getVehiclePreference()) {
				// check the distance to rider
				currDist = calculateDistance(inRider->getPickupLatitude(), inRider->getPickupLongitude(), (*it)->getCurrentLatitude(), (*it)->getCurrentLongitude());
				if (currDist < minDist) {
					// edit the mins
					minDist = currDist;
					outDriver = *it;
				}
			}
		}
	}

	return;
}


void riderStatus(ofstream &out, Rider* &r) {
	if (r->getCurrentState() == "Driver_on_the_way") {
		out << "You have already requested a ride and your driver is on the way to the pickup location." << endl;
	} else {
		out << "You can not request a ride at this moment as you are already on a trip." << endl;
	}
	return;
}

void writeRequestNoDriver(ofstream &out, Rider* &rider) {

	out << "Ride requested for user " << rider->getFirstName() << ", looking for an " << rider->getVehiclePreference() << " vehicle.\n";
	out << "Pick Up Location: " << rider->getPickupLocationName() << ", Drop off Location: " << rider->getDropoffLocationName() << ".\n";
	out << "Sorry we can not find a driver for you at this moment.\n";

	return;
}

void writeRequest(ofstream &out, Rider* &rider, Driver* &driver) {
	// Ride requested for user Rebecca, looking for an Economy vehicle.
 	// Pick Up Location: Williamsburg, Drop Off Location: Statue_of_Liberty.
	// We have found the closest driver Elena(4.7) for you.
	// Elena is now 7.9 miles away from you.

	// get distance from rider to driver
	double dist = calculateDistance(rider->getPickupLatitude(), rider->getPickupLongitude(), driver->getCurrentLatitude(), driver->getCurrentLongitude());

	out << "Ride requested for user " << rider->getFirstName() << ", looking for an " << rider->getVehiclePreference() << " vehicle.\n";
	out << "Pick Up Location: " << rider->getPickupLocationName() << ", Drop off Location: " << rider->getDropoffLocationName() << ".\n";
	out << "We have found the closest driver " << driver->getFirstName() << "(" << driver->getRating() << ") for you.\n";
	out << driver->getFirstName() << " is now " << std::fixed << std::setprecision(1) << dist << " miles away from you.\n";

	return;
}

// car type then calc dist
// proximity and 
void fillRequest(ofstream &out, string num, list<Rider*>* riderList, list<Driver*>* driverList) {
	// inNum, riders, drivers, out0
	Rider* rider = NULL;
	Driver* driver = NULL;

	searchRiderByNumber(num, riderList, rider);

	if (rider==NULL) {
		out << "Account does not exist.\n";
		return;
	}
	cout << "Found the rider\n";

	// search for driver for the rider
	// if the rider was already doing some other action aka not available
	if (rider->getCurrentState() != "Ready_to_request") {
		riderStatus(out, rider);
		return;
	}

	findDriverForRider(rider, driverList, driver);

	if (driver==NULL) {
		// no driver found
		writeRequestNoDriver(out, rider);
		return;
	}
	cout << "found a driver for rider" << endl;

	// found a driver
	writeRequest(out, rider, driver);

	// edit the rider and driver that have been matched
	rider->setCurrentState("Driver_on_the_way");
	rider->setDriverFirstName(driver->getFirstName());
	rider->setDriverLastName(driver->getLastName());
	rider->setDriverPhoneNumber(driver->getPhoneNumber());

	driver->setCurrentState("On_the_way_to_pickup");
	driver->setRiderFirstName(rider->getFirstName());
	driver->setRiderLastName(rider->getLastName());
	driver->setRiderPhoneNumber(rider->getPhoneNumber());
}

void fillCancel(ofstream &out, string num, list<Rider*>* &riderList, list<Driver*>* &driverList) {

	Rider* rider = NULL;
	Driver* driver = NULL;

	searchRiderByNumber(num, riderList, rider);

	// rider not found
	if (rider!=NULL) {
		// do all the rider functons

		return;
	}

	searchDriverByNumber(num, driverList, driver);

	if (driver!=NULL) {
		// do all the driver functions

		return;
	}

	// if i get here then no rider or driver was found with that number


	// is the driver canceling?
	// is the rider canceling?

	// 
}

void writeRiders(ofstream &out, list<Rider*>* &riderList) {
	list<Rider*>::iterator it;
	for (it=riderList->begin(); it!=riderList->end(); it++) {
		out << **it << endl;
	}
	return;
}

void writeDrivers(ofstream &out, list<Driver*>* &driverList) {
	list<Driver*>::iterator it;
	for (it=driverList->begin(); it!=driverList->end(); it++) {
		out << **it << endl;
	}
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

    Rider* rider = NULL;
    Driver* driver = NULL;


    // is the phone number valid
    if (isPhoneNumber(inNum)) {

    	// checks request
    	if (requestType=="request") {

    		fillRequest(output0, inNum, riders, drivers);

    	} else if (requestType=="cancel") {

    		// figure out how to cance
    		fillCancel()

    	} else {
    		cerr << "ERROR: Invaid ride type - " << requestType << endl;
    	}
    } else {
    	// bad input
    	output0 << "Phone number is invalid.\n";
    }

    writeRiders(output1, riders);
    writeDrivers(output2, drivers);

    // closes the outputs
    output0.close();
    output1.close();
    output2.close();

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