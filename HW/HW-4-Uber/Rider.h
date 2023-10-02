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
    double rating;
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
    // Constructor
    Rider(const std::string& firstName,
          const std::string& lastName,
          const std::string& gender,
          int age,
          const std::string& phoneNumber,
          double rating,
          const std::string& pickupLocationName,
          double pickupLatitude,
          double pickupLongitude,
          const std::string& dropoffLocationName,
          double dropoffLatitude,
          double dropoffLongitude,
          const std::string& vehiclePreference,
          const std::string& currentState,
          const std::string& driverFirstName = "null",
          const std::string& driverLastName = "null",
          const std::string& driverPhoneNumber = "null");

    // Getter methods (to be implemented)
    // ... (Other member functions as needed)
};

#endif // RIDER_H
