// header
#ifndef COURSE_H
#define COURSE_H

#include <string>

using std::string;

class Course {
public:
	Course(string aDept, string aCourseCode, string aCourseName, 
		string aDay, string aStartTime, string aEndTme, string aRoom);

	// no accessors or modifiers needed
	string getDept() const;
	string getCourseCode() const;
	string getCourseName() const;
	string getDay() const;
	string getStartTime() const;
	string getEndTime() const;
	string getRoom() const;


	// member func for comparing??
	void printRoom() const; // room?, deptCode, courseCode, courseName, day, startTime, endTime
	
	void printDept() const; // courseCode, CourseName, day, startTime, endTime

private:
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

#endif