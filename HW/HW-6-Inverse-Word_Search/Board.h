#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <ostream>

class Board {
public:
    Board(int rows, int cols);
    ~Board(); // Destructor

    char getChar(int row, int col) const;
    void setChar(int row, int col, char value);
    int getRows() const;
    int getCols() const;

private:
    std::vector<std::vector<char>>* board_;
};

std::ostream& operator<<(std::ostream& os, const Board& board);

#endif // BOARD_H