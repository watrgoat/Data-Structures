// header
#include <string>

using std::string;

class Course {
public:
	Course(string aDept, string aCourseCode, string aCourseName, 
		string aDay, string aStartTime, string aEndTme, string aRoom);

	// no accessors or modifiers needed
	string getRoom() const;
	int getCourseNameLength() const;
	int getDayLength() const;
	


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
// bool compareRoom()

// department compare
// bool compareDept()