// my test file
#include "Matrix.h"
#include <iostream>
#include <fstream>

using namespace std;

double intDiv(int a, int b) {
	double c = a;
	double d = b;
	return c/d;
}

int main() {
	int rows = 100;
	int cols = 5;

	Matrix m2(rows, cols, 1);

	m2.set(0, 0, 0);

	Matrix m1(m2);

	m1.set(0, 1, 2);

	cout << m2.num_cols() << endl;


	cout << m2 << m1 << endl;

	return 0;
}