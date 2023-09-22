// reverse engineered teamates code
#include <iostream>

int main() {
	char ***carrot;
	char **broccoli;
	char *tomato = new char;
	*tomato = 'z';
	broccoli = *tomato;
	carrot = *broccoli;
	
	char radish = 'q';

	std::cout << *broccoli << std::endl;

	delete tomato;

	return 0;
}
