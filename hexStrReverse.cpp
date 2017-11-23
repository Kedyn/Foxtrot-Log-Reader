#include <iostream>
#include <string>
#include "Tools.h"

std::string hexStrReverse(const std::string &data) {
	std::string *data_tokens = tokenizeString(data);
	std::string reverseStr = data_tokens[DATA_TOKEN_NUMBER];

	for (int i = 0, strLen = reverseStr.size(); i < (strLen / 2); i += 2) {
		std::swap(reverseStr[i], reverseStr[strLen - i - 2]);
		std::swap(reverseStr[i + 1], reverseStr[strLen - i - 1]);
	}

	return reverseStr;
}

int main() {
	std::cout << "Line 2: " << hexStrReverse(LINE_2) << " line\n";
	std::cout << "Line 196: " << hexStrReverse(LINE_196) << " line\n";

	return 0;
}
