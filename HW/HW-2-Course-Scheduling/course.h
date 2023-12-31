// course header

#ifndef COURSE_H
#define COURSE_H

#include <string>

using std::string;

class Course {
public:
	Course(string aCrn, string aDept, string aCourseCode, string aCourseName, 
		string aDay, string aStartTime, string aEndTme, string aRoom);

	// ACCESSORS
	string getDept() const;
	string getCourseCode() const;
	string getCourseName() const;
	string getDay() const;
	string getStartTime() const;
	string getEndTime() const;
	string getRoom() const;

private:
	string crn;
	string dept;
	string courseCode;
	string courseName;
	string day;
	string startTime;
	string endTime;
	string room;
};

// room compare order: tables by alphabetic room name??, day, start time hour, course code, department
bool compareRoom(const Course &course1, const Course &course2);

// department compare
bool compareDept(const Course &course1, const Course &course2);

// comparison for custom function
bool compareOnlyRoom(const Course &course1, const Course &course2);

#endif