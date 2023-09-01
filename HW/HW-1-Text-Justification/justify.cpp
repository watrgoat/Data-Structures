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

// function to read text and split up
bool GetText(std::string fileName, std::vector<std::string> &textArr) {
	// open file in read mode
	std::fstream file(fileName, std::ios::in);

	std::string line;

	while (std::getline(file, line)) {
	    std::string word;
	 
	    std::istringstream iss(line);
	    while (std::getline(iss, word, ' ')) {
	        textArr.push_back(word);
	    }
	}
	// Close the file
	file.close();
	return true;
}

// function for flush left pass text by const reference
bool left(std::string outName, const std::vector<std::string> &textArr) {

	return true;
}

// function for flush right


// function for full justify

// optional text file creation function?

// main function
int main(int argc, char* argv[]) {
	if (argc!=5) {
		std::cerr << "ERROR: Not enough or too many input arguments!" << std::endl;
		exit(0);
	}
	std::string inFileName = argv[1]; // input file name
	std::string outFileName = argv[2]; // output file name
	int textWidth = atoi(argv[3]); // text width
	std::string flushType = argv[4]; // flush_left, flush_right, or full_justify

	std::vector<std::string> text;

	bool success = GetText(inFileName, text);

	for (unsigned int i=0; i < text.size(); i++) {
		std::cout << text.at(i) << " " << strlen(text.at(i).c_str()) << std::endl;
	}

	if (flushType=="flush_left") {
		std::cout << "left" << std::endl;
	}
	else if (flushType=="flush_right") {
		std::cout << "right" << std::endl;
	}
	else if (flushType=="full_justify") {
		std::cout << "full" << std::endl;
	}
	else {
		std::cerr << "ERROR: " << flushType << " flush type is not an option." << std::endl;
	}

}
