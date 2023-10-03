#ifndef RIDER_H
#define RIDER_H

#include <string>

class Rider {
private:
    std::string firstName;
    std::string lastName;
    std::string gender;
    int age;
    std::string phoneNumber;
    std::string rating;
    std::string pickupLocationName;
    double pickupLatitude;
    double pickupLongitude;
    std::string dropoffLocationName;
    double dropoffLatitude;
    double dropoffLongitude;
    std::string vehiclePreference;
    std::string currentState;
    std::string driverFirstName;
    std::string driverLastName;
    std::string driverPhoneNumber;

public:
    Rider();
    
    // Constructor
    Rider(const std::string& firstName,
          const std::string& lastName,
          const std::string& gender,
          int age,
          const std::string& phoneNumber,
          const std::string& pickupLocationName,
          const std::string& rating,
          double pickupLatitude,
          double pickupLongitude,
          const std::string& dropoffLocationName,
          double dropoffLatitude,
          double dropoffLongitude,
          const std::string& vehiclePreference,
          const std::string& currentState,
          const std::string& driverFirstName,
          const std::string& driverLastName,
          const std::string& driverPhoneNumber);

    // Getter methods
    std::string getFirstName() const;
    std::string getLastName() const;
    std::string getGender() const;
    int getAge() const;
    std::string getPhoneNumber() const;
    std::string getRating() const;
    std::string getPickupLocationName() const;
    double getPickupLatitude() const;
    double getPickupLongitude() const;
    std::string getDropoffLocationName() const;
    double getDropoffLatitude() const;
    double getDropoffLongitude() const;
    std::string getVehiclePreference() const;
    std::string getCurrentState() const;
    std::string getDriverFirstName() const;
    std::string getDriverLastName() const;
    std::string getDriverPhoneNumber() const;

    // Setter methods
    void setFirstName(const std::string& firstName);
    void setLastName(const std::string& lastName);
    void setGender(const std::string& gender);
    void setAge(int age);
    void setPhoneNumber(const std::string& phoneNumber);
    void setRating(const std::string& rating);
    void setPickupLocationName(const std::string& locationName);
    void setPickupLatitude(double latitude);
    void setPickupLongitude(double longitude);
    void setDropoffLocationName(const std::string& locationName);
    void setDropoffLatitude(double latitude);
    void setDropoffLongitude(double longitude);
    void setVehiclePreference(const std::string& preference);
    void setCurrentState(const std::string& state);
    void setDriverFirstName(const std::string& driverFirstName);
    void setDriverLastName(const std::string& driverLastName);
    void setDriverPhoneNumber(const std::string& driverPhoneNumber);
};

#endif
