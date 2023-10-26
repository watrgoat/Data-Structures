#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <ostream>

class Board {
public:
    Board(int rows, int cols);
    ~Board(); // Destructor

    char get(int row, int col) const;
    void set(int row, int col, char value);
    int numRows() const;
    int numCols() const;

    void clear();

private:
    std::vector<std::vector<char>>* board_;
};

std::ostream& operator<<(std::ostream& os, const Board& board);

#endif // BOARD_H
