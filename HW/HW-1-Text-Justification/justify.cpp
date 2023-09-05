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
bool GetText(const string &fileName, vector<string> &textArr) {
	ifstream file(fileName);

	if (!file.good()) {
	    cerr << "Can't open " << fileName << endl;
	    exit(1);
	}

	string line;

	while (file >> line) {
	    string word;
		
	    istringstream iss(line);
	    while (getline(iss, word, ' ')) {
	        textArr.push_back(word);
	    }
	}

	file.close();
	return true;
}


// function for flush left pass text by const reference
bool FlushLeft(const string &outName, const unsigned int &maxWidth, const vector<string> &textArr) {
	ofstream file(outName);

	

	if (!file.good()) {
	    cerr << "Can't open " << outName << endl;
	    exit(1);
	}

	string dashedLine(maxWidth+4, '-');
	string line;

	file << dashedLine << endl;

	for (unsigned int i; i<textArr.size(); i++) {
		file.flush();
		if (line.length()+textArr[i].length()<=maxWidth) {
			// space goes before because there is a space always needed for 
			line += textArr[i] + ' ';
		} else {
			if (line.back() == ' ') line.pop_back();
			string extraSpace(maxWidth-line.length(), ' ');
			file << "| " << line << extraSpace << " |" << endl;
			line.clear();
			line += textArr[i] + ' ';
		}
		/*else if (textArr[i] >= maxWidth) {
			// MY BRAIN HURTED HERE
			line += " " + textArr[i]
			string tmpLine;
			while line >= maxWidth;
				tmpLine = line.substr(0, maxWidth)


		}*/
		// add word to line if it +1 isnt > maxWidth, " "
		// if word fits add the word
		// if word is > than maxWidth cut it off at 15 add a hyphen
		// if word is == to maxWidth
		
	}
	if (line.length()>1) {
		if (line.back() == ' ') line.pop_back();
		string extraSpace(maxWidth-line.length(), ' ');
		file << "| " << line << extraSpace << " |" << endl;
	}
	file << dashedLine << endl;
	file.close();
	return true;
}


// function for flush right
bool FlushRight(const string &outName, const unsigned int &maxWidth, const vector<string> &textArr) {
	ofstream file(outName);

	if (!file.good()) {
	    cerr << "Can't open " << outName << endl;
	    exit(1);
	}

	string dashedLine(maxWidth+4, '-');
	string line;

	file << dashedLine << endl;

	for (unsigned int i; i<textArr.size(); i++) {
		file.flush();
		if (line.length()+textArr[i].length()<=maxWidth) {
			// space goes before because there is a space always needed for 
			line += textArr[i] + ' ';
		} else {
			if (line.back() == ' ') line.pop_back();
			string extraSpace(maxWidth-line.length(), ' ');
			file << "| " << extraSpace << line << " |" << endl;
			line.clear();
			line += textArr[i] + ' ';
		}
		/*else if (textArr[i] >= maxWidth) {
			// MY BRAIN HURTED HERE
			line += " " + textArr[i]
			string tmpLine;
			while line >= maxWidth;
				tmpLine = line.substr(0, maxWidth)


		}*/
		// add word to line if it +1 isnt > maxWidth, " "
		// if word fits add the word
		// if word is > than maxWidth cut it off at 15 add a hyphen
		// if word is == to maxWidth
		
	}
	if (line.length()>1) {
		if (line.back() == ' ') line.pop_back();
		string extraSpace(maxWidth-line.length(), ' ');
		file << "| " << extraSpace << line << " |" << endl;
	}
	file << dashedLine << endl;
	file.close();
	return true;
}


// function for full justify
// divide the extra space and place it in between words, use floor div and modulo to contain remainder

// optional text file creation function?

// hold 2 values, startLine, endLine they are both equal to 1 the 
// if lineLength is empty and next item is greater than max width
// vector is searched with a lineLength value being stored
// start and endline values are updated to max line length.
// if single word is > than maxWidth catch it, set it to line, chop it like a tree, at max width-1 add a hyphen until lineLength < maxWidth
// once lineLength is too full add lines to file, repeat until reaching end of 
bool test(const string &outName, const unsigned int &maxWidth, const vector<string> &textArr) {
	int startLine, endLine = 1;
	int lineLength = 0;
	
	for (unsigned int i; i<textArr.size(); i++) {
		
	}
	return true;
}

// main function
int main(int argc, char* argv[]) {
	if (argc!=5) {
		cerr << "ERROR: Only 4 arguments accepted!" << endl;
		exit(1);
	}

	string inFileName = argv[1]; // input file name
	string outFileName = argv[2]; // output file name
	unsigned int textWidth = atoi(argv[3]); // text width
	string flushType = argv[4]; // flush_left, flush_right, or full_justify

	vector<string> text;

	// gets text from input file
	GetText(inFileName, text);

	bool success = false;

	if (flushType=="flush_left") {
		success = FlushLeft(outFileName, textWidth, text);
	}
	else if (flushType=="flush_right") {
		success = FlushRight(outFileName, textWidth, text);
	}
	else if (flushType=="full_justify") {
		cout << "full" << endl;
	}
	else {
		cerr << "ERROR: " << flushType << " flush type is not an option." << endl;
		exit(1);
	}

	return 0;
}
