#include "board.h"

Board::Board(int rows, int cols) {
    board_ = new std::vector<std::vector<char>>(rows, std::vector<char>(cols, '0'));
}

Board::~Board() {
    delete board_;
}

// O(1) time
char Board::get(int row, int col) const {
    return (*board_)[row][col];
}

// O(1) time
void Board::set(int row, int col, char value) {
    (*board_)[row][col] = value;
}

// O(1) time
int Board::numRows() const {
    return board_->size();
}

// O(1) time
int Board::numCols() const {
    // cant check board[0] if empty, undefined behavior
    return board_->empty() ? 0 : (*board_)[0].size();
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