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

// function for flush left

// function for flush right

// function for full justify

// optional text file creation function?

int main(int argc, char* argv[]) {
	if (argc!=5) {
		std::cerr << "ERROR: Not enough  or too many input arguments!" << std::endl;
		return 0;
	}
	const char* inFileName[] = argv[1]; // input file name
	const char* outFileName[] = argv[2]; // output file name
	int textWidth = atoi(argv[3]); // text width
	const char* flushType = argv[4]; // flush_left, flush_right, or full_justify

	std::cout << inFileName << std::endl;
	std::cout << outFileName << std::endl;
	std::cout << textWidth << std::endl;
	std::cout << flushType << std::endl;
}
