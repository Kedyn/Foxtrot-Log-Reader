#include <iostream>
#include <string>
#include "Tools.h"

std::string readOrWrite(const std::string &data) {
	std::string *data_tokens = tokenizeString(data);
	std::string cycle = data_tokens[CYCLE_TOKEN_NUMBER];

	if (cycle == "Rd") {
		return "Read";
	}
	else {
		return "Write";
	}
}

int main() {
	std::cout << "Line 2: " << readOrWrite(LINE_2) << " line\n";
	std::cout << "Line 176: " << readOrWrite(LINE_176) << " line\n";
	std::cout << "Line 195: " << readOrWrite(LINE_195) << " line\n";

	return 0;
}
