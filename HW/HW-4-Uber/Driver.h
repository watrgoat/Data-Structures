#ifndef DRIVER_H
#define DRIVER_H

#include <string>

class Driver {
private:
    std::string firstName;
    std::string lastName;
    std::string gender;
    int age;
    std::string phoneNumber;
    std::string rating;
    double currentLatitude;
    double currentLongitude;
    std::string vehicleType;
    std::string currentState;
    std::string riderFirstName;
    std::string riderLastName;
    std::string riderPhoneNumber;

public:
    Driver();

    // Constructor
    Driver(const std::string& firstName,
           const std::string& lastName,
           const std::string& gender,
           int age,
           const std::string& phoneNumber,
           const std::string& rating,
           double currentLatitude,
           double currentLongitude,
           const std::string& vehicleType,
           const std::string& currentState,
           const std::string& riderFirstName,
           const std::string& riderLastName,
           const std::string& riderPhoneNumber);
    

    // Getter methods
    std::string getFirstName() const;
    std::string getLastName() const;
    std::string getGender() const;
    int getAge() const;
    std::string getPhoneNumber() const;
    std::string getRating() const;
    double getCurrentLatitude() const;
    double getCurrentLongitude() const;
    std::string getVehicleType() const;
    std::string getCurrentState() const;
    std::string getRiderFirstName() const;
    std::string getRiderLastName() const;
    std::string getRiderPhoneNumber() const;

    // Setter methods
    void setFirstName(const std::string& firstName);
    void setLastName(const std::string& lastName);
    void setGender(const std::string& gender);
    void setAge(int age);
    void setPhoneNumber(const std::string& phoneNumber);
    void setRating(const std::string& rating);
    void setCurrentLatitude(double latitude);
    void setCurrentLongitude(double longitude);
    void setVehicleType(const std::string& vehicleType);
    void setCurrentState(const std::string& currentState);
    void setRiderFirstName(const std::string& riderFirstName);
    void setRiderLastName(const std::string& riderLastName);
    void setRiderPhoneNumber(const std::string& riderPhoneNumber);
};

#endif