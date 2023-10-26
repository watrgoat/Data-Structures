#include <iostream>
#include "Board.h"

Board::Board(int rows, int cols) {
    board_ = new std::vector<std::vector<char>>(rows, std::vector<char>(cols, '0'));
}

Board::~Board() {
    delete board_;
}

// Get board value in O(1) time
char Board::get(int row, int col) const {
    if (row < 0 || row >= numRows() || col < 0 || col >= numCols()) {
        std::cerr << "ERROR: get() out of bounds" << std::endl;
        return ' ';
    }
    return (*board_)[row][col];
}

// Set board value in O(1) time
void Board::set(int row, int col, char value) {
    if (row < 0 || row >= numRows() || col < 0 || col >= numCols()) {
        std::cerr << "ERROR: set() out of bounds" << std::endl;
        return;
    }
    (*board_)[row][col] = value;
}

// Return number of rows in O(1) time
int Board::numRows() const {
    return board_->size();
}

// Return number of columns in O(1) time
int Board::numCols() const {
    // cant check board[0] if empty, undefined behavior
    return board_->empty() ? 0 : (*board_)[0].size();
}

void Board::clear() {
    for (int i = 0; i < numRows(); i++) {
        for (int j = 0; j < numCols(); j++) {
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