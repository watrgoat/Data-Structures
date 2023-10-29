#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <set>
#include "Board.h" // Include the Board class header

std::set<std::string> allWords;
std::vector<std::string> requiredWords, forbiddenWords;

bool wordExists(const Board& board, int x, int y, const std::string &word) {
    const int dx[] = {1, 1, 0, -1, -1, -1, 0, 1};
    const int dy[] = {0, 1, 1, 1, 0, -1, -1, -1};

    for(int dir = 0; dir < 8; dir++) {
        int i, j;
        for(i = 0, j = 0; i < word.size(); i++) {
            int nx = x + i * dx[dir];
            int ny = y + i * dy[dir];
            if(nx < 0 || nx >= board.numRows() || ny < 0 || ny >= board.numCols() || board.get(nx, ny) != word[j++]) {
                break;
            }
        }
        if(i == word.size()) return true;
    }
    return false;
}

bool isSolution(const Board& board) {
    for(const std::string &word: requiredWords) {
        bool found = false;
        for(int i = 0; i < board.numRows() && !found; i++) {
            for(int j = 0; j < board.numCols() && !found; j++) {
                if(wordExists(board, i, j, word)) {
                    found = true;
                }
            }
        }
        if(!found) return false;
    }
    for(const std::string &word: forbiddenWords) {
        for(int i = 0; i < board.numRows(); i++) {
            for(int j = 0; j < board.numCols(); j++) {
                if(wordExists(board, i, j, word)) {
                    return false;
                }
            }
        }
    }
    return true;
}

// New function to check if a partial word can be found starting from (x,y) in a given direction
bool partialWordExists(const Board& board, int x, int y, const std::string &word) {
    const int dx[] = {1, 1, 0, -1, -1, -1, 0, 1};
    const int dy[] = {0, 1, 1, 1, 0, -1, -1, -1};

    for(int dir = 0; dir < 8; dir++) {
        int i, j;
        for(i = 0, j = 0; j < word.size() && i < word.size(); i++) {
            int nx = x + i * dx[dir];
            int ny = y + i * dy[dir];
            if(nx < 0 || nx >= board.numRows() || ny < 0 || ny >= board.numCols()) {
                break;
            }
            if(board.get(nx, ny) == word[j]) {
                j++;
            } else {
                break;
            }
        }
        if(j == word.size()) return true;
    }
    return false;
}

bool canContinue(const Board& board, int x, int y) {
    // Check forbidden words
    for(const std::string &word: forbiddenWords) {
        for(int i = 0; i <= x; i++) {
            for(int j = 0; j < board.numCols(); j++) {
                if(partialWordExists(board, i, j, word)) {
                    return false;
                }
            }
        }
    }

    // Check if required words can still be placed
    for(const std::string &word: requiredWords) {
        bool possible = false;
        for(int i = 0; i < board.numRows() && !possible; i++) {
            for(int j = 0; j < board.numCols() && !possible; j++) {
                if(partialWordExists(board, i, j, word)) {
                    possible = true;
                }
            }
        }
        if(!possible) return false;
    }
    return true;
}

bool findSolution(Board& board, std::ostream& out, bool findAll, int x, int y) {
    if(x == board.numRows()) {
        if(isSolution(board)) {
            out << board << std::endl;
            return true;
        }
        return false;
    }
    std::cout << board;
    for(char c = 'a'; c <= 'z'; c++) {
        board.set(x, y, c);
        if(!canContinue(board, x, y)) { // Check if we can continue after setting this letter
            continue;
        }
        int nx = (y == board.numCols() - 1) ? (x + 1) : x;
        int ny = (y + 1) % board.numCols();
        if(findSolution(board, out, findAll, nx, ny) && !findAll) {
            return true;
        }
    }
    return false;
}


int main(int argc, char *argv[]) {
    if(argc != 4) {
        std::cerr << "Usage: " << argv[0] << " <inputfile> <outputfile> <one_solution/all_solutions>" << std::endl;
        return 1;
    }

    std::ifstream in(argv[1]);
    std::ofstream out(argv[2]);
    bool findAll = (std::string(argv[3]) == "all_solutions");

    int width, height;
    in >> width >> height;
    Board board(width, height);
    
    char sign;
    std::string word;
    while(in >> sign >> word) {
        allWords.insert(word);
        if(sign == '+') {
            requiredWords.push_back(word);
        } else {
            forbiddenWords.push_back(word);
        }
    }

    if(!findSolution(board, out, findAll, 0, 0) && !findAll) {
        out << "No solutions found" << std::endl;
    }

    in.close();
    out.close();
    return 0;
}
