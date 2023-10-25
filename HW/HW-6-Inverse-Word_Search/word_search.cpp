// includes
#include <iostream>
#include <fstream>
#include <vector>
#include <Board.h>

using namespace std;

pair<int, int> ingest(ifstream &inputFile, vector<string> &positiveWords, vector<string> &negativeWords) {
    string line;
    int rows = 0;
    int cols = 0;
    bool is_dimension = true;
    while (inputFile >> line) {
        // first line is dimensions
        if (is_dimension) {
            size_t pos = line.find(' ');
            // get dimensions
            rows = stoi(line.substr(0, pos));
            cols = stoi(line.substr(pos + 1));
            
            is_dimension = false;
        } else {
            // get word
            string word = line.substr(1);
            // check if line is positive or negative
            if (line[0] == '+') {
                positiveWords.push_back(word);
            } else {
                negativeWords.push_back(word);
            }
        }
    }
    return make_pair(rows, cols);
}

bool isWordPlaceable(const Board& board, const string& word, int x, int y, int dx, int dy) {
    // Check if word can be placed starting from (x, y) and moving in the direction (dx, dy)
    // Make sure to check boundaries and whether the current spot is '0' or the expected character.
    // ...
    return true;  // or false
}

void placeWord(Board& board, const string& word, int x, int y, int dx, int dy) {
    // Place the word on the board starting from (x, y) and moving in the direction (dx, dy)
    // ...
}

void removeWord(Board& board, const string& word, int x, int y, int dx, int dy) {
    // Remove the word from the board starting from (x, y) and moving in the direction (dx, dy)
    for (int i = 0; i < word.length(); i++) {
        board.set(x + i*dx, y + i*dy, '0');
    }
}


bool findNegativeWords(const Board& board, const vector<string>& negativeWords) {
    // Check if any negative word is present on the board
    // ...
    return false;  // or true if negative words are found
}

bool backtrack(Board& board, const vector<string>& positiveWords, const vector<string>& negativeWords, int wordIndex) {
    if (wordIndex == positiveWords.size()) {
        return !findNegativeWords(board, negativeWords);
    }

    pair<int, int> directions[] = {{0, 1}, {1, 0}, {1, 1}, {1, -1}};
    for (int x = 0; x < board.numRows(); ++x) {
        for (int y = 0; y < board.numCols(); ++y) {
            for (int dir = 0; dir < 4; ++dir) {
                int dx = directions[dir].first;
                int dy = directions[dir].second;
                
                if (isWordPlaceable(board, positiveWords[wordIndex], x, y, dx, dy)) {
                    placeWord(board, positiveWords[wordIndex], x, y, dx, dy);
                    if (backtrack(board, positiveWords, negativeWords, wordIndex + 1)) {
                        return true;
                    }
                    // Remove the word for backtracking (undo the placement)
                    // ...
                }
            }
        }
    }
    return false;
}

void createPuzzle(int rows, int cols, const vector<string>& positiveWords, const vector<string>& negativeWords) {
    Board board(rows, cols);
    if (backtrack(board, positiveWords, negativeWords, 0)) {
        // The puzzle is created successfully. You can now print or use the board.
    }
}





int main(int argc, char* argv[]) {
    if (argc != 3) {
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
    ingest(input_file, positiveWords, negativeWords);
    

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
    
}