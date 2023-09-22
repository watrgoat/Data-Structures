// matrix.cpp
#include "matrix.h"
#include <iostream>

Matrix::Matrix(unsigned int m, unsigned int n, double fill) {
	if (m==0||n==0) {
		// empty arr
		_rows = 0;
		_cols = 0;
	} else {
		_rows = m;
		_cols = n;
	}

	// initializes array of input size

	// creates array of pointers of size _rows in the heap
	arr = new double*[_rows];
	for (int i=0; i<_rows; i++) {
		// creates array of doubles of size _cols in the heap
		arr[i] = new double[_cols];
	}

	// applys fill value
	for (int i=0; i<_rows; i++) {
		for (int j=0; j<_cols; j++) {
			arr[i][j] = fill;
		}
	}
}

bool Matrix::get(unsigned int x, unsigned int y) {
	return arr[x][y];
}