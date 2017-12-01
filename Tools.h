#ifndef TOOLS_H
#define TOOLS_H

#include <string>

//Tokenizes data string into non-whitespace strings array
std::vector<std::string> tokenizeString(const std::string& data);

std::string hexCharToBinary(char hex);

std::string hexToBinary(const std::string& hex);

std::string hexStringReverse(const std::string& hex);

#endif

