// my test file
#include "matrix.h"
#include <iostream>

using namespace std;

double intDiv(int a, int b) {
	double c = a;
	double d = b;
	return c/d;
}

int main() {
	int rows = 10;
	int cols = 5;

	Matrix m1(rows, cols, 1);
	Matrix m2;

	cout << m2.num_rows() << endl;


	double p;

	m2.get(0, 0, p);

	cout << p << endl;
	cout << '[';

	for (int i=0; i<m1.num_rows(); i++) {
		for (int j=0; j<m1.num_cols(); j++) {
			m1.get(i, j, p);
			cout << ' ' << p;
		}
		if (i!=rows-1) {
			cout << endl << ' ';
		}
	}

	cout << " ]" << endl;


	// Matrix *myMatrix = new Matrix(arr);

	return 0;
}