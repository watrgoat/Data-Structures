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
	switch (dayDigit) {
	case "M":
		return "Monday";
	case "T":
		return "Tuesday";
	case "W":
		return "Wednesday";
	case "R":
		return "Thursday";
	case "F":
		return "Friday";
	default:
		cerr << "ERROR: Incorrect day digit:" << dayDigit << endl;
		exit(1);
	}
}

void dayExpander(const vector<string> &shortDayCourses, vector<Course> &readDayCourses) {
	
	readDayCourses.push_back(Course(
	shortDayCourses[0], shortDayCourses[1], shortDayCourses[2], shortDayCourses[3],
	shortDayCourses[4], shortDayCourses[5], shortDayCourses[6], shortDayCourses[7]));
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