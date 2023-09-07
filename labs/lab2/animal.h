// File: animal.h

class Date {
public:
  Date();
  Date(int aHour, int aMinute, int aSecond);

  // ACCESSORS
  int getHour() const;
  int getMinute() const;
  int getSecond() const;

  // MODIFIERS
  void setHour(int aHour);
  void setMinute(int aMinute);
  void setSecond(int aSecond);
  void increment();

  // other member functions that operate on date objects
  bool isEqual(const Date& date2) const;  // same day, month, & year?
  bool isLeapYear() const;     
  int lastDayInMonth() const;
  bool isLastDayInMonth() const;
  void print() const;                     // output as month/day/year

private:  // REPRESENTATION (member variables)
  int hour;
  int minute;
  int second;
};

// prototypes for other functions that operate on class objects are often
// included in the header file, but outside of the class declaration
bool sameDay(const Date &date1, const Date &date2); // same day & month?