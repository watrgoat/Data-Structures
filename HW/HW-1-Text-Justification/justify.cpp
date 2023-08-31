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

int main(int argc, char* argv[]) {
	if (argc<5) {
		std::cerr << "ERROR: Not enough input arguments." << std::endl;
		return 0;
	}
	char inFileName = argv[1];
	char outFileName = argv[2];
	int textWidth = atoi(argv[3]);

	// argv[1]: input file name
	// argv[2]: output file name
	// argv[3]: text width
	// argv[4]: 
}
