// course class

#include <iostream>
#include <map>
#include <string>
#include "course.h"

using namespace std;

// apparantly maps arent allowed???? everyone should already be familiar with dicts...
// const map<string, int> dayMap = {{"Monday", 0}, {"Tuesday", 1}, {"Wednesday", 2}, {"Thursday", 3}, {"Friday", 4}};

Course::Course(string aCrn, string aDept, string aCourseCode, string aCourseName, 
			string aDay, string aStartTime, string aEndTime, string aRoom) {
	crn = aCrn;
	dept = aDept;
	courseCode = aCourseCode;
	courseName = aCourseName;
	day = aDay;
	startTime = aStartTime;
	endTime = aEndTime;
	room = aRoom;
}

string Course::getDept() const {
	return dept;
}
string Course::getCourseCode() const {
	return courseCode;
}
string Course::getCourseName() const{
	return courseName;
}
string Course::getDay() const {
	return day;
}
string Course::getStartTime() const {
	return startTime;
}
string Course::getEndTime() const {
	return endTime;
}
string Course::getRoom() const {
	return room;
}

int day2int(const string &dayOfWeek) {
	if (dayOfWeek=="Monday") {
		return 0;
	} else if (dayOfWeek=="Tuesday") {
		return 1;
	} else if (dayOfWeek=="Wednesday") {
		return 2;
	} else if (dayOfWeek=="Thursday") {
		return 3;
	} else {
		return 4;
	}
}

bool word2bool(const string &s1, const string &s2) {
	if (s1.compare(s2)<=0) {
		return true;
	} else {
		return false;
	}
}

// 11:12PM
bool time2bool(const string &time1, const string &time2) {

	if (time1[5] == 'A' && time2[5] == 'P') {
		return true;
	} else if (time1[5] == 'P' && time2[5] == 'A') {
		return false;
	} else if (stoi(time1.substr(0, 2)) > stoi(time2.substr(0, 2))) {
		return true;
	} else if (stoi(time2.substr(0, 2)) > stoi(time1.substr(0, 2))) {
		return false;
	} else if (stoi(time1.substr(3, 2)) > stoi(time2.substr(3, 2))) {
		return true;
	} else if (stoi(time2.substr(3, 2)) > stoi(time1.substr(3, 2))) {
		return false;
	} else {
		return true;
	}
}


// main roomm comp
bool compareRoom(const Course &course1, const Course &course2) {
	// order of ops: tables by alphabetic room name??, day, start time hour, course code, department

	if (course1.getRoom()!=course2.getRoom()) {
		// compare rooms
		// if string 1 <= string 2 then string1 comes before
		return word2bool(course1.getRoom(), course2.getRoom());
		
	} else if (course1.getDay()!=course2.getDay()) {
		return day2int(course1.getDay()) >= day2int(course1.getDay());

	} else if (course1.getStartTime()!=course2.getStartTime()) {
		// am pm, hour, then min
		return time2bool(course1.getStartTime(), course2.getStartTime());

	} else if (course1.getCourseCode()!=course2.getCourseCode()) {
		return word2bool(course1.getCourseCode(), course2.getCourseCode());

	} else if (course1.getDept()!= course2.getDept()) {
		return word2bool(course1.getDept(), course2.getDept());

	} else {
		// they are the complete same
		return false;
	}
}

// main dept compare
bool compareDept(const Course &course1, const Course &course2) {
	return true;
}