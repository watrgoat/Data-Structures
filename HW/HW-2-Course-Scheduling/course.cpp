// course class

#include <iostream>
#include <map>
#include <string>
#include "course.h"

using namespace std::string, std::map, std::cout

const map<string, int> dayMap = {{"Monday", 0}, {"Tuesday", 1}, {"Wednesday", 2}, {"Thursday", 3}, {"Friday", 4}};

Course::Course(string aDept, string aCourseCode, string aCourseName, 
		string aDay, string aStartTime, string aEndTime, string aRoom) {
	dept = aDept;
	courseCode = aCourseCode;
	courseName = aCourseName;
	day = dayMap[aDay];
	startTime = aStartTime;
	endTime = aEndTime;
}

string Course::getDept() const {

}
string Course::getCourseCode() const {

}
string Course::getCourseName() const{

}
string Course::getDay() const {
	return dayMap.find(day)->first;
}
string Course::getStartTime() const
string Course::getEndTime() const
string Course::getRoom() const