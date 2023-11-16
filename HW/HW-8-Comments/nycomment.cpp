/*
Makes youtube comments like reddit comments!!
*/

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "CommentNode.h"
#include "CommentTree.h"


int main(int argc, char* argv[]) {
    // check input arg len
    if (argc != 4) {
        std::cerr << "Usage: ./run <input_json> <input_text> <output_text>" << std::endl;
    }

    // open json file
    std::ifstream json_file(argv[1]);
    if (!json_file.is_open()) {
        std::cerr << "Error: Cannot open file '" << argv[1] << "'." << std::endl;
        return 1;
    }

    CommentTree comments;

    // read json comments
    comments.readJsonComments(json_file);

    // close json file
    json_file.close();

    // open text file
    std::ifstream text_file(argv[2]);
    if (!text_file.is_open()) {
        std::cerr << "Error: Cannot open file '" << argv[2] << "'." << std::endl;
        return 1;
    }

    // open output file
    std::ofstream out_file(argv[3]);
    if (!out_file.is_open()) {
        std::cerr << "Error: Cannot open file '" << argv[3] << "'." << std::endl;
        return 1;
    }

    // execute text comments
    comments.executeTextComments(text_file, out_file);

    // close files
    text_file.close();
    out_file.close();
    // ./run.exe hold_me_closer.json input1_hold_me_closer.txt output.txt
    return 0;
}