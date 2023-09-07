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
bool FlushLeft(ofstream &file, const vector<string> &lineVec, const unsigned int &width) {
	string line;

	for (unsigned int i=0; i < lineVec.size(); i++) {
		line += lineVec[i] + ' ';
	}
	// remove extra space at the end
	line.pop_back();

	// adds the rest of spaces at the end
	string extraSpaces(width-line.length(), ' ');
	file << "| " << line << extraSpaces << " |" << endl;

	return true;
}


// function for flush right
bool FlushRight(ofstream &file, const vector<string> &lineVec, const unsigned int &width) {
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
bool FullJustify(ofstream &file, const vector<string> &lineVec, const unsigned int &width, const unsigned int &lineLen) {
	string line;

	if (lineVec.size() == 1) {
		line += lineVec[0];
		string space(width-line.length(), ' ');
		file << "| " << line << space << " |" << endl;
		return true;
	}

	string space((width-lineLen)/(lineVec.size()-1), ' ');
	int extraSpaces = (width-lineLen) % (lineVec.size()-1);
	
	for (unsigned int i=0; i < lineVec.size()-1; i++) {
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
// divide the extra space and place it in between words, use floor div and modulo to contain remainder

void Flush(ofstream &outerFile, const vector<string> &lineV, const unsigned int &wideness, const string &type, const int &lineL, const bool &isLast) {
	if (type=="flush_left") {
		FlushLeft(outerFile, lineV, wideness);
	} else if (type=="flush_right") {
		FlushRight(outerFile, lineV, wideness) ;
	} else if (type=="full_justify" && !(isLast)) {
		FullJustify(outerFile, lineV, wideness, lineL);
	} else if (type=="full_justify" && isLast) {
		FlushLeft(outerFile, lineV, wideness);
	}
	return;
}

// hold 2 values, startLine, endLine they are both equal to 1 the 
// if lineLength is empty and next item is greater than max width
// vector is searched with a lineLength value being stored
// start and endline values are updated to max line length.
// if single word is > than maxWidth catch it, set it to line, chop it like a tree, at max width-1 add a hyphen until lineLength < maxWidth
// once lineLength is too full add lines to file, repeat until reaching end of 
bool LineSplitter(ofstream &oFile, const unsigned int &maxWidth, const vector<string> &textArr, const string &textType) {
	int lineLength = 0;
	vector<string> line;
	string longLine;
	
	for (unsigned int i=0; i<textArr.size(); i++) {
		if (textArr[i].length() > maxWidth) {

			if  (lineLength > 0) {
				Flush(oFile, line, maxWidth, textType, lineLength, false);
				line.clear();
				lineLength = 0;
			}

			longLine = textArr[i];

			while (longLine.length() > maxWidth) {
				oFile << "| " << longLine.substr(0,maxWidth-1) << "- |" << endl;
				longLine = longLine.substr(maxWidth-1);
			}

			if (longLine.length() > 0) {
				line.push_back(longLine);
				lineLength = longLine.length();
				longLine.clear();
			}
		} else {
			// word not too long
			if (textArr[i].length() + (line.size()-1) + lineLength >= maxWidth) {
				Flush(oFile, line, maxWidth, textType, lineLength, i==textArr.size()-1);
				line.clear();
				lineLength = textArr[i].length();
				line.push_back(textArr[i]);
			} else {
				line.push_back(textArr[i]);
				lineLength += textArr[i].length();
			}
		}
	}

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

	ifstream inFile(argv[1]); // input file name
	ofstream outFile(argv[2]); // output file name
	unsigned int textWidth = atoi(argv[3]); // text width
	string flushType = argv[4]; // flush_left, flush_right, or full_justify

	if (!inFile.good()) {
	    std::cerr << "Can't open " << argv[1] << " to read.\n";
	    exit(1);
	}

	if (!outFile.good()) {
    	std::cerr << "Can't open " << argv[2] << " to read.\n";
    	exit(1);
    }

    if (textWidth<2) {
    	std::cerr << "Text width input too small\n";
    	exit(1);
    }

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

	outFile << dashedLine << endl;

	LineSplitter(outFile, textWidth, text, flushType);

	outFile << dashedLine << endl;

	outFile.close();
	return 0;
}
