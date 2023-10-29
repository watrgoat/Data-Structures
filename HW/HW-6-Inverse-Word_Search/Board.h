#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <ostream>

class Board {
public:
    Board(int rows, int cols); // Default constructor
    Board(const Board& other); // Copy constructor
    Board& operator=(const Board& other); // Assignment operator
    ~Board(); // Destructor

    // Getters
    char get(int row, int col) const;
    int numRows() const;
    int numCols() const;

    // Setters
    void set(int row, int col, char value);
    void clear();

    bool operator<(const Board& other) const;

private:
    std::vector<std::vector<char>>* board_;
    int rows_;
    int cols_;
};

std::ostream& operator<<(std::ostream& os, const Board& board);
bool operator==(const Board& b1, const Board& b2);

#endif // BOARD_H
