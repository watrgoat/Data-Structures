// includes
#include <iostream>
#include <fstream>
#include <vector>
#include <Board.h>

using namespace std;

void ingest(ifstream &inputFile, vector<string> &positiveWords, vector<string> &negativeWords) {
    string line;
    while (inputFile >> line) {
        // first line is dimensions
        if (line[0] == 'D') {
            // get dimensions
            int rows = stoi(line.substr(1, line.find('x')));
            int cols = stoi(line.substr(line.find('x') + 1));
            // create board
            Board board(rows, cols);
        }
        // check if line is positive or negative
        if (line[0] == '+') {
            positiveWords.push_back(line.substr(1));
        } else {
            negativeWords.push_back(line.substr(1));
        }
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
    vector<vector<char>> data;

    // ingest input file
    ingest(input_file, data);
    // store data into 

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