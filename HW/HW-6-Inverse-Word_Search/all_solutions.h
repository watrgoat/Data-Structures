#ifndef ALL_SOLUTIONS_H
#define ALL_SOLUTIONS_H

void fillWithCombinations(Board& board, int row, int col, const vector<string>& negativeWords, vector<Board>& solutions);
void backtrack(Board& board, const vector<string>& positiveWords, const vector<string>& negativeWords, int wordIndex, vector<Board>& solutions);
vector<Board> createAllPuzzles(int rows, int cols, const vector<string>& positiveWords, const vector<string>& negativeWords);

#endif // ALL_SOLUTIONS_H