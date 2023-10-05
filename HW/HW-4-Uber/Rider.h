#ifndef RIDER_H
#define RIDER_H

#include <iostream>
#include <fstream>
#include <string>

using std::string, std::ostream, std::endl;

class Rider {
private:
    string firstName;
    string lastName;
    string gender;
    int age;
    string phoneNumber;
    string rating;
    string pickupLocationName;
    double pickupLatitude;
    double pickupLongitude;
    string dropoffLocationName;
    double dropoffLatitude;
    double dropoffLongitude;
    string vehiclePreference;
    string currentState;
    string driverFirstName;
    string driverLastName;
    string driverPhoneNumber;

public:
    // default constructor
    Rider();
    
    // donstructor
    Rider(const string& firstName,
          const string& lastName,
          const string& gender,
          int age,
          const string& phoneNumber,
          const string& pickupLocationName,
          const string& rating,
          double pickupLatitude,
          double pickupLongitude,
          const string& dropoffLocationName,
          double dropoffLatitude,
          double dropoffLongitude,
          const string& vehiclePreference,
          const string& currentState,
          const string& driverFirstName,
          const string& driverLastName,
          const string& driverPhoneNumber);

    // copy constructor
    Rider(const Rider& other);

    // Getter methods
    string getFirstName() const;
    string getLastName() const;
    string getGender() const;
    int getAge() const;
    string getPhoneNumber() const;
    string getRating() const;
    string getPickupLocationName() const;
    double getPickupLatitude() const;
    double getPickupLongitude() const;
    string getDropoffLocationName() const;
    double getDropoffLatitude() const;
    double getDropoffLongitude() const;
    string getVehiclePreference() const;
    string getCurrentState() const;
    string getDriverFirstName() const;
    string getDriverLastName() const;
    string getDriverPhoneNumber() const;

    // Setter methods
    void setFirstName(const string& firstName);
    void setLastName(const string& lastName);
    void setGender(const string& gender);
    void setAge(int age);
    void setPhoneNumber(const string& phoneNumber);
    void setRating(const string& rating);
    void setPickupLocationName(const string& locationName);
    void setPickupLatitude(double latitude);
    void setPickupLongitude(double longitude);
    void setDropoffLocationName(const string& locationName);
    void setDropoffLatitude(double latitude);
    void setDropoffLongitude(double longitude);
    void setVehiclePreference(const string& preference);
    void setCurrentState(const string& state);
    void setDriverFirstName(const string& driverFirstName);
    void setDriverLastName(const string& driverLastName);
    void setDriverPhoneNumber(const string& driverPhoneNumber);
};

ostream& operator<<(ostream &out, const Rider &rider);

#endif
