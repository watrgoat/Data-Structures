#include "Driver.h"

Driver::Driver()
: firstName(""), lastName(""), gender(""), age(0), phoneNumber(""), rating(0.0), 
  currentLatitude(0.0), currentLongitude(0.0), vehicleType(""), currentState(""), 
  riderFirstName("null"), riderLastName("null"), riderPhoneNumber("null") {}

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

std::string Driver::getFirstName() const { return firstName; }
std::string Driver::getLastName() const { return lastName; }
std::string Driver::getGender() const { return gender; }
int Driver::getAge() const { return age; }
std::string Driver::getPhoneNumber() const { return phoneNumber; }
double Driver::getRating() const { return rating; }
double Driver::getCurrentLatitude() const { return currentLatitude; }
double Driver::getCurrentLongitude() const { return currentLongitude; }
std::string Driver::getVehicleType() const { return vehicleType; }
std::string Driver::getCurrentState() const { return currentState; }
std::string Driver::getRiderFirstName() const { return riderFirstName; }
std::string Driver::getRiderLastName() const { return riderLastName; }
std::string Driver::getRiderPhoneNumber() const { return riderPhoneNumber; }

void Driver::setFirstName(const std::string& firstName) { this->firstName = firstName; }
void Driver::setLastName(const std::string& lastName) { this->lastName = lastName; }
void Driver::setGender(const std::string& gender) { this->gender = gender; }
void Driver::setAge(int age) { this->age = age; }
void Driver::setPhoneNumber(const std::string& phoneNumber) { this->phoneNumber = phoneNumber; }
void Driver::setRating(double rating) { this->rating = rating; }
void Driver::setCurrentLatitude(double latitude) { this->currentLatitude = latitude; }
void Driver::setCurrentLongitude(double longitude) { this->currentLongitude = longitude; }
void Driver::setVehicleType(const std::string& vehicleType) { this->vehicleType = vehicleType; }
void Driver::setCurrentState(const std::string& currentState) { this->currentState = currentState; }
void Driver::setRiderFirstName(const std::string& riderFirstName) { this->riderFirstName = riderFirstName; }
void Driver::setRiderLastName(const std::string& riderLastName) { this->riderLastName = riderLastName; }
void Driver::setRiderPhoneNumber(const std::string& riderPhoneNumber) { this->riderPhoneNumber = riderPhoneNumber; }