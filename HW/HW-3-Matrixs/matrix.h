// matrix header
#ifndef MATRIX_H 
#define MATRIX_H

#include <iostream>

using namespace std;

class Matrix {
public:
    // Constructors and Destructor
    Matrix();
    Matrix(unsigned int rows, unsigned int cols, double fill);
    Matrix(const Matrix &other);
    ~Matrix();

    // Assignment Operator and Swapping
    Matrix& operator=(Matrix other);
    friend void swap(Matrix &m1, Matrix &m2);

    // Getters
    bool get(unsigned int x, unsigned int y, double &value) const;
    unsigned int num_rows() const;
    unsigned int num_cols() const;

    // Setters
    bool set(unsigned int x, unsigned int y, double value);

    // Utility Functions
    void clear();
    bool operator==(const Matrix &other) const;
    bool operator!=(const Matrix &other) const;

    // Matrix Arithmetic
    Matrix operator+(const Matrix &other) const;
    bool add(const Matrix &other);
    Matrix operator-(const Matrix &other) const;
    bool subtract(const Matrix &other);

    // Scalar Operations
    void multiply_by_coefficient(double a);

    // Row and Column Operations
    bool swap_row(unsigned int a, unsigned int b);
    void transpose();

    // Matrix Slicing
    double* get_row(unsigned int a) const;
    double* get_col(unsigned int a) const;
    Matrix* quarter() const;

private:
    unsigned int _rows;
    unsigned int _cols;
    double **arr;
};

// Stream Operator Overload
ostream& operator<<(ostream &out, const Matrix &mat);
#endif