#include <iostream>
#include <string>
#include <list>


template <class T>
void print(std::list<T> &data, const std::string &label) {
  std::cout << label << " ";
  typename std::list<T>::iterator it;
  for (it = data.begin(); it!=data.end(); it++) {
    std::cout << " " << *it;
  }
  std::cout << std::endl;
}


template <class T>
void reverse(std::list<T> &data) {
  // FILL IN THIS FUNCTION
  // loop over half the list and swap all values inside
  // two pointers. 1 at end, 1 at begin
  typename std::list<T>::iterator it = data.end();
  while (it!=data.begin()) {
    T tmp = data.front();
    data.pop_front();
    data.insert(it, tmp);
    it--;
  }
}


int main() {
  std::list<int> data;
  data.push_back(1);
  data.push_back(2);
  data.push_back(3);
  data.push_back(4);
  data.push_back(5);
  data.push_back(6);
  data.push_back(7);
  data.push_back(8);

  print(data,"before:");
  reverse(data);
  print(data,"after: ");

  std::list<std::string> data2;
  data2.push_back("apple");
  data2.push_back("banana");
  data2.push_back("carrot");
  data2.push_back("date");

  print(data2,"before:");
  reverse(data2);
  print(data2,"after: ");
}
