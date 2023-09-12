// scheduling.cpp
// main file for hw 2

#include <iostream>
#include <fstream>
#include <iomanip>
#include <algorithm>
#include <vector>
#include "course.h"

using namespace std;

string convertDay(string dayDigit) {
	if (dayDigit=="M") {}
	return ;
}

int main(int argc, char* argv[]) {

	ifstream inputFile(argv[1]);
	ofstream outputFile(argv[2]);

	vector<Course> courses;



	// checks argument inputs and calls assosiated functions
	if (argc==4) {
		if (argv[3]=="room") {
			// finds all rooms
		} else if (argv[3]=="custom") {
			// find the times when rooms are empty.
		}
	} else if (argc==5) {
		if (argv[3]=="room") {
			// write func that only saves courses that are in that room from argv[4]
		} else if (argv[3]=="dept") {

		}
	} else {
		cerr << "ERROR: Incorrect arguments inputted.\n";
	}

	

	// do stuff
}