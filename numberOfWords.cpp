#include <iostream>
#include <string>
#include "Tools.h"

int numberOfWords(const std::string& hex) {
	return std::stoi(hex, nullptr, 16) / 2;
}

int main() {
	std::string *line_176_tokens = tokenizeString(LINE_176);
	std::string *line_196_tokens = tokenizeString(LINE_196);

	std::cout << "Number of words in line 176: " << numberOfWords("0x"+line_176_tokens[DATA_TOKEN_NUMBER]) << '\n';
	std::cout << "Number of words in line 196: " << numberOfWords("0x"+line_196_tokens[DATA_TOKEN_NUMBER]) << '\n';

	return 0;
}
