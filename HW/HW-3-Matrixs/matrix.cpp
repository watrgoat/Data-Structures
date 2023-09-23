// matrix.cpp
#include "matrix.h"
#include <iostream>

// constructor
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

// destructor
Matrix::~Matrix() {
	for (int i=0; i<_rows; i++) {
		delete[] arr[i];
	}
	delete[] arr;
}

// function to access 
bool Matrix::get(unsigned int x, unsigned int y, double &value) {
	// not in range
	if (x>=_rows || y>=_cols) {
		return false;
	}
	value = arr[x][y];
	return true;
}