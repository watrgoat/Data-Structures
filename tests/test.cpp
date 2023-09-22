#include <iostream>

using namespace std;

int main() {
	int *p = new int;
	*p = 10;
	int *q = p;
	cout << p << " " << q << endl;
	p = new int;
	*p = 1;
	cout << *p << " " << *q << endl;
}