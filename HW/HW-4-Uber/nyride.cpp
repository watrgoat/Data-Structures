#include <list>
#include <iostream>
#include <fstream>
#include <Rider.h>
#include <Driver.h>

using namespace std;

// main uber functions
// what is it asking for?
// large file outline?
// what order should this be done
// efficiency?
// how to use std::list in this?
list readRiderFile(const ifstream &file, list &inRiders) {
	string word;

	int i = 0;
	while (file >> word) {
		// make a curr rider w def values
		// add setter 
		switch {
		case 0:
			// f name

		case 1:
			// last name
		case 2:
			// gender
		case 3:
			// age
		case 4:
			// number
		case 5:
			// rating
		case 6:
			// pickup loc
		case 7:
			// pickup lat
		case 8:
			// pickup long
		case 9:
			// drop loc
		case 10:
			// drop lat
		case 11:
			// drop long
		case 12:
			// car type req
		case 13:
			// current state
		case 14:
			// drive f name
		case 15:
			// driver l name
		case 16:
			// driver number
		}
		i++;
	}
}


int main(int argc, char* argv[]) {
	// do stuff
	if (argc > 8 || argc < 8) {
		cerr << "ERROR: WONG INPUT SIZE" << endl;
		exit(1);
	}


	return 0;
}