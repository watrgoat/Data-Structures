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
	int rows = 5;
	int cols = 5;

	Matrix m2(rows, cols, 1);

	m2.set(0, 0, 0);

	Matrix m1 = m2;

	cout << m1.num_rows() << ' ' << m2.num_rows() << endl;

	cout << m1.num_cols() << ' ' << m2.num_cols() << endl;

	cout << (m1 == m2) << endl;

	m1.set(0, 1, 2);

	cout << (m1 == m2) << endl;


	cout << m2 << m1 << endl;



	return 0;
}