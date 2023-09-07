// File: time.h

class Time {
public:
  Time();
  Time(int aHour, int aMinute, int aSecond);

  // ACCESSORS
  int getHour() const;
  int getMinute() const;
  int getSecond() const;

  // MODIFIERS
  void setHour(int aHour);
  void setMinute(int aMinute);
  void setSecond(int aSecond);

  void PrintAMPM() const;

private:  // REPRESENTATION (member variables)
  int hour;
  int minute;
  int second;
};