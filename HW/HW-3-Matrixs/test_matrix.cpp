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

	double arr[rows][cols];

	for (int i=0;i<rows;i++) {
		for (int j=1;j<cols+1;j++) {
			arr[i][j] = intDiv(i, j);
		}
	}

	Matrix m1(rows, cols, 1);
	double p;

	cout << '[';

	for (int i=0; i<rows; i++) {
		for (int j=0; j<cols; j++) {
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