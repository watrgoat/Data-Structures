// matrix header
#ifndef MATRIX_H 
#define MATRIX_H

class Matrix {
public:
	Matrix(unsigned int rows, unsigned int cols, double fill);

	// GETTERS
	// how to get row and col?
	double point(unsigned int x, unsigned int y) const; 
	unsigned int num_rows() const; // return _rows
	unsigned int num_cols() const; // return _cols

	void clear(); // reset num of rows and cols to 0

	Matrix operator==(const Matrix &other) const;
	Matrix operator!=(const Matrix &other) const;
	Matrix operator+(const Matrix &other) const;
	Matrix operator-(const Matrix &other) const;
private:
	unsigned int _rows;
	unsigned int _cols;
	double **arr;
}

#endif