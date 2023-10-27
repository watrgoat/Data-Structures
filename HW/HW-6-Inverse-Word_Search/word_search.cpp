// includes
#include <iostream>
#include <fstream>
#include <vector>
#include "Board.h"

using namespace std;

// define all possible movement directions on the board.
const pair<int, int> DIRECTIONS[] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1}};

pair<int, int> ingest(ifstream &inputFile, vector<string> &positiveWords, vector<string> &negativeWords) {
    string first, second;
    int rows = 0;
    int cols = 0;
    bool is_dimension = true;
    while (inputFile >> first >> second) {
        // first line is dimensions
        if (is_dimension) {
            // get dimensions
            cols = stoi(first);
            rows = stoi(second);

            is_dimension = false;
        } else {
            
            // check if line is positive or negative
            if (first == "+") {
                positiveWords.push_back(second);
            } else {
                negativeWords.push_back(second);
            }
        }
    }
    return make_pair(rows, cols);
}

bool isPositionInBounds(const Board& board, const string& word, int x, int y, int dx, int dy) {
    return !(x < 0 || y < 0 ||
             x + (word.length() - 1)*dx >= board.numRows() ||
             x + (word.length() - 1)*dx < 0 ||
             y + (word.length() - 1)*dy >= board.numCols() ||
             y + (word.length() - 1)*dy < 0);
}

bool containsZeros(const Board& board) {
    for (int x = 0; x < board.numRows(); ++x) {
        for (int y = 0; y < board.numCols(); ++y) {
            if (board.get(x, y) == '0') {
                return true;
            }
        }
    }
    return false;
}

// This function checks if a word can be placed on the board 
// starting from coordinates (x, y) and moving in direction (dx, dy).
bool isWordPlaceable(const Board& board, const string& word, int x, int y, int dx, int dy) {
    if (!isPositionInBounds(board, word, x, y, dx, dy)) {
        return false;
    }

    // iterate through the word's characters and ensure the path on the board is '0'.
    for (size_t i = 0; i < word.length(); i++) {
        char currentCell = board.get(x + i*dx, y + i*dy);
        if (currentCell != '0' && currentCell != word[i]) {
            return false; // Cell is occupied by a different character than the current word's character.
        }
    }
    return true;
}


// This function places a word on the board starting from (x, y) and 
// moving in the direction (dx, dy) for each character in the word.
void placeWord(Board& board, const string& word, int x, int y, int dx, int dy) {
    for (int i = 0; i < word.length(); i++) {
        board.set(x + i*dx, y + i*dy, word[i]);
    }
}

// This function searches the board for any of the words provided in negativeWords.
// It returns true if any of the negative words are found.
bool searchNegativeWord(const Board& board, vector<string>& words, int x, int y, int dx, int dy, int index) {
    if (index == words.size()) return true;

    if (!isPositionInBounds(board, words[index], x, y, dx, dy)) return false;

    for (int i = 0; i < words.size(); i++) {
        if (index < words[i].length() && board.get(x, y) == words[i][index]) {
            if (index == words[i].length() - 1) return true; // found a negative word

            // continue searching in the current direction
            if (searchNegativeWord(board, words, x + dx, y + dy, dx, dy, index + 1)) {
                return true;
            }
        }
    }
    return false;
}

bool findNegativeWords(const Board& board, const vector<string>& negativeWords) {
    int numRows = board.numRows();
    int numCols = board.numCols();

    for (int x = 0; x < numRows; x++) {
        for (int y = 0; y < numCols; y++) {
            for (int dir = 0; dir < 8; dir++) {
                int dx = DIRECTIONS[dir].first;
                int dy = DIRECTIONS[dir].second;

                vector<string> tempWords = negativeWords; // make a copy of negative words for this iteration
                cout << "here" << endl;
                // start searching from position (x, y) in the current direction
                if (searchNegativeWord(board, tempWords, x, y, dx, dy, 0)) {
                    return true;
                }
            }
        }
    }
    return false;
}

bool isNegativeWordPresentFromPosition(const Board& board, const string& negativeWord, int x, int y, int dx, int dy) {
    for (size_t m = 0; m < negativeWord.length(); m++) {
        int checkX = x + m*dx;
        int checkY = y + m*dy;

        // If out of bounds or characters don't match, abort early
        if (checkX < 0 || checkX >= board.numRows() || checkY < 0 || checkY >= board.numCols() || board.get(checkX, checkY) != negativeWord[m]) {
            return false;
        }
    }
    return true;
}

bool checkForNegativeWordsAroundPosition(const Board& board, const vector<string>& negativeWords, int startX, int startY) {
    for (const string& negativeWord : negativeWords) {
        for (int dir = 0; dir < 8; dir++) {
            int dx = DIRECTIONS[dir].first;
            int dy = DIRECTIONS[dir].second;
            
            if (isNegativeWordPresentFromPosition(board, negativeWord, startX, startY, dx, dy)) {
                return true;
            }
        }
    }
    return false;
}

