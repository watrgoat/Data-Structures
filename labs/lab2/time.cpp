// File:    time.cpp
// Purpose: Implementation file for the Time class.
# include <iostream>
# include <string>

# include "time.h"


Time::Time() {	// default constructor
  hour = 0;
  minute = 0;
  second = 0;
}

Time::Time(int aHour, int aMinute, int aSecond) { // construct from hour, minute, & second
  hour = aHour;
  minute = aMinute;
  second = aSecond;
}


int Time::getHour() const {
  return hour;
}

int Time::getMinute() const {
  return minute;
}
	
int Time::getSecond() const {
  return second;
}

void Time::setHour(int h) {
  hour = h;
}

void Time::setMinute(int m) {
  minute = m;
}

void Time::setSecond(int s) {
  second = s; 
}

void Time::PrintAMPM() const {
  // 12:00:00 AM
  int tmpHour = hour;
  std::string ext = " am";
  if (hour > 12) {
    tmpHour -= 12;
    ext = " pm";
  }
  if (hour == 12) {
    ext = " pm";
  }
  
  std::string sHour = std::to_string(tmpHour);
  std::string sMinute = std::to_string(minute);
  std::string sSecond = std::to_string(second);

  if (sHour.length() < 2) {
    sHour.insert(0, "0");
  }
  if (sMinute.length() < 2) {
    sMinute.insert(0, "0");
  }
  if (sSecond.length() < 2) {
    sSecond.insert(0, "0");
  }

  if (hour==0||hour==24) {
    // print 12 am
    std::cout << "12" << ':' << sMinute << ':' << sSecond << " am" << std::endl; 
  } else {
    std::cout << sHour << ':' << sMinute << ':' << sSecond << ext << std::endl; 
  }

}