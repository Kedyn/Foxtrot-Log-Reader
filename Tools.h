/*
Here you can add tools that you think might be helpful for everyone.
*/
#ifndef TOOLS_H
#define TOOLS_H

#include <string>
#include <regex>

const std::string S_TO_D = "40000810";
const std::string D_TO_S = "40000C18";

const std::string LINE_176 = " -329828 3---       13.140us             -11.749s   Single          A32nD         40000C18         00000000    D32    Wr       Data ----- ----   1111111";
const std::string LINE_195 = " -329809 3---        1.598us             -11.749s   Single          A32nD         40000810         00000000    D32    Rd       Data ----- ----   1111111";


const int NUMBER_OF_TABS = 14;

const int ADDRESS_TOKEN_NUMBER = 6;
const int DATA_TOKEN_NUMBER    = 7;

//Tokenizes data string into non-whitespace strings array
std::string* tokenizeString(const std::string& data) {
	std::regex regex("(\\S+)");

	std::sregex_iterator beginning(data.begin(), data.end(), regex);
	std::sregex_iterator end;

	std::string *result = new std::string[std::distance(beginning, end)];

	std::size_t result_index = 0;
	for (std::sregex_iterator i = beginning; i != end; ++i, ++result_index) {
		std::smatch match = *i;
		std::string match_str = match.str();
		result[result_index] = match_str;
	}

	return result;
}

#endif

