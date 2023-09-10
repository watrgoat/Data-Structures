// header
#include <string>

using std::string;

class Course {
public:
	Course(string aCRN, string aDeptCode, string aCourseCode, string aCourseName, 
		string aDay, string aStartTime, string aEndTme, string aRoom);

	// ACCESSORS
	string getCRN() const;
	string getDeptCode() const;
	string getCourseCode() const;
	string getCourseName() const;
	string getDay() const;
	string getStartTime() const;
	string getEndTime() const;
	string getRoom() const;

	// no modifiers needed

	// member func for comparing??
	void print() const;

};