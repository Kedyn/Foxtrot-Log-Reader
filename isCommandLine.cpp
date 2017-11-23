#include <iostream>
#include <string>
#include "Tools.h"

bool isCommandLine(const std::string& data) {
	std::string *data_tokens = tokenizeString(data);
	std::string hex_address = "0x"+data_tokens[ADDRESS_TOKEN_NUMBER];

	if (hex_address == S_TO_D || hex_address == D_TO_S) {
		return true;
	}
	return false;
}

int main() {
	std::cout << "Line 2 is a " << isCommandLine(LINE_2) << " command line\n";
	std::cout << "Line 176 is a " << isCommandLine(LINE_176) << " command line\n";
	std::cout << "Line 195 is a " << isCommandLine(LINE_195) << " command line\n";

	std::cout << "\nNotice: 0 is false, 1 is true\n";

	return 0;
}
