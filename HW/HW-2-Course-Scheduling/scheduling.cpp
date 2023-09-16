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
	// converts day characters into full words
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
	// expands days into multiple course objects, for ex: MR -> two days so 2 objects
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
	// reads all the courses from input files
	string word;
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

void oneRoom(vector<Course> &roomCourses, const string &inRoom) {
	unsigned int i = 0;

	while (i<roomCourses.size()) {
		if (roomCourses[i].getRoom() != inRoom) {
			roomCourses.erase(roomCourses.begin() + i);
		} else {
			i++;
		}
	}
}

void printRoom(ofstream &file, const vector<Course> &c) {
	string currRoom;
	unsigned int classNameSize = 11;
	unsigned int daySize = 6;
	unsigned int deptSize = 4;
	int entryCount = 0;
	unsigned int j;
	
	// loop over ahead of printing and save where the last one was bc of un
	for (unsigned int i=0;i<c.size();i++) {
		// checks if room has changed
		if (currRoom!=c[i].getRoom()) {
			// checks if room is not empty to print newline
			if (!currRoom.empty()) {
				file << entryCount << " entries\n\n";
			}
			// reseting vars
			currRoom = c[i].getRoom();
			classNameSize = 11;
			daySize = 6;
			deptSize = 4;
			file << "Room " << currRoom << endl;
			j = i;
			// searches ahead to find max sizes of course name, dept, and day.
			while (j < c.size() && currRoom==c[j].getRoom()) {
				// find max length
				if (c[j].getCourseName().length() > classNameSize) {
					classNameSize = c[j].getCourseName().length();
				}
				if (c[j].getDay().length() > daySize) {
					daySize = c[j].getDay().length();
				}
				if (c[j].getDept().length() > deptSize) {
					deptSize = c[j].getDept().length();
				}
				j++;
			}
			// uses previously searched values to update the header
			entryCount = j-i;
			string classSpace(classNameSize-11, ' ');
			string daySpace(daySize-3, ' ');
			string deptSpace(deptSize-4, ' ');
			file << "Dept" << deptSpace << "  Coursenum  Class Title" << classSpace << "  Day" << daySpace << "  Start Time  End Time\n";

			string classDashes(classNameSize, '-');
			string dayDashes(daySize, '-');
			string deptDashes(deptSize, '-');
			file << deptDashes << "  ---------  " << classDashes << "  " << dayDashes << "  ----------  --------\n";
		}
		// uses the values from earlier to fill in extra spaces
		string classSpace(classNameSize-c[i].getCourseName().length(), ' ');
		string daySpace(daySize-c[i].getDay().length(), ' ');
		string deptSpace(deptSize-c[i].getDept().length(), ' ');
		file << c[i].getDept() << deptSpace << "  " << c[i].getCourseCode()<< "    " <<  c[i].getCourseName() << classSpace << "  " << c[i].getDay() << daySpace << "  " << c[i].getStartTime() << "     " << c[i].getEndTime() << " " <<  endl;
	}
	file << entryCount << " entries\n\n";
}

void oneDept(vector<Course> &deptCourses, const string &inDept) {
	// erases all other department courses from stored vector
	unsigned int i = 0;

	while (i<deptCourses.size()) {
		if (deptCourses[i].getDept() != inDept) {
			deptCourses.erase(deptCourses.begin() + i);
		} else {
			i++;
		}
	}
}

void printDept(ofstream &file, const vector<Course> &c, const string &inDept) {
	unsigned int classNameSize = 11;
	unsigned int daySize = 6;
	int entryCount = c.size();

	file << "Dept " << inDept << endl;

	// finds all max values for future outputs
	for (unsigned int i=0;i<c.size();i++) {
		// find max length
		if (c[i].getCourseName().length() > classNameSize) {
			classNameSize = c[i].getCourseName().length();
		}
		if (c[i].getDay().length() > daySize) {
			daySize = c[i].getDay().length();
		}
	}

	// prints the heading of dept file using variables recieved from earilier
	string classSpace(classNameSize-11, ' ');
	string daySpace(daySize-3, ' ');
	file << "Coursenum  Class Title" << classSpace << "  Day" << daySpace << "  Start Time  End Time\n";
	string classDashes(classNameSize, '-');
	string dayDashes(daySize, '-');
	file << "---------  " << classDashes << "  " << dayDashes << "  ----------  --------\n";
	
	// loop over ahead of printing and save where the last one was bc of un
	for (unsigned int i=0;i<c.size();i++) {
		// formatting helpers
		string classSpace(classNameSize-c[i].getCourseName().length(), ' ');
		string daySpace(daySize-c[i].getDay().length(), ' ');

		file << c[i].getCourseCode()<< "    " <<  c[i].getCourseName() << classSpace << "  " << c[i].getDay() << daySpace << "  " << c[i].getStartTime() << "     " << c[i].getEndTime() << " " <<  endl;
	}

	file << entryCount << " entries\n\n";
}

void printCustom(ofstream &file, const vector<Course> &c) {
	// most common class start time
	int currCount = 1;
	int maxCount = 1;
	string mostCommonTime;

	for (unsigned int i=1; i<c.size(); i++) {
		if (c[i].getStartTime()==c[i-1].getStartTime()) {
			currCount++;
		} else {
			currCount = 1;
		}

		if (currCount > maxCount) {
			maxCount = currCount;
			mostCommonTime = c[i].getStartTime();
		}
	}

	file << "The most common starting time accross all the courses is: " << mostCommonTime << endl;

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
    	outputFile << "No data available.\n";
    	return 0;
    }

	vector<Course> courses;

	readCourses(inputFile, courses);

	// checks argument inputs and calls assosiated functions
	if (argc==4) {
		if (arg1=="room") {
			// sort by rooms
			sort(courses.begin(), courses.end(), compareRoom);
			printRoom(outputFile, courses);
		} else if (arg1=="custom") {

			// sort based on start time
			sort(courses.begin(), courses.end(), compareOnlyRoom);
			// find most common start time
			printCustom(outputFile, courses);
		}
	} else if (argc==5) {

		string arg2 = argv[4];
		if (arg1=="room") {

			// only saves courses that are in that room from courses
			oneRoom(courses, arg2);

			if (courses.size()==0) {
				outputFile << "No data available.\n";

			} else {
				sort(courses.begin(), courses.end(), compareRoom);
				printRoom(outputFile, courses);

			}
		} else if (arg1=="dept") {
			// get rid of courses not in that dept
			oneDept(courses, arg2);
			sort(courses.begin(), courses.end(), compareDept);
			printDept(outputFile, courses, arg2);

		}
	} else {
		cerr << "ERROR: Incorrect input args.\n";
	}

	return 0;
}