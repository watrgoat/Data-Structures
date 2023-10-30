// includes
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <set>
#include "Board.h"

using namespace std;

// all possible movement directions on the board
const pair<int, int> DIRECTIONS[] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1}};

// ingest the file
pair<int, int> ingest(ifstream &inputFile, vector<string> &positiveWords, vector<string> &negativeWords) {
    // first two items are always board dimensions
    int width, height;
    inputFile >> width >> height;

    // read in the pos and neg words
    string sign, word;
    while (inputFile >> sign >> word) {
        // check if pos or neg
        if (sign == "+") {
            positiveWords.push_back(word);
        } else {
            negativeWords.push_back(word);
        }
    }
    return make_pair(height, width);
}

// checks if the word will fit inside the bounds of the current board
bool wordFits(const Board& board, const string& word, int x, int y, int dx, int dy) {
    return !(x < 0 || y < 0 ||
             x + (int(word.length()) - 1)*dx >= board.numRows() ||
             x + (int(word.length()) - 1)*dx < 0 ||
             y + (int(word.length()) - 1)*dy >= board.numCols() ||
             y + (int(word.length()) - 1)*dy < 0);
}

// check if board contains any empty values
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

// checks if a word can be placed on the board
bool isWordPlaceable(const Board& board, const string& word, int x, int y, int dx, int dy) {
    // if word doesnt fit return
    if (!wordFits(board, word, x, y, dx, dy)) {
        return false;
    }

    // if word will overlap another without the same characters
    for (size_t i = 0; i < word.length(); i++) {
        char currentCell = board.get(x + i*dx, y + i*dy);
        if (currentCell != '0' && currentCell != word[i]) {
            return false;
        }
    }
    return true;
}

// places a word in the board towards given direction
void placeWord(Board& board, const string& word, int x, int y, int dx, int dy) {
    for (int i = 0; i < int(word.length()); i++) {
        board.set(x + i*dx, y + i*dy, word[i]);
    }
}

// checks for words matching at position in direction
bool matchingWord(const Board& board, const string& word, int x, int y, int dx, int dy) {
    // if word doesnt fit return
    if (!wordFits(board, word, x, y, dx, dy)) {
        return false;
    }

    // if words will overlap
    for (size_t i = 0; i < word.length(); i++) {
        char currentCell = board.get(x + i*dx, y + i*dy);
        if (currentCell != word[i]) {
            return false;
        }
    }
    return true;
}

// check if the board contains any word from the negativeWords list
bool containsNegativeWord(const Board& board, const vector<string>& negativeWords) {
    for (const string& word : negativeWords) {
        for (int x = 0; x < board.numRows(); x++) {
            for (int y = 0; y < board.numCols(); y++) {
                for (int i = 0; i < 8; i++) {
                    int dx = DIRECTIONS[i].first;
                    int dy = DIRECTIONS[i].second;
                    // if the words allign
                    if (matchingWord(board, word, x, y, dx, dy)) {
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

void fillRemainingSpaces(Board& board, const vector<string>& positiveWords, const vector<string>& negativeWords, set<Board>& solutions, int startX = 0, int startY = 0, char minChar = 'a') {
    // stored loc of a zero
    int zeroX = -1, zeroY = -1;
    bool found = false;

    // traverse board to find the first '0' after curr position
    for (int x = startX; x < board.numRows() && !found; x++) {
        // resets y cord when in new row
        int yStart = (x == startX) ? startY : 0;
        
        for (int y = yStart; y < board.numCols() && !found; y++) {
            if (board.get(x, y) == '0') {
                zeroX = x;
                zeroY = y;
                found = true;
            }
        }
    }

    // no '0' character found add to solutions if no neg words
    if (!found) {
        if (!containsNegativeWord(board, negativeWords)) {
            solutions.insert(board);
        }
        return;
    }

    // fill the '0' character with every char from minChar to z
    for (char ch = minChar; ch <= 'z'; ch++) {
        board.set(zeroX, zeroY, ch);
        if (zeroY < board.numCols() - 1) {
            // move along the row to next col
            fillRemainingSpaces(board, positiveWords, negativeWords, solutions, zeroX, zeroY + 1, ch);
        } else {
            // if end of at last col then start at beg of next row
            fillRemainingSpaces(board, positiveWords, negativeWords, solutions, zeroX + 1, 0, ch);
        }
    }
    board.set(zeroX, zeroY, '0');  // restore board
}

void driver(Board& board, const vector<string>& positiveWords, const vector<string>& negativeWords, int wordIndex, set<Board>& solutions) {
    // if all words have been placed
    if (wordIndex == int(positiveWords.size())) {
        // still has some '0's so fill them
        if (containsZeros(board)) {
            fillRemainingSpaces(board, positiveWords, negativeWords, solutions);
        // no '0's so add to solutions set
        } else if (!containsNegativeWord(board, negativeWords)) {
            solutions.insert(board);
        }
        return;
    }
    
    string currentWord = positiveWords[wordIndex];
    
    // place every word in every position every direction
    for (int x = 0; x < board.numRows(); x++) {
        for (int y = 0; y < board.numCols(); y++) {
            for (int i = 0; i < 8; i++) {
                int dx = DIRECTIONS[i].first;
                int dy = DIRECTIONS[i].second;

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