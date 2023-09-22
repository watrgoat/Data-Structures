// matrix header
#ifndef MATRIX_H 
#define MATRIX_H

class Matrix {
public:
	Matrix(unsigned int rows, unsigned int cols, double fill);

	// GETTERS
	// how to get row and col?
	double point(unsigned int x, unsigned int y) const; 
	unsigned int num_rows() const;
	unsigned int num_cols() const;

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