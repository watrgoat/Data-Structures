// matrix.cpp
#include "matrix.h"
#include <iostream>

// default constructor
Matrix::Matrix() {
	_rows = 0;
	_cols = 0;
	arr = new double*[_rows];
}

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
	for (unsigned int i=0; i<_rows; i++) {
		// creates array of doubles of size _cols in the heap
		arr[i] = new double[_cols];
	}

	// applys fill value
	for (unsigned int i=0; i<_rows; i++) {
		for (unsigned int j=0; j<_cols; j++) {
			arr[i][j] = fill;
		}
	}
}

// copy constructor
Matrix::Matrix(const Matrix &other) {
	_rows = other.num_rows();
	_cols = other.num_cols();

	arr = new double*[_rows];
	for (unsigned int i=0; i<_rows; i++) {
		// creates array of doubles of size _cols in the heap
		arr[i] = new double[_cols];
	}

	// fills in the values
	for (unsigned int i=0; i<_rows; i++) {
		for (unsigned int j=0; j<_cols; j++) {
			other.get(i, j, arr[i][j]);
		}
	}
}

// destructor
Matrix::~Matrix() {
	for (unsigned int i=0; i<_rows; i++) {
		delete[] arr[i];
	}
	delete[] arr;
}

// function to access 
bool Matrix::get(unsigned int x, unsigned int y, double &value) const {
	// not in range
	if (x>=_rows || y>=_cols) {
		return false;
	}
	value = arr[x][y];
	return true;
}

unsigned int Matrix::num_rows() const {
	return _rows;
}

unsigned int Matrix::num_cols() const {
	return _cols;
}