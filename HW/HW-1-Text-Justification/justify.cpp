/*
example.txt:

Here is an example of text justification.

And here’s the output produced for that input file for 
the three different justification modes, for the specified
text width of 16:

flush left:
--------------------
| Here is an       |
| example of text  |
| justification.   |
--------------------

flush right:
--------------------
|       Here is an |
|  example of text |
|   justification. |
--------------------

full justify:
--------------------
| Here    is    an |
| example  of text |
| justification.   |
--------------------*/

# include <iostream>
# include <fstream>
# include <sstream>
# include <string>
# include <vector>
# include <cstring>

// void function for the dashed lines at the start and end


//optional function to print out everything, takes spaced out text lines as input

// function to read text and split up words
// possible change: bool func to output success
void GetText(const std::string &fileName, std::vector<std::string> &textArr) {
	std::ifstream file(fileName);

	if (!file.good()) {
	    std::cerr << "Can't open " << fileName << std::endl;
	    exit(1);
	}

	std::string line;

	while (file >> line) {
	    std::string word;
		
	    std::istringstream iss(line);
	    while (std::getline(iss, word, ' ')) {
	        textArr.push_back(word);
	    }
	}

	file.close();
}

// function for flush left pass text by const reference
void FlushLeft(const std::string &outName, const int &maxWidth, const std::vector<std::string> &textArr) {
	std::ofstream file(outName);

	if (!file.good()) {
	    std::cerr << "Can't open " << outName << std::endl;
	    exit(1);
	}

	std::string line = textArr[0];
	std::string front(maxWidth+4, '-');
	std::cout << front << "\n";

	for (unsigned int i=1; i < textArr.size(); i++) { 
		// fyi size function call inside the loop is referencing the size val stored for all vectors and therfore has no practical difference and the tradeoff of saving the value to memory actually makes it worse
		if (line.length()+textArr[i].length() > maxWidth) {
			std::cout << "| " << line.substr(0, line.length()-1) << " |\n";
			// adds line then erases line
			line.clear();
		}
		line += " " + textArr[i];
	}

	std::cout << front << "\n";
	file.close();
}

// function for flush right

// function for full justify

// optional text file creation function?

// main function
int main(int argc, char* argv[]) {
	if (argc!=5) {
		std::cerr << "ERROR: Only 4 arguments accepted!" << std::endl;
		exit(1);
	}

	std::string inFileName = argv[1]; // input file name
	std::string outFileName = argv[2]; // output file name
	int textWidth = atoi(argv[3]); // text width
	std::string flushType = argv[4]; // flush_left, flush_right, or full_justify

	std::vector<std::string> text;

	// gets text from input file
	GetText(inFileName, text);

	if (flushType=="flush_left") {
		FlushLeft(outFileName, textWidth, text);
	}
	else if (flushType=="flush_right") {
		std::cout << "right" << std::endl;
	}
	else if (flushType=="full_justify") {
		std::cout << "full" << std::endl;
	}
	else {
		std::cerr << "ERROR: " << flushType << " flush type is not an option." << std::endl;
		exit(1);
	}

}