void fillWithCombinations(Board& board, int row, int col, const vector<string>& negativeWords, vector<Board>& solutions) {
    // If we've filled the entire board, check for negative words
    if (!containsZeros(board)) {
        if (!findNegativeWords(board, negativeWords)) { // can be made more efficient, but it's left as is for now
            solutions.push_back(board);
        }
        return;
    }

    // If this cell is empty ('0'), try to fill it with a letter
    if (board.get(row, col) == '0') {
        for (char letter = 'a'; letter <= 'z'; ++letter) {
            board.set(row, col, letter);
            
            // Check if a negative word has formed around this position. If it has, we can skip further exploration.
            if (!checkForNegativeWordsAroundPosition(board, negativeWords, row, col)) {
                // Determine the next row and column for recursive call
                int nextRow = (col == board.numCols() - 1) ? row + 1 : row;
                int nextCol = (col == board.numCols() - 1) ? 0 : col + 1;
                
                fillWithCombinations(board, nextRow, nextCol, negativeWords, solutions);
            }

            board.set(row, col, '0');  // Reset cell after trying all letters
        }
    } else {
        // Determine the next row and column for recursive call
        int nextRow = (col == board.numCols() - 1) ? row + 1 : row;
        int nextCol = (col == board.numCols() - 1) ? 0 : col + 1;

        fillWithCombinations(board, nextRow, nextCol, negativeWords, solutions);
    }
}


// This function attempts to fit all positive words onto the board, 
// while ensuring that none of the negative words appear.
// If a valid configuration is found, it's added to the solutions vector.
void backtrack(Board& board, const vector<string>& positiveWords, const vector<string>& negativeWords, int wordIndex, vector<Board>& solutions) {
    if (wordIndex == positiveWords.size()) {
        // Fill remaining cells with letter combinations
        // we know
        fillWithCombinations(board, 0, 0, negativeWords, solutions);
        return;
    }
    if (wordIndex > 0) {
        if (findNegativeWords(board, negativeWords)) { return; }
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
                    Board snap(board);
                    placeWord(board, positiveWords[wordIndex], x, y, dx, dy);
                    backtrack(board, positiveWords, negativeWords, wordIndex + 1, solutions);
                    board = snap;
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

bool fillWithCombinations(Board& board, int row, int col, const vector<string>& negativeWords) {
    // If we have reached the end of the board.
    if (row == board.numRows()) {
        return !findNegativeWords(board, negativeWords); // True if a valid board, False otherwise
    }

    // If we have reached the end of the column, move to the next row.
    if (col == board.numCols()) {
        return fillWithCombinations(board, row + 1, 0, negativeWords);
    }

    // If the cell is not '0', skip to the next cell without changing anything.
    if (board.get(row, col) != '0') {
        return fillWithCombinations(board, row, col + 1, negativeWords);
    }

    // If the cell is '0', try placing each of the letters and recurse.
    for (char letter = 'a'; letter <= 'z'; ++letter) {
        board.set(row, col, letter);
        if (!findNegativeWords(board, negativeWords) && fillWithCombinations(board, row, col + 1, negativeWords)) {
            return true;  // Found a valid board in the recursive call
        }
        // Undo the choice before trying the next letter (Backtrack)
        board.set(row, col, '0');
    }

    return false;  // No valid board found at this level
}

bool backtrackOne(Board& board, const vector<string>& positiveWords, const vector<string>& negativeWords, int wordIndex) {
    if (wordIndex == positiveWords.size()) {
        // Fill remaining cells with letter combinations
        return fillWithCombinations(board, 0, 0, negativeWords);
    }

    Board snap(board);
    for (int x = 0; x < board.numRows(); ++x) {
        for (int y = 0; y < board.numCols(); ++y) {
            for (int dir = 0; dir < 8; ++dir) {
                int dx = DIRECTIONS[dir].first;
                int dy = DIRECTIONS[dir].second;
                if (isWordPlaceable(board, positiveWords[wordIndex], x, y, dx, dy)) {
                    placeWord(board, positiveWords[wordIndex], x, y, dx, dy);
                    if (backtrackOne(board, positiveWords, negativeWords, wordIndex + 1)) {
                        return true;  // A valid solution has been found in the recursive call
                    }
                    board = snap;  // Reset board to previous state
                }
            }
        }
    }
    return false;  // No solution found at this level
}

Board createOnePuzzle(int rows, int cols, const vector<string>& positiveWords, const vector<string>& negativeWords) {
    Board board(rows, cols);
    backtrackOne(board, positiveWords, negativeWords, 0);

    return board;
}

void printAll(ofstream &out, vector<Board> solves) {
    out << solves.size() << " solution(s)" << endl;
    for (int i = 0; i < solves.size(); i++) {
        out << solves[i];
    }
}

void printOne(ofstream &out, Board solve) {
    out << solve;
}

int main(int argc, char* argv[]) {
    if (argc != 4) {
        cerr << "Usage: ./word_search <input_file> <output_file> <solution_type>" << endl;
        return 1;
    }

    // open input file
    ifstream input_file(argv[1]);
    if (!input_file.is_open()) {
        cerr << "Error: could not open file '" << argv[1] << "'." << endl;
        return 1;
    }
    
    // create data structure to store input file
    vector<string> positiveWords;
    vector<string> negativeWords;

    // ingest input file
    pair<int, int> dim = ingest(input_file, positiveWords, negativeWords);
    
    // close input file
    input_file.close();

    // open output file
    ofstream output_file(argv[2]);
    if (!output_file.is_open()) {
        cerr << "Error: could not open file '" << argv[2] << "'." << endl;
        return 1;
    }

    string solution_type = argv[3];
    if (solution_type == "all_solutions") {

        vector<Board> solves = createAllPuzzles(dim.first, dim.second, positiveWords, negativeWords);
        // print all solutions
        printAll(output_file, solves);

    } else if (solution_type == "one_solution") {
        Board solve = createOnePuzzle(dim.first, dim.second, positiveWords, negativeWords);

        // print one solution
        printOne(output_file, solve);
    } else {
        cerr << "Error: invalid solution type '" << solution_type << "'." << endl;
        return 1;
    }

    // close output file
    output_file.close();
    return 0;
}