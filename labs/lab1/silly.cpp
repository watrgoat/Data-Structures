# include <iostream>

int main(int argc, char* argv[]) {
	// checking the number of cmd line args
	if (argc < 2) return 0;

	// set product to first value
	int product = atoi(argv[1]);
	
	// loop over the number of command line arguments
	for(int i=2; i<argc; i++) {
		// converts command line args from string to int and multiplies
		int input = atoi(argv[i]);
		product *= input;
	}
	std::cout << "product of integers: " << product << std::endl;
	return 0;
}