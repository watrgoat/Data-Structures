#include "all_solutions.h"
#include "Board.h"
#include <vector>

void fillWithCombinations(Board& board, int row, int col, const vector<string>& negativeWords, vector<Board>& solutions) {
    if (row == board.numRows() - 1 && col == board.numCols()) {
        if (!findNegativeWords(board, negativeWords)) {
            solutions.push_back(board);
        }
        return;
    }

    if (board.get(row, col) == '0') {
        for (char letter = 'a'; letter <= 'z'; ++letter) {
            board.set(row, col, letter);
            if (col == board.numCols() - 1) {
                fillWithCombinations(board, row + 1, 0, negativeWords, solutions);
            } else {
                fillWithCombinations(board, row, col + 1, negativeWords, solutions);
            }
            board.set(row, col, '0');  // reset cell after trying all letters
        }
    } else {
        if (col == board.numCols() - 1) {
            fillWithCombinations(board, row + 1, 0, negativeWords, solutions);
        } else {
            fillWithCombinations(board, row, col + 1, negativeWords, solutions);
        }
    }
}

// This function attempts to fit all positive words onto the board, 
// while ensuring that none of the negative words appear.
// If a valid configuration is found, it's added to the solutions vector.
void backtrack(Board& board, const vector<string>& positiveWords, const vector<string>& negativeWords, int wordIndex, vector<Board>& solutions) {
    if (wordIndex == positiveWords.size()) {
        fillWithCombinations(board, 0, 0, negativeWords, solutions);
        return;
    }

    // iterate over the board's rows
    for (int x = 0; x < board.numRows(); ++x) {
        // iterate over the board's columns
        for (int y = 0; y < board.numCols(); ++y) {
            // iterate over the possible movement directions
            for (int dir = 0; dir < 8; ++dir) {
                int dx = DIRECTIONS[dir].first;
                int dy = DIRECTIONS[dir].second;
                if (isWordPlaceable(board, positiveWords[wordIndex], x, y, dx, dy)) {
                    placeWord(board, positiveWords[wordIndex], x, y, dx, dy);
                    backtrack(board, positiveWords, negativeWords, wordIndex + 1, solutions);
                    removeWord(board, positiveWords[wordIndex], x, y, dx, dy);
                }
            }
        }
    }
}

vector<Board> createAllPuzzles(int rows, int cols, const vector<string>& positiveWords, const vector<string>& negativeWords) {
    Board board(rows, cols);
    vector<Board> solutions;
    backtrack(board, positiveWords, negativeWords, 0, solutions);
    
    return solutions;
}