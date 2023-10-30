#include <iostream>
#include "Board.h"

// constructor
Board::Board(int rows, int cols) {
    board_ = new std::vector<std::vector<char>>(rows, std::vector<char>(cols, '0'));
    rows_ = rows;
    cols_ = cols;
}

// copy constructor
Board::Board(const Board& other) {
    board_ = new std::vector<std::vector<char>>(*other.board_);
    rows_ = other.rows_;
    cols_ = other.cols_;
}

// assignment operator
Board& Board::operator=(const Board& other) {
    if (this != &other) {
        delete board_;
        board_ = new std::vector<std::vector<char>>(*other.board_);
        rows_ = other.rows_;
        cols_ = other.cols_;
    }
    return *this;
}

// destructor
Board::~Board() {
    delete board_;
}

// gets value from board
char Board::get(int row, int col) const {
    if (row < 0 || row >= rows_ || col < 0 || col >= cols_) {
        std::cerr << "ERROR: get() out of bounds" << std::endl;
        return ' ';
    }
    return (*board_)[row][col];
}

// gets num of rows
int Board::numRows() const {
    return rows_;
}

// gets num of columns
int Board::numCols() const {
    return cols_;
}

// sets a value
void Board::set(int row, int col, char value) {
    if (row < 0 || row >= rows_ || col < 0 || col >= cols_) {
        std::cerr << "ERROR: set() out of bounds" << std::endl;
        return;
    }
    (*board_)[row][col] = value;
}

// reset the entire board to '0'
void Board::clear() {
    for (int i = 0; i < rows_; i++) {
        for (int j = 0; j < cols_; j++) {
            set(i, j, '0');
        }
    }
}

// compare two boards to see which one is less
// needed for storing boards in set
bool Board::operator<(const Board& other) const {
    for (int x = 0; x < numRows(); x++) {
        for (int y = 0; y < numCols(); y++) {
            if (get(x, y) != other.get(x, y)) {
                return get(x, y) < other.get(x, y);
            }
        }
    }
    return false;
}

// print out the board
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

// check if two boards are same
bool operator==(const Board& b1, const Board& b2) {
    if (b1.numRows() != b2.numRows() || b1.numCols() != b2.numCols()) {
        return false;
    }
    for (int i = 0; i < b1.numRows(); i++) {
        for (int j = 0; j < b1.numCols(); j++) {
            if (b1.get(i, j) != b2.get(i, j)) {
                return false;
            }
        }
    }
    // made here so all elements same
    return true;
}
