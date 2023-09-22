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

	cout << "[";

	for (int i=0;i<rows;i++) {
		for (int j=0;j<cols;j++) {
			cout << ' ' << arr[i][j];
		}
		if (i==rows-1) {
			continue;
		}
		cout << endl;
		cout << ' ';
	}
	cout << " ]" << endl;

	// Matrix *myMatrix = new Matrix(arr);

	return 0;
}