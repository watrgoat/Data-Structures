#include "Rider.h"

Rider::Rider()
: firstName(""), lastName(""), gender(""), age(0), phoneNumber(""), rating(""), 
  pickupLocationName(""), pickupLatitude(0.0), pickupLongitude(0.0),
  dropoffLocationName(""), dropoffLatitude(0.0), dropoffLongitude(0.0), 
  vehiclePreference(""), currentState(""), driverFirstName(""), 
  driverLastName(""), driverPhoneNumber("") {}

Rider::Rider(const std::string& firstName,
             const std::string& lastName,
             const std::string& gender,
             int age,
             const std::string& phoneNumber,
             const std::string& rating,
             const std::string& pickupLocationName,
             double pickupLatitude,
             double pickupLongitude,
             const std::string& dropoffLocationName,
             double dropoffLatitude,
             double dropoffLongitude,
             const std::string& vehiclePreference,
             const std::string& currentState,
             const std::string& driverFirstName,
             const std::string& driverLastName,
             const std::string& driverPhoneNumber)
          : firstName(firstName),
            lastName(lastName),
            gender(gender),
            age(age),
            phoneNumber(phoneNumber),
            rating(rating),
            pickupLocationName(pickupLocationName),
            pickupLatitude(pickupLatitude),
            pickupLongitude(pickupLongitude),
            dropoffLocationName(dropoffLocationName),
            dropoffLatitude(dropoffLatitude),
            dropoffLongitude(dropoffLongitude),
            vehiclePreference(vehiclePreference),
            currentState(currentState),
            driverFirstName(driverFirstName),
            driverLastName(driverLastName),
            driverPhoneNumber(driverPhoneNumber) {}

Rider::Rider(const Rider& other) {
  firstName = other.getFirstName();
  lastName = other.getLastName();
  gender = other.getGender();
  age = other.getAge();
  phoneNumber = other.getPhoneNumber();
  rating = other.getRating();
  pickupLocationName = other.getPickupLocationName();
  pickupLatitude = other.getPickupLatitude();
  pickupLongitude = other.getPickupLongitude();
  dropoffLocationName = other.getDropoffLocationName();
  dropoffLatitude = other.getDropoffLatitude();
  dropoffLongitude = other.getDropoffLongitude();
  vehiclePreference = other.getVehiclePreference();
  currentState = other.getCurrentState();
  driverFirstName = other.getDriverFirstName();
  driverLastName = other.getDriverLastName();
  driverPhoneNumber = other.getDriverPhoneNumber(); }

std::string Rider::getFirstName() const { return firstName; }
std::string Rider::getLastName() const { return lastName; }
std::string Rider::getGender() const { return gender; }
int Rider::getAge() const { return age; }
std::string Rider::getPhoneNumber() const { return phoneNumber; }
std::string Rider::getRating() const { return rating; }
std::string Rider::getPickupLocationName() const { return pickupLocationName; }
double Rider::getPickupLatitude() const { return pickupLatitude; }
double Rider::getPickupLongitude() const { return pickupLongitude; }
std::string Rider::getDropoffLocationName() const { return dropoffLocationName; }
double Rider::getDropoffLatitude() const { return dropoffLatitude; }
double Rider::getDropoffLongitude() const { return dropoffLongitude; }
std::string Rider::getVehiclePreference() const { return vehiclePreference; }
std::string Rider::getCurrentState() const { return currentState; }
std::string Rider::getDriverFirstName() const { return driverFirstName; }
std::string Rider::getDriverLastName() const { return driverLastName; }
std::string Rider::getDriverPhoneNumber() const { return driverPhoneNumber; }

void Rider::setFirstName(const std::string& firstName) { this->firstName = firstName; }
void Rider::setLastName(const std::string& lastName) { this->lastName = lastName; }
void Rider::setGender(const std::string& gender) { this->gender = gender; }
void Rider::setAge(int age) { this->age = age; }
void Rider::setPhoneNumber(const std::string& phoneNumber) { this->phoneNumber = phoneNumber; }
void Rider::setRating(const std::string& rating) { this->rating = rating; }
void Rider::setPickupLocationName(const std::string& locationName) { this->pickupLocationName = locationName; }
void Rider::setPickupLatitude(double latitude) { this->pickupLatitude = latitude; }
void Rider::setPickupLongitude(double longitude) { this->pickupLongitude = longitude; }
void Rider::setDropoffLocationName(const std::string& locationName) { this->dropoffLocationName = locationName; }
void Rider::setDropoffLatitude(double latitude) { this->dropoffLatitude = latitude; }
void Rider::setDropoffLongitude(double longitude) { this->dropoffLongitude = longitude; }
void Rider::setVehiclePreference(const std::string& preference) { this->vehiclePreference = preference; }
void Rider::setCurrentState(const std::string& state) { this->currentState = state; }
void Rider::setDriverFirstName(const std::string& driverFirstName) { this->driverFirstName = driverFirstName; }
void Rider::setDriverLastName(const std::string& driverLastName) { this->driverLastName = driverLastName; }
void Rider::setDriverPhoneNumber(const std::string& driverPhoneNumber) { this->driverPhoneNumber = driverPhoneNumber; }