// matrix.cpp
#include "Matrix.h"
#include <iostream>
#include <algorithm>

using namespace std;

// NEED TO CHECK IF GET RETURNS TRUE

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

	// fills in the values from copied arr
	for (unsigned int i=0; i<_rows; i++) {
		for (unsigned int j=0; j<_cols; j++) {
			// no need to check if get returns true since it has copied size
			other.get(i, j, arr[i][j]);
		}
	}
}

// swap function to for assignment explained: https://stackoverflow.com/questions/3279543/what-is-the-copy-and-swap-idiom
void swap(Matrix &m1, Matrix &m2) {
	swap(m1._rows, m2._rows);
	swap(m1._cols, m2._cols);
	swap(m1.arr , m2.arr);
}

// assignment operator
Matrix& Matrix::operator=(Matrix other) {
	// swaps objs
	swap(*this, other);

	return *this;
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

// func to change value
bool Matrix::set(unsigned int x, unsigned int y, double value) {
	// not in range
	if (x>=_rows || y>=_cols) {
		return false;
	}

	arr[x][y] = value;
	return true;
}

void Matrix::clear() {
	for (unsigned int i=0; i<_rows; i++) {
		delete[] arr[i];
	}
	delete[] arr;

	_rows = 0;
	_cols = 0;

	arr = new double*[0];
}

// operator overload funcs
bool Matrix::operator==(const Matrix &other) const {
	// check sizes
	if (_rows!=other.num_rows() || _cols!=other.num_cols()) {
		return false;
	}
	double p;
	// check all squares
	for (unsigned int i=0; i<_rows; i++) {
		for (unsigned int j=0; j<_cols; j++) {
			other.get(i, j, p);
			if (arr[i][j] != p) {
				return false;
			}
		}
	}

	return true;
}

bool Matrix::operator!=(const Matrix &other) const {
	// check size
	if (_rows!=other.num_rows() || _cols!=other.num_cols()) {
		return true;
	}

	double p;
	// check all squares
	for (unsigned int i=0; i<_rows; i++) {
		for (unsigned int j=0; j<_cols; j++) {
			other.get(i, j, p);
			if (arr[i][j] != p) {
				return true;
			}
		}
	}
	
	return false;
}

Matrix Matrix::operator+(const Matrix &other) const {
	// check size
	if (_rows!=other.num_rows() || _cols!=other.num_cols()) {
		cerr << "ERROR: Invalid matrix input. Can't add inequal size matrices" << endl;
		exit(1);
	}

	// create a copy of 1 matrix and add second values
	Matrix mat(other);
	double p;

	for (unsigned int i=0; i<_rows; i++) {
		for (unsigned int j=0; j<_cols; j++) {
			other.get(i, j, p);
			mat.set(i, j, (arr[i][j]+p));
		}
	}

	return mat;
}

bool Matrix::add(const Matrix &other) {
	// check size
	if (_rows!=other.num_rows() || _cols!=other.num_cols()) {
		// inequal sized matrix
		return false;
	}

	double p;

	for (unsigned int i=0; i<_rows; i++) {
		for (unsigned int j=0; j<_cols; j++) {
			other.get(i, j, p);
			arr[i][j] = (arr[i][j]+p);
		}
	}

	return true;
}

Matrix Matrix::operator-(const Matrix &other) const {
		// check size
	if (_rows!=other.num_rows() || _cols!=other.num_cols()) {
		cerr << "ERROR: Invalid matrix input. Can't subtract inequal size matrices" << endl;
		exit(1);
	}

	// create a copy of 1 matrix and add second values
	Matrix mat(other);
	double p;

	for (unsigned int i=0; i<_rows; i++) {
		for (unsigned int j=0; j<_cols; j++) {
			other.get(i, j, p);
			mat.set(i, j, (arr[i][j]-p));
		}
	}

	return mat;
}

bool Matrix::subtract(const Matrix &other) {
	// check size
	if (_rows!=other.num_rows() || _cols!=other.num_cols()) {
		// inequal sized matrix
		return false;
	}

	double p;

	for (unsigned int i=0; i<_rows; i++) {
		for (unsigned int j=0; j<_cols; j++) {
			other.get(i, j, p);
			arr[i][j] = (arr[i][j]-p);
		}
	}

	return true;
}

ostream& operator<<(ostream &out, const Matrix &mat) {
	double p;

	out << endl;
	out << mat.num_rows() << " x " << mat.num_cols() << " matrix:" << endl;
	out << '[';

	for (unsigned int i=0; i<mat.num_rows(); i++) {
		for (unsigned int j=0; j<mat.num_cols(); j++) {
			mat.get(i, j, p);
			out << ' ' << p;
		}
		if (i!=mat.num_rows()-1) {
			out << endl << ' ';
		}
	}

	out << " ]" << endl;

	return out;
}

void Matrix::multiply_by_coefficient(double a) {
	for (unsigned int i=0; i<_rows; i++) {
		for (unsigned int j=0; j<_cols; j++) {
			// multiply by coef
			arr[i][j] *= a;
		}
	}
}

bool Matrix::swap_row(unsigned int a, unsigned int b) {
	// check size
	if (a>=_rows && b>=_rows) {
		return false;
	}

	double *row1 = arr[a];
	arr[a] = arr[b];
	arr[b] = row1;
	return true;
}

void Matrix::transpose() {
	// early return for small matrices
	if (_rows<=1 && _cols<=1) {
		return;
	}

	// create temp matrix with swapped row and column values
	Matrix temp(_cols, _rows, 0);

	for (unsigned int i=0; i<_rows; i++) {
		for (unsigned int j=0; j<_cols; j++) {
			temp.set(j, i, arr[i][j]);
		}
	}

	swap(*this, temp);
}

double* Matrix::get_row(unsigned int a) const {
	if (a>=_rows) {
		return nullptr;
	}

	// stores column array in heap
	// MUST DELETE AFTER CALLED
	double *row = new double[_cols];
	
	// adds rows elements to array
	for (unsigned int i=0; i<_cols; i++) {
		row[i] = arr[a][i];
	}

	return row;
}

double* Matrix::get_col(unsigned int a) const {
	// return pointer with variable row????
	if (a>=_cols) {
		return nullptr;
	}

	// stores column array in heap
	// MUST DELETE AFTER CALLED
	double *column = new double[_rows];

	// adds column elements to array
	for (unsigned int i=0; i<_rows; i++) {
		column[i] = arr[i][a];
	}

	return column;
}

Matrix* Matrix::quarter() const {
	// check if empty

	// how to find height and width
	unsigned int cut_row = (_rows+1)/2;
	unsigned int cut_col = (_cols+1)/2;

	Matrix* quarters = new Matrix[4]{
        Matrix(cut_row, cut_col, 0),
        Matrix(cut_row, cut_col, 0),
        Matrix(cut_row, cut_col, 0),
        Matrix(cut_row, cut_col, 0)
    };


    // early return for empty matrix
    if (_rows==0 || _cols==0) {
		return quarters;
	}

	
	for (unsigned int i=0; i<cut_row; i++) {
		for (unsigned int j=0; j<cut_col; j++) {
			// upper left
			quarters[0].set(i, j, arr[i][j]);
			// upper right
			quarters[1].set(i, j, arr[i][j + _cols/2]);
			// lower left
			quarters[2].set(i, j, arr[i + _rows/2][j]);
			// lower right
			quarters[3].set(i, j, arr[i + _rows/2][j + _cols/2]);
		}
	}

    return quarters;
}