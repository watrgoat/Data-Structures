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

// void function for the dashed lines at the start and end

//optional function to print out everything, takes spaced out text lines as input

// function to read text and split up
std::std::vector<std::string> v;

// function for flush left
void left(char *text[]) {
	std::cout << text << std::endl;
}

// function for flush right

// function for full justify

// optional text file creation function?

int main(int argc, char* argv[]) {
	if (argc!=5) {
		std::cerr << "ERROR: Not enough or too many input arguments!" << std::endl;
		return 0;
	}
	std::string inFileName = argv[1]; // input file name
	std::string outFileName = argv[2]; // output file name
	int textWidth = atoi(argv[3]); // text width
	std::string flushType = argv[4]; // flush_left, flush_right, or full_justify

	// open file in read mode
	std::fstream file(inFileName, std::ios::in);

	std::string line;
	while (std::getline(file, line)) {
		std::string sentence = "Geeks For Geeks";
	    std::string word;
	 
	    std::istringstream iss(line);
	    while (std::getline(iss, word, ' ')) {
	        std::cout << word << std::endl;
	    }
	}

	// Close the file
	file.close();

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
