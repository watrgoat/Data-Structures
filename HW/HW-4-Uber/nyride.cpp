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

/*	Simplfied Uber:
	
	takes 7 arguments on top of the run file
	1. drivers input file
	2. riders input file
	3. users output file from input command
	4. drivers output file
	5. riders output file
	6. input phone number
	7. ride request or cancel
	
*/

// reads each driver into the driver list
void readDriverFile(ifstream &file, list<Driver*>* &inDrivers) {
	string word;

	int i = 0;
	// loop over driver text
	// assign values to temp Driver obj then add to list
	Driver curr;
	while (file >> word) {
		// break statements are required to get no errors
		// switch determines differnt drivers
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
			// put driver on the heap and add to list
			Driver* d = new Driver(curr);
			inDrivers->push_back(d);
			Driver curr;
		}
	}
}

// reads each rider into the rider list
void readRiderFile(ifstream &file, list<Rider*>* &inRiders) {
	string word;

	int i = 0;
	Rider curr;
	// loop over input rider file
	while (file >> word) {
		// switch determine different riders
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
			// add rider to heap and push to back
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

// checks if string is in phone num format
bool isPhoneNumber(const string &num) {
	// regex pattern: follows xxx-xxx-xxxx digits only format
	regex pattern("^\\d{3}-\\d{3}-\\d{4}$");
    return regex_match(num, pattern);
}

// returns driver from driver list based on phone number input
Driver* searchDriverByNumber(const string &num, list<Driver*> &driverList) {
	list<Driver*>::iterator it;
	// iterate over drivers and return if matches phone number
	for (it = driverList.begin(); it!=driverList.end(); it++) {
		if ((*it)->getPhoneNumber() == num) {
			return *it;
		}
	}
	return NULL;
}

// search for rider by a phone number and return the pointer to that rider
Rider* searchRiderByNumber(const string &num, list<Rider*> &riderList) {
	list<Rider*>::iterator it;
	// loops through riders returns when finding proper phone number
    for (it = riderList.begin(); it != riderList.end(); ++it) {
        if ((*it)->getPhoneNumber() == num) {
            return *it;
        }
    }
    return NULL;
}

// searches for a driver for a specified rider, returns driver for that rider
Driver* findDriverForRider(Rider* &inRider, list<Driver*> &driverList) {
	list<Driver*>::iterator it;
	double minDist = std::numeric_limits<double>::max();
	double currDist;
	Driver* outDriver = NULL;

	// iterates over list finding the minimum distanced driver to the current requesting rider
	for (it = driverList.begin(); it!=driverList.end(); it++) {
		// if the driver is available
		if ((*it)->getCurrentState() == "Available") {
			// check if driver fits preferred vehicle type
			if ((*it)->getVehicleType() == inRider->getVehiclePreference()) {
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
	return outDriver;
}


// outputs the status of the rider if it isnt available
void riderStatus(ofstream &out, Rider* &r) {
	if (r->getCurrentState() == "Driver_on_the_way") {
		out << "You have already requested a ride and your driver is on the way to the pickup location." << endl;
	} else {
		out << "You can not request a ride at this moment as you are already on a trip." << endl;
	}
	return;
}

// writes the request for when no driver is found
void writeRequestNoDriver(ofstream &out, Rider* &rider) {
	// a vs an
	if (rider->getVehiclePreference()=="Economy") {
		out << "Ride requested for user " << rider->getFirstName() << ", looking for an " << rider->getVehiclePreference() << " vehicle." << endl;
	} else {
		out << "Ride requested for user " << rider->getFirstName() << ", looking for a " << rider->getVehiclePreference() << " vehicle." << endl;
	}

	out << "Pick Up Location: " << rider->getPickupLocationName() << ", Drop Off Location: " << rider->getDropoffLocationName() << "." << endl;
	out << "Sorry we can not find a driver for you at this moment." << endl;

	return;
}

// write function for a request being filled out
void writeRequest(ofstream &out, Rider* &rider, Driver* &driver) {

	// get distance from rider to driver and truncates to 1 decimal place
	double dist = calculateDistance(rider->getPickupLatitude(), rider->getPickupLongitude(), driver->getCurrentLatitude(), driver->getCurrentLongitude());
	dist = int(dist*10)/10.0f;

	if (rider->getVehiclePreference()=="Economy") {
		out << "Ride requested for user " << rider->getFirstName() << ", looking for an " << rider->getVehiclePreference() << " vehicle." << endl;
	} else {
		out << "Ride requested for user " << rider->getFirstName() << ", looking for a " << rider->getVehiclePreference() << " vehicle." << endl;
	}

	out << "Pick Up Location: " << rider->getPickupLocationName() << ", Drop Off Location: " << rider->getDropoffLocationName() << "." << endl;
	out << "We have found the closest driver " << driver->getFirstName() << "(" << driver->getRating() << ") for you." << endl;
	out << driver->getFirstName() << " is now " << dist << " miles away from you." << endl;

	return;
}

// helper func for when a driver is requested
void fillRequest(ofstream &out, string num, list<Rider*>* riderList, list<Driver*>* driverList) {
	
	// get rider from number
	Rider* rider = searchRiderByNumber(num, *riderList);

	// exit if rider was not found
	if (rider==NULL) {
		out << "Account does not exist." << endl;
		return;
	}

	
	// exit if rider was not available for ride
	if (rider->getCurrentState() != "Ready_to_request") {
		riderStatus(out, rider);
		return;
	}
	
	// find driver for the rider
	Driver* driver = findDriverForRider(rider, *driverList);

	// exit if no driver found
	if (driver==NULL) {
		writeRequestNoDriver(out, rider);
		return;
	}

	// write the request into ouput
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

// helper func for removing driver and rider status
void removeStatus(Rider* r, Driver* d) {
	d->setCurrentState("Available");
	d->setRiderFirstName("null");
	d->setRiderLastName("null");
	d->setRiderPhoneNumber("null");

	r->setCurrentState("Ready_to_request");
	r->setDriverFirstName("null");
	r->setDriverLastName("null");
	r->setDriverPhoneNumber("null");
}

// helper func fullfilling a cancel request
void fillCancel(ofstream &out, string num, list<Rider*>* &riderList, list<Driver*>* &driverList) {

	Rider* rider = searchRiderByNumber(num, *riderList);

	// rider found fullfill rider cancel
	if (rider!=NULL) {

		// check rider for otw status
		if (rider->getCurrentState()!="Driver_on_the_way") {
			out << "You can only cancel a ride request if your driver is currently on the way to the pickup location." << endl;
			return;
		}
		
		// find driver for that rider
		Driver* driver = searchDriverByNumber(rider->getDriverPhoneNumber(), *driverList);

		out << "Ride request for user " << rider->getFirstName() << " is now canceled by the user." << endl;

		// edit the driver and riders statuses
		removeStatus(rider, driver);

		// remove rider from the list
		riderList->remove(rider);

		return;
	}

	// rider not found so search for driver
	Driver* driver = searchDriverByNumber(num, *driverList);

	// if driver found fullfill driver cancel
	if (driver!=NULL) {
		// do all the driver functions
		if (driver->getCurrentState()!="On_the_way_to_pickup") {
			out << "You can only cancel a ride request if you are currently on the way to the pickup location." << endl;
			return;
		}

		// find rider that is expecting driver
		Rider* rider = searchRiderByNumber(driver->getRiderPhoneNumber(), *riderList);

		// Your driver Edward has cancelled the ride request. We will now find a new driver for you.
		out << "Your driver " << driver->getFirstName() << " has cancelled the ride request. We will now find a new driver for you." << endl;

		removeStatus(rider, driver);

		// put driver in hold state as to not re-match driver and rider
		driver->setCurrentState("TEMP_UNAVAILABLE");

		// call fill ride request on the rider
		fillRequest(out, rider->getPhoneNumber(), riderList, driverList);

		// reset driver state back
		driver->setCurrentState("Available");

		return;
	}

	// no driver or rider found with input number
	out << "Account does not exist." << endl;
	return;
}

// write a 
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
	if (argc>8 || argc<8) {
		cerr << "ERROR: WRONG INPUT SIZE" << endl;
		exit(1);
	}

	// allocate lists onto heap containing riders and drivers also on the heap
	list<Rider*> *riders = new list<Rider*>;
	list<Driver*> *drivers = new list<Driver*>;

	// assign input args
	ifstream driverInFile(argv[1]);
	ifstream riderInFile(argv[2]);
	ofstream output0(argv[3]);
	ofstream output1(argv[4]);
	ofstream output2(argv[5]);
	string inNum = argv[6];
	string requestType = argv[7];

	// checks if input and output files are able to be opened
	if (!driverInFile.good()) {
	    std::cerr << "Can't open " << argv[1] << " to read." << endl;
	    exit(1);
	} if (!riderInFile.good()) {
    	std::cerr << "Can't open " << argv[2] << " to write." << endl;
    	exit(1);
    } if (!output0.good()) {
    	std::cerr << "Can't open " << argv[3] << " to write." << endl;
    	exit(1);
    } if (!output1.good()) {
    	std::cerr << "Can't open " << argv[4] << " to write." << endl;
    	exit(1);
    } if (!output2.good()) {
    	std::cerr << "Can't open " << argv[5] << " to write." << endl;
    	exit(1);
    }

    // read in the rider and driver input files
    readRiderFile(riderInFile, riders);
    readDriverFile(driverInFile, drivers);

    // check for valid phone num
    if (isPhoneNumber(inNum)) {

    	// checks request
    	if (requestType=="request") {

    		fillRequest(output0, inNum, riders, drivers);

    	} else if (requestType=="cancel") {

    		// figure out how to cance
    		fillCancel(output0, inNum, riders, drivers);

    	} else {
    		cerr << "ERROR: Invaid ride type - " << requestType << endl;
    	}
    } else {
    	// bad number
    	output0 << "Phone number is invalid." << endl;
    }
    
    // writes the updated driver and riders out to files.
    writeDrivers(output1, drivers);
    writeRiders(output2, riders);

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