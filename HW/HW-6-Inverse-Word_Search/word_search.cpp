// includes
#include <iostream>
#include <fstream>
#include <vector>
#include "Board.h"

using namespace std;

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

bool isWordPlaceable(const Board& board, const string& word, int x, int y, int dx, int dy) {
    
    // check if word is in bounds 
    // current position + word length * direction > board size
    if (x + word.length()*dx >= board.numRows() || y + word.length()*dy >= board.numCols() ||
        x + (word.length() - 1)*dx < 0 || y + (word.length() - 1)*dy < 0) {
        return false;
    }


    // check if all characters are 0
    for (size_t i = 0; i < word.length(); i++) {
        cout << "here" << endl;
        if (board.get(x + i*dx, y + i*dy) != '0') {
            return false;
        }
    }
    
    return true;  // or false
}

void placeWord(Board& board, const string& word, int x, int y, int dx, int dy) {
    // Place the word on the board starting from (x, y) and moving in the direction (dx, dy)
    for (int i = 0; i < word.length(); i++) {
        board.set(x + i*dx, y + i*dy, word[i]);
    }

}

void removeWord(Board& board, const string& word, int x, int y, int dx, int dy) {
    // Remove the word from the board starting from (x, y) and moving in the direction (dx, dy)
    for (int i = 0; i < word.length(); i++) {
        board.set(x + i*dx, y + i*dy, '0');
    }
}

bool findNegativeWords(const Board& board, const vector<string>& negativeWords) {
    pair<int, int> directions[] = {{0, 1}, {1, 0}, {1, 1}, {1, -1}};
    
    for (const string& negativeWord : negativeWords) {
        for (int x = 0; x < board.numRows(); x++) {
            for (int y = 0; y < board.numCols(); y++) {
                for (int dir = 0; dir < 4; dir++) {
                    int dx = directions[dir].first;
                    int dy = directions[dir].second;
                    
                    bool isMatch = true;
                    for (size_t m = 0; m < negativeWord.length(); m++) {
                        cout << "out of bounds" << endl;
                        if (board.get(x + m*dx, y + m*dy) != negativeWord[m]) {
                            isMatch = false;
                            break;
                        }
                    }
                    if (isMatch) { return true; }
                }
            }
        }
    }
    return false;
}


void backtrack(Board& board, const vector<string>& positiveWords, const vector<string>& negativeWords, int wordIndex, vector<Board>& solutions) {
    cout << solutions.size() << endl;
    if (wordIndex == positiveWords.size()) {
        if (!findNegativeWords(board, negativeWords)) {
            solutions.push_back(board);  // Store this valid board as a solution
        }
    }

    pair<int, int> directions[] = {{0, 1}, {1, 0}, {1, 1}, {1, -1}};
    for (int x = 0; x < board.numRows(); ++x) {
        for (int y = 0; y < board.numCols(); ++y) {
            for (int dir = 0; dir < 4; ++dir) {
                int dx = directions[dir].first;
                int dy = directions[dir].second;
                cout << "x: " << x << " y: " << y << " dx: " << dx << " dy: " << dy << endl;
                cout << board << endl;
                
                if (isWordPlaceable(board, positiveWords[wordIndex], x, y, dx, dy)) {

                    cout << "placeable" << endl;
                    cout << board << endl;
                    placeWord(board, positiveWords[wordIndex], x, y, dx, dy);
                    cout << "after place" << endl;
                    backtrack(board, positiveWords, negativeWords, wordIndex + 1, solutions);
                    removeWord(board, positiveWords[wordIndex], x, y, dx, dy);
                }
            }
        }
    }
}


void createPuzzle(int rows, int cols, const vector<string>& positiveWords, const vector<string>& negativeWords) {
    Board board(rows, cols);
    vector<Board> solutions;
    backtrack(board, positiveWords, negativeWords, 0, solutions);
    
    // The `solutions` vector now contains all possible solution boards.
    // You can print them, store them, or perform other actions as required.
    cout << "Solutions:" << endl;
    for (const Board& solution : solutions) {
        cout << solution << endl;
    }
}



int main(int argc, char* argv[]) {
    if (argc != 4) {
        cout << "Usage: ./word_search <input_file> <output_file> <solution_type>" << endl;
        return 1;
    }

    // open input file
    ifstream input_file(argv[1]);
    if (!input_file.is_open()) {
        cout << "Error: could not open file '" << argv[1] << "'." << endl;
        return 1;
    }
    
    // create data structure to store input file
    vector<string> positiveWords;
    vector<string> negativeWords;

    // ingest input file
    pair<int, int> dim = ingest(input_file, positiveWords, negativeWords);
    
    // close input file
    input_file.close();

    // create puzzle
    createPuzzle(dim.first, dim.second, positiveWords, negativeWords);
    
    // create all soltions with positive words.
    // make the board rectangular and set to empty value
    // if still found in board then you can set to any character a-z
    // but make sure that u still check for bad words 
    // backtracking algorithm



    // eleminate bad boards as you go not at the end

    // print all solutions to output file

    // open output file
    ofstream output_file(argv[2]);
    if (!output_file.is_open()) {
        cout << "Error: could not open file '" << argv[2] << "'." << endl;
        return 1;
    }

    // close output file
    output_file.close();
    
}