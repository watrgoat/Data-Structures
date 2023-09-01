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
# include <string>

// void function for the dashed lines at the start and end

//optional function to print out everything, takes spaced out text lines as input

// function for flush left

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

	switch (flushType) {
		case "flush_left":
			std::cout << "testing" << std::endl;
		case "flush_right":
			std::cout << "testing" << std::endl;
		case "full_justify":
			std::cout << "testing" << std::endl;
		default:
			std::cerr << "ERROR: " << flushType << " is not a flush type" << std::endl;
	}
	return 0;
}
