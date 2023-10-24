#include <iostream>

using namespace std;

class MyClass {
public:
	ostream& operator<<(ostream& os) {
		os << "Hello world!";
		return os;
	}
};

int main() {
	MyClass obj;
	obj.operator<<(cout);
}