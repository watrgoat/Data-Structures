# include <iostream>
# include <fstream>
# include <sstream>
# include <string>
# include <vector>
# include <cstring>

using namespace std;

// void function for the dashed lines at the start and end


//optional function to print out everything, takes spaced out text lines as input

// function to read text and split up words
// possible change: bool func to output success
bool GetText(ifstream &file, vector<string> &textArr) {
	if (!file.good()) {
	    cerr << "Can't open " << fileName << endl;
	    exit(1);
	}

	string line;

	while (file >> line) {
	    string word;
	    stringstream ss(line);

	    while (ss >> word) {
	        textArr.push_back(word);
	    }
	}

	file.close();
	return true;
}


// function for flush left pass text by const reference
bool FlushLeft(ofstream &oFile, const vector<string> &lineVec) {
	string line;
	for (unsigned int i; i < lineVec.size(); i++) {
		line += lineVec
	}
	// loop over words serperate by a space
	// add the rest of spaces at the end
	return true;
}


// function for flush right
bool FlushRight(ofstream &oFile, const vector<string> &lineVec) {
	
	return true;
}


// function for full justify
bool FullJustify(ofstream &oFile, const vector<string> &lineVec) {

	return true;
}
// divide the extra space and place it in between words, use floor div and modulo to contain remainder

// optional text file creation function?

// hold 2 values, startLine, endLine they are both equal to 1 the 
// if lineLength is empty and next item is greater than max width
// vector is searched with a lineLength value being stored
// start and endline values are updated to max line length.
// if single word is > than maxWidth catch it, set it to line, chop it like a tree, at max width-1 add a hyphen until lineLength < maxWidth
// once lineLength is too full add lines to file, repeat until reaching end of 
bool LineSplitter(ofstream &outFile, const unsigned int &maxWidth, const vector<string> &textArr, const string &textType) {
	int lineLength = 0;
	vector<string> line;
	string longLine;
	
	for (unsigned int i; i<textArr.size(); i++) {
		if (textArr[i].length() > maxWidth) {
			// word too long

			if  (lineLength > 0) {
				// CALL FLUSH HERE
				line.clear();
				lineLength = 0;
			}

			longLine = textArr[i];

			while (longLine.length() > maxWidth) {
				cout << "| " << longLine.substr(0,maxWidth-1) << "- |" << endl;
				longLine = longLine.substr(maxWidth);
			}

			if (longLine.length() > 0) {
				line.push_back(longLine)
				lineLength = longLine.length();
				longLine.clear();
			}
		} else {
			// word not too long

			if (textArr[i].length() + 1 + lineLength > maxWidth) {
				// CALL FLUSH HERE
				line.clear();
				lineLength = 0;
			} else {
				// line not too long
				line.push_back(textArr[i])
				lineLength += textArr[i].length()
			}
		}
	}
	return true;
}

// main function
int main(int argc, char* argv[]) {
	if (argc!=5) {
		cerr << "ERROR: Only 4 arguments accepted!" << endl;
		exit(1);
	}

	ifstream inFile(argv[1]); // input file name
	ofstream outFile(argv[2]); // output file name
	unsigned int textWidth = atoi(argv[3]); // text width
	string flushType = argv[4]; // flush_left, flush_right, or full_justify

	if (flushType!="flush_left" || flushType!="flush_right" || flushType!="full_justify") {
		cerr << "ERROR: " << flushType << " is not an option." << endl;
		exit(1);
	}


	vector<string> text;

	// gets text from input file
	GetText(inFileName, text);

	bool success = false;

	

	return 0;
}
