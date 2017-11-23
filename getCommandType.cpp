#include <iostream>
#include <string>
#include "Tools.h"

std::string getCommandType(const std::string& data) {
	std::string *data_tokens = tokenizeString(data);

	if ("0x"+data_tokens[ADDRESS_TOKEN_NUMBER] == S_TO_D) {
		return S_TO_D;
	}
	else {
		return D_TO_S;
	}
}

std::string cmdToString(const std::string& command_type) {
	if (command_type == S_TO_D) {
		return "S_TO_D";
	}
	return "D_TO_S";
}

int main() {
	std::cout << "Line 176 is a " << cmdToString(getCommandType(LINE_176)) << " command\n";
	std::cout << "Line 195 is a " << cmdToString(getCommandType(LINE_195)) << " command\n";

	return 0;
}

