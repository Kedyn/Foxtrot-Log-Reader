#include <iostream>
#include "FoxtrotLogReader.h"

void usage(const char* function_name) {
	std::cout << "Usage: " << function_name << " string\n";
		std::cout << "Where string is a filename\n";
}

int main(int argc, char* argv[]) {
	if (argc == 1) {
		usage(argv[0]);
		return 1;
	}
		
	else if (argc == 2) {
		FoxtrotLogReader parser(argv[1], "notTruelyRequired.txt");
		parser.parseLog();
		return 0;
	}

	else {
		std::cout << "Error: should only specify one input file.\n";
		usage(argv[0]);
		return 2;
	}
}
