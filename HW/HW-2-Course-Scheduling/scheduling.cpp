// scheduling.cpp
// main file for hw 2

#include <iostream>
#include <fstream>
#include <iomanip>
#include <algorithm>
#include <vector>
#include "course.h"

using namespace std;

string convertDay(char dayDigit) {
	if (dayDigit=='M') {
		return "Monday";
	} else if (dayDigit=='T') {
		return "Tuesday";
	} else if (dayDigit=='W') {
		return "Wednesday";
	} else if (dayDigit=='R') {
		return "Thursday";
	} else if (dayDigit=='F') {
		return "Friday";
	} else{
		cerr << "ERROR: Incorrect day digit:" << dayDigit << endl;
		exit(1);
	}
}

bool dayExpander(const vector<string> &shortDayCourses, vector<Course> &readDayCourses) {
	string days = shortDayCourses[4];
	if (days.length()>1) {

		readDayCourses.push_back(Course(
		shortDayCourses[0], shortDayCourses[1], shortDayCourses[2], shortDayCourses[3],
		convertDay(shortDayCourses[4][1]), shortDayCourses[5], shortDayCourses[6], shortDayCourses[7]));

		readDayCourses.push_back(Course(
		shortDayCourses[0], shortDayCourses[1], shortDayCourses[2], shortDayCourses[3],
		convertDay(shortDayCourses[4][0]), shortDayCourses[5], shortDayCourses[6], shortDayCourses[7]));
	} else {
		readDayCourses.push_back(Course(
		shortDayCourses[0], shortDayCourses[1], shortDayCourses[2], shortDayCourses[3],
		convertDay(shortDayCourses[4][0]), shortDayCourses[5], shortDayCourses[6], shortDayCourses[7]));
	}

	return true;
}

bool readCourses(ifstream &file, vector<Course> &rCourses) {
	string word;

	// catch days
	vector<string> indvCourse;
	int i = 0;
	while (file>>word) {
		// reset on new course line
		if (i%8==0&&i!=0) {
			// expand multi day courses
			dayExpander(indvCourse, rCourses);
			indvCourse.clear();
			i = 0;
		}
		indvCourse.push_back(word);
		i++;
	}
	dayExpander(indvCourse, rCourses);
	indvCourse.clear();
	return true;
}

void printRoom(const vector<Course> &c) {
	string currRoom;

	for (unsigned int i=0;i<c.size();i++) {
		if (currRoom!=c[i].getRoom()) {
			currRoom = c[i].getRoom();
			cout << "Room " << currRoom << endl;
			cout << "Dept  CourseNum  Class Title" << classNameSpace << "  Day" << daySpace << "  Start Time  End Time" << endl;

			
		}

	}
	cout << c.getDept() <<' '<< c.getCourseCode()<<' '<<  c.getCourseName() <<' '<< c.getDay() <<' ' << c.getStartTime() <<' '<< c.getEndTime() <<  endl;
}

bool findRooms(vector<Course> &allCourses) {
	// sort courses
	sort(allCourses.begin(), allCourses.end(), compareRoom);
}

int main(int argc, char* argv[]) {

	if (argc!=4&&argc!=5) {
		cerr << "ERROR: Invalid input count." << endl;
		exit(1);
	}


	ifstream inputFile(argv[1]);
	ofstream outputFile(argv[2]);
	string arg1 = argv[3];

	vector<Course> courses;

	readCourses(inputFile, courses);

	// check if courses is empty

	if (!(courses.size()>0)) {
		cout << "No data available.\n\n";
	}

	for (unsigned int i=0;i<courses.size();i++) {
		// cout << courses[i].getDept() << courses[i].getCourseCode() << courses[i].getCourseName() <<  endl;
	}

	cout << "Finished reading " << courses.size() << " courses" << endl;

	// checks argument inputs and calls assosiated functions
	if (argc==4) {
		if (arg1=="room") {
			// finds all rooms
			findRooms(courses);
		} else if (arg1=="custom") {
			// find the times when rooms are empty.
		}
	} else if (argc==5) {
		// maybe needed??
		string arg2 = argv[4];
		if (arg1=="room") {
			// write func that only saves courses that are in that room from argv[4]
		} else if (arg1=="dept") {

		}
	} else {
		cerr << "ERROR: Incorrect arguments inputted.\n";
	}

	for (unsigned int i=0;i<courses.size();i++) {
		printRoom(courses[i]);
	}

	return 0;
}