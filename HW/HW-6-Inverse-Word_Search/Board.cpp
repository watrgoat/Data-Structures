#include <iostream>
#include "Board.h"

Board::Board(int rows, int cols) {
    board_ = new std::vector<std::vector<char>>(rows, std::vector<char>(cols, '0'));
    rows_ = rows;
    cols_ = cols;
}

// Copy constructor
Board::Board(const Board& other) {
    board_ = new std::vector<std::vector<char>>(*other.board_);
    rows_ = other.rows_;
    cols_ = other.cols_;
}

// Assignment operator
Board& Board::operator=(const Board& other) {
    if (this != &other) {
        delete board_;
        board_ = new std::vector<std::vector<char>>(*other.board_);
        rows_ = other.rows_;
        cols_ = other.cols_;
    }
    return *this;
}

Board::~Board() {
    delete board_;
}

// Get board value in O(1) time
char Board::get(int row, int col) const {
    if (row < 0 || row >= rows_ || col < 0 || col >= cols_) {
        std::cerr << "ERROR: get() out of bounds" << std::endl;
        return ' ';
    }
    return (*board_)[row][col];
}

// Return number of rows in O(1) time
int Board::numRows() const {
    return rows_;
}

// Return number of columns in O(1) time
int Board::numCols() const {
    // cant check board[0] if empty, undefined behavior
    return cols_;
}

// Set board value in O(1) time
void Board::set(int row, int col, char value) {
    if (row < 0 || row >= rows_ || col < 0 || col >= cols_) {
        std::cerr << "ERROR: set() out of bounds" << std::endl;
        return;
    }
    (*board_)[row][col] = value;
}

void Board::clear() {
    for (int i = 0; i < rows_; i++) {
        for (int j = 0; j < cols_; j++) {
            set(i, j, '0');
        }
    }
}

std::ostream& operator<<(std::ostream& os, const Board& board) {
    os << "Board: " << std::endl;
    for (int i = 0; i < board.numRows(); i++) {
        os << "  ";
        for (int j = 0; j < board.numCols(); j++) {
            os << board.get(i, j);
        }
        os << std::endl;
    }
    return os;
}