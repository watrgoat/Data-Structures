// matrix header
#ifndef MATRIX_H 
#define MATRIX_H

class Matrix {
public:
	// constructor
	Matrix(unsigned int rows, unsigned int cols, double fill);

	// destructor
	~Matrix();

	// GETTERS
	// how to get row and col?
	bool get(unsigned int x, unsigned int y, double &value) const; 
	unsigned int num_rows() const; // return _rows
	unsigned int num_cols() const; // return _cols

	void clear(); // reset num of rows and cols to 0 and deallocate all memory

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