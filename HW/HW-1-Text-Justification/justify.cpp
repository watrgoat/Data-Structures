// File:	justify.cpp

# include <iostream>
# include <fstream>
# include <sstream>
# include <string>
# include <vector>
# include <cstring>

using namespace std;


// function to read text and split up words
bool GetText(ifstream &file, vector<string> &textArr) {
	string line;

	// in stream each line in file
	while (file >> line) {
	    string word;

	    // splits line by spaces
	    stringstream ss(line);
	    while (ss >> word) {
	        textArr.push_back(word);
	    }
	}

	file.close();
	return true;
}


// function for flush left pass text by const reference
bool FlushLeft(ofstream &file, const vector<string> &lineVec, unsigned int width) {
	string line;

	// loops over words and connects them
	for (unsigned int i=0; i < lineVec.size(); i++) {
		line += lineVec[i] + ' ';
	}
	// remove extra space at the end
	line.pop_back();

	// adds the rest of spaces at the end based on how much space is left
	string extraSpaces(width-line.length(), ' ');
	file << "| " << line << extraSpaces << " |" << endl;

	return true;
}


// function for flush right
bool FlushRight(ofstream &file, const vector<string> &lineVec, unsigned int width) {
	string line;

	for (unsigned int i=0; i < lineVec.size(); i++) {
		line += lineVec[i] + ' ';
	}
	// remove extra space at the end
	line.pop_back();

	// adds the rest of spaces at the end
	string extraSpaces(width-line.length(), ' ');
	file << "| " <<  extraSpaces << line << " |" << endl;

	return true;
}


// function for full justify
bool FullJustify(ofstream &file, const vector<string> &lineVec, unsigned int width, int lineLen) {
	string line;

	// if there is only one element, left justify
	if (lineVec.size() == 1) {
		line += lineVec[0];
		string space(width-line.length(), ' ');
		file << "| " << line << space << " |" << endl;
		return true;
	}

	// divids extra space and place it in between words
	// uses floor div and modulo to account for remaining spaces
	string space((width-lineLen)/(lineVec.size()-1), ' ');
	int extraSpaces = (width-lineLen) % (lineVec.size()-1);
	
	for (unsigned int i=0; i < lineVec.size()-1; i++) {
		// extra spaces for the first ones if needed
		if (extraSpaces > 0) {
			line += lineVec[i] + space + ' ';
			extraSpaces -= 1;
		} else {
			line += lineVec[i] + space;
		}
		
	}
	line += lineVec.back();
	file << "| " << line << " |" << endl;
	return true;
}


// calls the specific justify function: made to reduce code repitition
void Flush(ofstream &outerFile, const vector<string> &lineV, unsigned int wideness, const string &type, int lineL, bool isLast) {
	if (type=="flush_left") {
		FlushLeft(outerFile, lineV, wideness);
	} else if (type=="flush_right") {
		FlushRight(outerFile, lineV, wideness) ;
	} else if (type=="full_justify" && !(isLast)) {
		FullJustify(outerFile, lineV, wideness, lineL);
	} else if (type=="full_justify" && isLast) {
		// calls left justify if it is the last of full justify
		FlushLeft(outerFile, lineV, wideness);
	}
	return;
}


// splits lines into a smaller vectors (max size of a line) and then gives  to the appropriate justification function
bool LineSplitter(ofstream &oFile, unsigned int maxWidth, const vector<string> &textArr, const string &textType) {
	int lineLength = 0;
	vector<string> line;
	string longLine;
	
	for (unsigned int i=0; i<textArr.size(); i++) {
		// if line is long
		if (textArr[i].length() > maxWidth) {

			// flushes current text if any
			if  (lineLength > 0) {
				Flush(oFile, line, maxWidth, textType, lineLength, false);
				line.clear();
				lineLength = 0;
			}

			longLine = textArr[i];

			// chops down long line until there the line is less than max
			while (longLine.length() > maxWidth) {
				oFile << "| " << longLine.substr(0,maxWidth-1) << "- |" << endl;
				longLine = longLine.substr(maxWidth-1);
			}

			// checks for any more chars in the long line, pushes to vector
			if (longLine.length() > 0) {
				line.push_back(longLine);
				lineLength = longLine.length();
				longLine.clear();
			}
		// word is not too long
		} else {
			
			// checks if the next word will overfill the current line
			// if it does it flushes and adds the current word to line
			if (textArr[i].length() + (line.size()-1) + lineLength >= maxWidth) {
				Flush(oFile, line, maxWidth, textType, lineLength, false);
				line.clear();
				lineLength = textArr[i].length();
				line.push_back(textArr[i]);

			// adds word to line if nothing else happened
			} else {
				line.push_back(textArr[i]);
				lineLength += textArr[i].length();
			}
		}
	}

	// checks if there is anything left in the line and flushes it
	if (line.size() > 0) {
		Flush(oFile, line, maxWidth, textType, lineLength, true);
		line.clear();
		lineLength = 0;
	}

	return true;
}


// main function
int main(int argc, char* argv[]) {
	if (argc!=5) {
		cerr << "ERROR: Only 4 arguments accepted!" << endl;
		exit(1);
	}

	// input arguments
	ifstream inFile(argv[1]);
	ofstream outFile(argv[2]);
	unsigned int textWidth = atoi(argv[3]);
	string flushType = argv[4];



	// checks if in and out files opened.
	if (!inFile.good()) {
	    std::cerr << "Can't open " << argv[1] << " to read.\n";
	    exit(1);
	} if (!outFile.good()) {
    	std::cerr << "Can't open " << argv[2] << " to read.\n";
    	exit(1);
    }

    // checks if text width input is geater than 2
    if (textWidth<2) {
    	std::cerr << "Text width input too small\n";
    	exit(1);
    }

    // checks flush type inputs are written correctly
	if (flushType=="flush_left" || flushType=="flush_right" || flushType=="full_justify") {
		// good
	} else {
		cerr << flushType << " is not an option.\n";
		exit(1);
	}

	vector<string> text;
	string dashedLine(textWidth+4, '-');

	// gets text from input file
	GetText(inFile, text);

	// adds the dahsed line at the start
	outFile << dashedLine << endl;

	// calls line split function on text
	LineSplitter(outFile, textWidth, text, flushType);

	// dashed line at the end
	outFile << dashedLine << endl;

	outFile.close();

	return 0;
}
