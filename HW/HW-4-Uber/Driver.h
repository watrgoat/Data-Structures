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
    double rating;
    double currentLatitude;
    double currentLongitude;
    std::string vehicleType;
    std::string currentState;
    std::string riderFirstName;
    std::string riderLastName;
    std::string riderPhoneNumber;

public:
    Driver() = default;
    
    // You can also provide an appropriate constructor if needed

    // Getters
    std::string getFirstName() const;
    std::string getLastName() const;
    std::string getGender() const;
    int getAge() const;
    std::string getPhoneNumber() const;
    double getRating() const;
    double getCurrentLatitude() const;
    double getCurrentLongitude() const;
    std::string getVehicleType() const;
    std::string getCurrentState() const;
    std::string getRiderFirstName() const;
    std::string getRiderLastName() const;
    std::string getRiderPhoneNumber() const;
};

#endif