#include "Driver.h"

Driver::Driver(const std::string& firstName,
               const std::string& lastName,
               const std::string& gender,
               int age,
               const std::string& phoneNumber,
               double rating,
               double currentLatitude,
               double currentLongitude,
               const std::string& vehicleType,
               const std::string& currentState,
               const std::string& riderFirstName,
               const std::string& riderLastName,
               const std::string& riderPhoneNumber)
    : firstName(firstName),
      lastName(lastName),
      gender(gender),
      age(age),
      phoneNumber(phoneNumber),
      rating(rating),
      currentLatitude(currentLatitude),
      currentLongitude(currentLongitude),
      vehicleType(vehicleType),
      currentState(currentState),
      riderFirstName(riderFirstName),
      riderLastName(riderLastName),
      riderPhoneNumber(riderPhoneNumber) {}

std::string Driver::getFirstName() const {
    return firstName;
}

std::string Driver::getLastName() const {
    return lastName;
}

std::string Driver::getGender() const {
    return gender;
}

int Driver::getAge() const {
    return age;
}

std::string Driver::getPhoneNumber() const {
    return phoneNumber;
}

double Driver::getRating() const {
    return rating;
}

double Driver::getCurrentLatitude() const {
    return currentLatitude;
}

double Driver::getCurrentLongitude() const {
    return currentLongitude;
}

std::string Driver::getVehicleType() const {
    return vehicleType;
}

std::string Driver::getCurrentState() const {
    return currentState;
}

std::string Driver::getRiderFirstName() const {
    return riderFirstName;
}

std::string Driver::getRiderLastName() const {
    return riderLastName;
}

std::string Driver::getRiderPhoneNumber() const {
    return riderPhoneNumber;
}
