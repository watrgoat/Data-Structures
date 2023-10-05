#include "Driver.h"

using std::string;

// default constructor
Driver::Driver()
: firstName(""), lastName(""), gender(""), age(0), phoneNumber(""), rating(""), 
  currentLatitude(0.0), currentLongitude(0.0), vehicleType(""), currentState(""), 
  riderFirstName(""), riderLastName(""), riderPhoneNumber("") {}

// constructor
Driver::Driver(const string& firstName,
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
               const string& riderPhoneNumber)
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

// copy constructor
Driver::Driver(const Driver& other) {
  firstName = other.getFirstName();
  lastName = other.getLastName();
  gender = other.getGender();
  age = other.getAge();
  phoneNumber = other.getPhoneNumber();
  rating = other.getRating();
  currentLatitude = other.getCurrentLatitude();
  currentLongitude = other.getCurrentLongitude();
  vehicleType = other.getVehicleType();
  currentState = other.getCurrentState();
  riderFirstName = other.getRiderFirstName();
  riderLastName = other.getRiderLastName();
  riderPhoneNumber = other.getRiderPhoneNumber(); }

// getters
string Driver::getFirstName() const { return firstName; }
string Driver::getLastName() const { return lastName; }
string Driver::getGender() const { return gender; }
int Driver::getAge() const { return age; }
string Driver::getPhoneNumber() const { return phoneNumber; }
string Driver::getRating() const { return rating; }
double Driver::getCurrentLatitude() const { return currentLatitude; }
double Driver::getCurrentLongitude() const { return currentLongitude; }
string Driver::getVehicleType() const { return vehicleType; }
string Driver::getCurrentState() const { return currentState; }
string Driver::getRiderFirstName() const { return riderFirstName; }
string Driver::getRiderLastName() const { return riderLastName; }
string Driver::getRiderPhoneNumber() const { return riderPhoneNumber; }

// setters
void Driver::setFirstName(const string& firstName) { this->firstName = firstName; }
void Driver::setLastName(const string& lastName) { this->lastName = lastName; }
void Driver::setGender(const string& gender) { this->gender = gender; }
void Driver::setAge(int age) { this->age = age; }
void Driver::setPhoneNumber(const string& phoneNumber) { this->phoneNumber = phoneNumber; }
void Driver::setRating(const string&  rating) { this->rating = rating; }
void Driver::setCurrentLatitude(double latitude) { this->currentLatitude = latitude; }
void Driver::setCurrentLongitude(double longitude) { this->currentLongitude = longitude; }
void Driver::setVehicleType(const string& vehicleType) { this->vehicleType = vehicleType; }
void Driver::setCurrentState(const string& currentState) { this->currentState = currentState; }
void Driver::setRiderFirstName(const string& riderFirstName) { this->riderFirstName = riderFirstName; }
void Driver::setRiderLastName(const string& riderLastName) { this->riderLastName = riderLastName; }
void Driver::setRiderPhoneNumber(const string& riderPhoneNumber) { this->riderPhoneNumber = riderPhoneNumber; }

// overload output steam operator
ostream& operator<<(ostream &out, const Driver &driver) {
  // print driver
}