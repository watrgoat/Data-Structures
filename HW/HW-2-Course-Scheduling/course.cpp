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

bool compareRoom(const Course &course1, const Course &course2) {
	// order of ops: tables by alphabetic room name??, day, start time hour, course code, department
	return true;
}

// department compare
bool compareDept(const Course &course1, const Course &course2) {
	return true;
}