/*
This program was created assuming the line (data) passed to getCommandType() will have already
determine that S_TO_D or D_TO_S hexadecimal codes have been detected in the line
*/
#include <iostream>
#include <string>
#include "Tools.h"

std::string getCommandType(const std::string& data) {
	std::string *data_tokens = tokenizeString(data);

	if (data_tokens[ADDRESS_TOKEN_NUMBER] == S_TO_D) {
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
	std::string line_176 = " -329828 3---       13.140us             -11.749s   Single          A32nD         40000C18         00000000    D32    Wr       Data ----- ----   1111111";
	std::string line_195 = " -329809 3---        1.598us             -11.749s   Single          A32nD         40000810         00000000    D32    Rd       Data ----- ----   1111111";

	std::cout << "Line 176 is a " << cmdToString(getCommandType(line_176)) << " command\n";
	std::cout << "Line 195 is a " << cmdToString(getCommandType(line_195)) << " command\n";

	return 0;
}

