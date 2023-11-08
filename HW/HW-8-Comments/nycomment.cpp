/*
Makes youtube comments like reddit comments!!
*/

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "CommentNode.h"

using namespace std;

// Function Prototypes
void readJsonComments(vector<string>& comments);
void readTextComments(vector<string>& comments);

void readJsonComments(vector<string>& comments) {
    
}

void readTextComments(ifstream &file, vector<string>& comments) {
    
}

int main(int argc, char* argv[]) {
    // check input arg len
    if (argc != 4) {
        cerr << "Usage: ./run <input_json> <input_text> <output_text>" << endl;
    }

    // read in json comments
    vector<CommentNode> comments;
    readJsonComments(comments);
}