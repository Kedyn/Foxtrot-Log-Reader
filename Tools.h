#ifndef TOOLS_H
#define TOOLS_H

#include <string>
#include <regex>

//Tokenizes data string into non-whitespace strings array
std::string* tokenizeString(const std::string& data) {
	std::regex regex("(\\S+)");

	std::sregex_iterator beginning(data.begin(), data.end(), regex);
	std::sregex_iterator end;

	std::string *result = new std::string[std::distance(beginning, end)];

	size_t result_index = 0;
	for (std::sregex_iterator i = beginning; i != end; ++i, ++result_index) {
		std::smatch match = *i;
		std::string match_str = match.str();
		result[result_index] = match_str;
	}

	return result;
}

std::string hexCharToBinary(char hex) {
	switch(hex) {
		case '0': return "0000";
		case '1': return "0001";
		case '2': return "0010";
		case '3': return "0011";
		case '4': return "0100";
		case '5': return "0101";
		case '6': return "0110";
		case '7': return "0111";
		case '8': return "1000";
		case '9': return "1001";
		case 'A': return "1010";
		case 'B': return "1011";
		case 'C': return "1100";
		case 'D': return "1101";
		case 'E': return "1110";
		case 'F': return "1111";
		default: return "";
	}
}

std::string hexToBinary(const std::string& hex) {
	std::string result;
	for (size_t i = 0; i < hex.length(); ++i) {
		result += hexCharToBinary(hex[i]);
	}
	return result;
}

std::string hexStringReverse(const std::string& hex) {
	std::string result = "";
	size_t len = hex.length();
	for (size_t i = 4; i <= len; i += 4) {
		result += hex.substr(len - i,4);
	}
	return result;
}

#endif

