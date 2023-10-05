#ifndef DRIVER_H
#define DRIVER_H

#include <iostream>
#include <fstream>
#include <string>

using std::string, std::ostream, std::endl;

class Driver {
private:
    string firstName;
    string lastName;
    string gender;
    int age;
    string phoneNumber;
    string rating;
    double currentLatitude;
    double currentLongitude;
    string vehicleType;
    string currentState;
    string riderFirstName;
    string riderLastName;
    string riderPhoneNumber;

public:
    // default constructor
    Driver();

    // constructor
    Driver(const string& firstName,
           const string& lastName,
           const string& gender,
           int age,
           const string& phoneNumber,
           const string& rating,
           double currentLatitude,
           double currentLongitude,
           const string& vehicleType,
           const string& currentState,
           const string& riderFirstName,
           const string& riderLastName,
           const string& riderPhoneNumber);
    
    // copy constructor
    Driver(const Driver& other);

    // Getter methods
    string getFirstName() const;
    string getLastName() const;
    string getGender() const;
    int getAge() const;
    string getPhoneNumber() const;
    string getRating() const;
    double getCurrentLatitude() const;
    double getCurrentLongitude() const;
    string getVehicleType() const;
    string getCurrentState() const;
    string getRiderFirstName() const;
    string getRiderLastName() const;
    string getRiderPhoneNumber() const;

    // Setter methods
    void setFirstName(const string& firstName);
    void setLastName(const string& lastName);
    void setGender(const string& gender);
    void setAge(int age);
    void setPhoneNumber(const string& phoneNumber);
    void setRating(const string& rating);
    void setCurrentLatitude(double latitude);
    void setCurrentLongitude(double longitude);
    void setVehicleType(const string& vehicleType);
    void setCurrentState(const string& currentState);
    void setRiderFirstName(const string& riderFirstName);
    void setRiderLastName(const string& riderLastName);
    void setRiderPhoneNumber(const string& riderPhoneNumber);
};

ostream& operator<<(ostream &out, const Driver &driver);

#endif