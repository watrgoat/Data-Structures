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
	if (dayDigit=="M") {
		return "Monday";
	} else if (dayDigit=="T") {
		return "Tuesday";
	} else if (dayDigit=="W") {
		return "Wednesday";
	} else if (dayDigit=="R") {
		return "Thursday";
	} else if (dayDigit=="F") {
		return "Friday";
	} else {
		cerr << "ERROR: Incorrect day digit:" << dayDigit << endl;
		exit(1);
	}
}

void dayExpander(const vector<string> &shortDayCourses, const vector<Course> &readDayCourses) {
	
	
	Course(indvCourse[0], indvCourse[1], indvCourse[2], indvCourse[3], indvCourse[4], indvCourse[5], indvCourse[6], indvCourse[7]);
}

bool readCourses(ifstream &file, vector<Course> &readCourses) {
	string word;

	// catch days
	vector<string> indvCourse;
	int i = 1;
	while (file>>word) {
		
		if (i%9==0) {
			// expand multi day courses
			// double up
			day

			
			indvCourse.clear();
			i = 1;
		}
		indvCourse.push_back(word);
		i++
	}
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