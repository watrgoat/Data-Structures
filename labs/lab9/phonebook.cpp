// A simple "caller ID" program

#include <iostream>
#include <vector>
#include <string>
#include <map>
using namespace std;

// add a number, name pair to the phonebook
void add(map<int, string> &phonebook, int number, string const& name) {
  phonebook[number] = name;
}

// given a phone number, determine who is calling
void identify(map<int, string> & phonebook, int number) {
  // check if default behavior is to return empty string
  if (phonebook[number] == "") 
    cout << "unknown caller!" << endl;
  else 
    cout << phonebook[number] << " is calling!" << endl;
}


int main() {
  // create the phonebook; initially all numbers are unassigned
  map<int, string> phonebook;

  // add several names to the phonebook
  add(phonebook, 9873987, "fred");
  add(phonebook, 2222, "sally");
  add(phonebook, 3333, "george");

  // test the phonebook
  identify(phonebook, 9873987);
  identify(phonebook, 4444);
}

// analyze the code
// add func has a time complexity of O(m), since vector is already initialized, but need to assign name of size m (string copy)
// O(size of names x max phone size) space, but still bad, since we initialize a ton of space for the vector, even if we don't use it

// identify func has a time complexity of O(m), since vector is already initialized, and just need to access the string at index number

// new functions have same time complexity, but MUCH less space complexity
