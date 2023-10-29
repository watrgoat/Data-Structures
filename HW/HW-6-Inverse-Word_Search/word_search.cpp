// includes
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <set>
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

// Helper function to check if the board contains any word from the negativeWords list
bool containsNegativeWord(const Board& board, const vector<string>& negativeWords) {
    for (const string& word : negativeWords) {
        for (int x = 0; x < board.numRows(); x++) {
            for (int y = 0; y < board.numCols(); y++) {
                for (int dx = -1; dx <= 1; dx++) {
                    for (int dy = -1; dy <= 1; dy++) {
                        if (dx == 0 && dy == 0) continue;

                        if (isWordPlaceable(board, word, x, y, dx, dy)) {
                            return true;
                        }
                    }
                }
            }
        }
    }
    return false;
}

void fillRemainingSpaces(Board& board, const vector<string>& positiveWords, const vector<string>& negativeWords, set<Board>& solutions, int startX = 0, int startY = 0, char minChar = 'a') {
    // Find the first '0' character starting from (startX, startY)
    int zeroX = -1, zeroY = -1;
    bool found = false;
    for (int x = startX; x < board.numRows() && !found; x++) {
        for (int y = (x == startX ? startY : 0); y < board.numCols() && !found; y++) {
            if (board.get(x, y) == '0') {
                zeroX = x;
                zeroY = y;
                found = true;
            }
        }
    }

    // If no '0' character is found, add the board to solutions if it doesn't contain negative words
    if (!found) {
        if (!containsNegativeWord(board, negativeWords)) {
            solutions.insert(board);
        }
        return;
    }

    // Try filling the found '0' character with every character from 'minChar' to 'z'
    for (char ch = minChar; ch <= 'z'; ch++) {
        board.set(zeroX, zeroY, ch);
        if (zeroY < board.numCols() - 1) {
            // If not the last cell in the current row, move to the next cell in the same row
            fillRemainingSpaces(board, positiveWords, negativeWords, solutions, zeroX, zeroY + 1, ch);
        } else {
            // If the last cell in the current row, move to the first cell of the next row
            fillRemainingSpaces(board, positiveWords, negativeWords, solutions, zeroX + 1, 0, ch);
        }
    }
    board.set(zeroX, zeroY, '0');  // Restore the board for backtracking
}

void driver(Board& board, const vector<string>& positiveWords, const vector<string>& negativeWords, int wordIndex, set<Board>& solutions) {
    // Base case: if all words have been placed and there are no '0's left
    if (wordIndex == positiveWords.size()) {
        if (containsZeros(board)) {
            // If there are '0' characters, try filling them up
            fillRemainingSpaces(board, positiveWords, negativeWords, solutions);
        } else if (!containsNegativeWord(board, negativeWords)) {
            // If there are no '0' characters, add the board to solutions
            solutions.insert(board);
        }
        return;
    }
    
    string currentWord = positiveWords[wordIndex];
    
    // Try placing the current word in every possible position and direction
    for (int x = 0; x < board.numRows(); x++) {
        for (int y = 0; y < board.numCols(); y++) {
            for (int dx = -1; dx <= 1; dx++) {
                for (int dy = -1; dy <= 1; dy++) {
                    // Skip the case where dx = dy = 0 as it's not a valid direction
                    if (dx == 0 && dy == 0) continue;

                    if (isWordPlaceable(board, currentWord, x, y, dx, dy)) {
                        Board boardCopy = board;  // Store a copy of the current board state
                        placeWord(board, currentWord, x, y, dx, dy);
                        driver(board, positiveWords, negativeWords, wordIndex + 1, solutions);
                        board = boardCopy;  // Restore the board to its previous state
                    }
                }
            }
        }
    }
}

set<Board> createAllPuzzles(int rows, int cols, const vector<string>& positiveWords, const vector<string>& negativeWords) {
    Board board(rows, cols);
    set<Board> solutions;
    driver(board, positiveWords, negativeWords, 0, solutions);
    
    return solutions;
}

void printAll(ofstream &out, set<Board> solves) {
    if (solves.size() == 0) {
        out << "No solutions found" << endl;
        return;
    }

    out << solves.size() << " solution(s)" << endl;
    for (set<Board>::iterator it = solves.begin(); it != solves.end(); it++) {
        out << *it;
    }
}

void printOne(ofstream &out, Board solve) {
    if (containsZeros(solve)) {
        out << "No solutions found" << endl;
        return;
    }
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

        set<Board> solves = createAllPuzzles(dim.first, dim.second, positiveWords, negativeWords);
        // print all solutions
        printAll(output_file, solves);

    } else if (solution_type == "one_solution") {
        Board solve = *createAllPuzzles(dim.first, dim.second, positiveWords, negativeWords).begin();

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