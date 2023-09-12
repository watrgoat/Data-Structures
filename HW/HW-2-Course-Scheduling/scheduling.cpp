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
	return dayMap[dayDigit];
}

int main(int argc, char* argv[]) {

	ifstream

	if (argc==4) {
		if (argv[3]=="room") {
			// find rooms
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

	vector<Course> courses;

	// do stuff
}