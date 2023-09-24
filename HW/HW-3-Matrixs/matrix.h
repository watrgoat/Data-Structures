// matrix header
#ifndef MATRIX_H 
#define MATRIX_H

class Matrix {
public:
	// default constructor
	Matrix();

	// constructor
	Matrix(unsigned int rows, unsigned int cols, double fill);

	// copy constructor
	Matrix(const Matrix &other);

	// destructor
	~Matrix();

	// GETTERS
	bool get(unsigned int x, unsigned int y, double &value) const; 
	unsigned int num_rows() const;
	unsigned int num_cols() const;

	// SETTERS
	void set(unsigned int x, unsigned int y, double &value) const;

	void clear(); // reset num of rows and cols to 0 and deallocate all memory

	Matrix operator==(const Matrix &other) const;
	Matrix operator!=(const Matrix &other) const;
	Matrix operator+(const Matrix &other) const;
	Matrix operator-(const Matrix &other) const;
	Matrix operator<<(const Matrix &other) const;
private:
	unsigned int _rows;
	unsigned int _cols;
	double **arr;
};

#endif