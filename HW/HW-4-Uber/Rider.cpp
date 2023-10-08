#include "Rider.h"

using namespace std;

// default constructor
Rider::Rider()
: firstName(""), lastName(""), gender(""), age(0), phoneNumber(""), rating(""), 
  pickupLocationName(""), pickupLatitude(0.0), pickupLongitude(0.0),
  dropoffLocationName(""), dropoffLatitude(0.0), dropoffLongitude(0.0), 
  vehiclePreference(""), currentState(""), driverFirstName(""), 
  driverLastName(""), driverPhoneNumber("") {}

// constructor
Rider::Rider(const string& firstName,
             const string& lastName,
             const string& gender,
             int age,
             const string& phoneNumber,
             const string& rating,
             const string& pickupLocationName,
             double pickupLatitude,
             double pickupLongitude,
             const string& dropoffLocationName,
             double dropoffLatitude,
             double dropoffLongitude,
             const string& vehiclePreference,
             const string& currentState,
             const string& driverFirstName,
             const string& driverLastName,
             const string& driverPhoneNumber)
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

// copy constructor
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

// getters
string Rider::getFirstName() const { return firstName; }
string Rider::getLastName() const { return lastName; }
string Rider::getGender() const { return gender; }
int Rider::getAge() const { return age; }
string Rider::getPhoneNumber() const { return phoneNumber; }
string Rider::getRating() const { return rating; }
string Rider::getPickupLocationName() const { return pickupLocationName; }
double Rider::getPickupLatitude() const { return pickupLatitude; }
double Rider::getPickupLongitude() const { return pickupLongitude; }
string Rider::getDropoffLocationName() const { return dropoffLocationName; }
double Rider::getDropoffLatitude() const { return dropoffLatitude; }
double Rider::getDropoffLongitude() const { return dropoffLongitude; }
string Rider::getVehiclePreference() const { return vehiclePreference; }
string Rider::getCurrentState() const { return currentState; }
string Rider::getDriverFirstName() const { return driverFirstName; }
string Rider::getDriverLastName() const { return driverLastName; }
string Rider::getDriverPhoneNumber() const { return driverPhoneNumber; }

// setters
void Rider::setFirstName(const string& firstName) { this->firstName = firstName; }
void Rider::setLastName(const string& lastName) { this->lastName = lastName; }
void Rider::setGender(const string& gender) { this->gender = gender; }
void Rider::setAge(int age) { this->age = age; }
void Rider::setPhoneNumber(const string& phoneNumber) { this->phoneNumber = phoneNumber; }
void Rider::setRating(const string& rating) { this->rating = rating; }
void Rider::setPickupLocationName(const string& locationName) { this->pickupLocationName = locationName; }
void Rider::setPickupLatitude(double latitude) { this->pickupLatitude = latitude; }
void Rider::setPickupLongitude(double longitude) { this->pickupLongitude = longitude; }
void Rider::setDropoffLocationName(const string& locationName) { this->dropoffLocationName = locationName; }
void Rider::setDropoffLatitude(double latitude) { this->dropoffLatitude = latitude; }
void Rider::setDropoffLongitude(double longitude) { this->dropoffLongitude = longitude; }
void Rider::setVehiclePreference(const string& preference) { this->vehiclePreference = preference; }
void Rider::setCurrentState(const string& state) { this->currentState = state; }
void Rider::setDriverFirstName(const string& driverFirstName) { this->driverFirstName = driverFirstName; }
void Rider::setDriverLastName(const string& driverLastName) { this->driverLastName = driverLastName; }
void Rider::setDriverPhoneNumber(const string& driverPhoneNumber) { this->driverPhoneNumber = driverPhoneNumber; }

// overload output stream operator
ostream& operator<<(ostream &out, const Rider &rider) {
  // print rider
  out << rider.getFirstName() << ' ' << rider.getLastName() << ' ' << rider.getGender() << ' ' << rider.getAge() << ' ' << rider.getPhoneNumber() << ' ';
  out << rider.getRating() << ' ' << rider.getPickupLocationName() << ' ' << rider.getPickupLatitude() << ' ' << rider.getPickupLongitude() << ' ';
  out << rider.getDropoffLocationName() << ' ' << rider.getDropoffLatitude() << ' ' << rider.getDropoffLongitude() << ' ' << rider.getVehiclePreference() << ' ';
  out << rider.getCurrentState() << ' ' << rider.getDriverFirstName() << ' ' << rider.getDriverLastName() << ' ' << rider.getDriverPhoneNumber();

  return out;
}
