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
	vector<string> indvCourse;


	int i = 0;
	while (file>>word) {
		// cout << "test" << endl;
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
	unsigned int classNameSize = 11;
	unsigned int daySize = 6;
	int entryCount = 0;
	unsigned int j;
	
	// loop over ahead of printing and save where the last one was bc of un
	for (unsigned int i=0;i<c.size();i++) {
		if (currRoom!=c[i].getRoom()) {
			if (!currRoom.empty()) {
				cout << entryCount << " entries\n\n";
			}
			currRoom = c[i].getRoom();
			cout << "Room " << currRoom << endl;
			j = i;
			while (j < c.size() && currRoom==c[j].getRoom()) {
				// find max length
				if (c[j].getCourseName().length() > classNameSize) {
					classNameSize = c[j].getCourseName().length();
				}
				if (c[j].getDay().length() > daySize) {
					daySize = c[j].getDay().length();
				}
				j++;
			}
			entryCount = j-i;
			string classSpace(classNameSize-11, ' ');
			string daySpace(daySize-3, ' ');
			cout << "Dept  CourseNum  Class Title" << classSpace << "  Day" << daySpace << "  Start Time  End Time\n";
			string classDashes(classNameSize, '-');
			string dayDashes(daySize, '-');
			cout << "----  ---------  " << classDashes << "  " << dayDashes << "  ----------  --------\n";
		}
		string classSpace(classNameSize-c[i].getCourseName().length(), ' ');
		string daySpace(daySize-c[i].getDay().length(), ' ');
		cout << c[i].getDept() << "  " << c[i].getCourseCode()<< "    " <<  c[i].getCourseName() << classSpace << "  " << c[i].getDay() << daySpace << "  " << c[i].getStartTime() << "     " << c[i].getEndTime() << " " <<  endl;
	}
	cout << entryCount << " entries\n\n";
}

void oneRoom(vector<Course> &roomCourses, string inRoom) {
	for (unsigned int i=0; i<roomCourses.size(); i++) {
		if (roomCourses[i].getRoom() != inRoom) {
			roomCourses.erase(roomCourses.begin() + i);
		}
	}
}

int main(int argc, char* argv[]) {

	// checks argument count
	if (argc!=4&&argc!=5) {
		cerr << "ERROR: Invalid input count." << endl;
		exit(1);
	}

	ifstream inputFile(argv[1]);
	ofstream outputFile(argv[2]);
	string arg1 = argv[3];

	// checks if input and output files are able to be opened
	if (!inputFile.good()) {
	    std::cerr << "Can't open " << argv[1] << " to read.\n";
	    exit(1);
	} if (!outputFile.good()) {
    	std::cerr << "Can't open " << argv[2] << " to write.\n";
    	exit(1);
    }

    // checks if input file is empty
    if (inputFile.peek() == ifstream::traits_type::eof()) {
    	cout << "No data available.\n\n";
    	return 0;
    }

	vector<Course> courses;

	readCourses(inputFile, courses);


	// cout << "Finished reading " << courses.size() << " courses" << endl;

	// checks argument inputs and calls assosiated functions
	if (argc==4) {
		if (arg1=="room") {
			// sort by rooms
			sort(courses.begin(), courses.end(), compareRoom);
			printRoom(courses);
		} else if (arg1=="custom") {
			// find the times when rooms are empty.
		}
	} else if (argc==5) {
		// maybe needed??
		string arg2 = argv[4];
		if (arg1=="room") {
			cout << "HERE" << endl;
			// write func that only saves courses that are in that room from courses
			oneRoom(courses, arg2);
			for (unsigned int i=0;i<courses.size();i++)
				cout << c[i].getDept() << "  " << c[i].getCourseCode()<< "    " <<  c[i].getCourseName() << classSpace << "  " << c[i].getDay() << "  " << c[i].getStartTime() << "     " << c[i].getEndTime() << " " <<  endl;
			// printRoom(courses);
		} else if (arg1=="dept") {

		}
	} else {
		cerr << "ERROR: Incorrect input args.\n";
	}

	return 0;
}