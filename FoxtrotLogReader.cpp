#include <fstream>
#include <sstream>
#include "Tools.h"
#include "FoxtrotLogReader.h"


bool FoxtrotLogReader::isDataAddress(const std::string& address) {
	int address_number = std::stoi(address, nullptr, 16);
	if ((address_number >= std::stoi(S_TO_D_INITIAL_ADRESS, nullptr, 16) &&
		address_number <= std::stoi(S_TO_D_FINAL_ADRESS, nullptr, 16)) ||
		(address_number >= std::stoi(D_TO_S_INITIAL_ADRESS, nullptr, 16) &&
		address_number <= std::stoi(D_TO_S_FINAL_ADRESS, nullptr, 16))) {
		return true;
	}
	else {
		return false;
	}
}

void FoxtrotLogReader::parseLog() {
	std::ifstream log_contents(log_file);
	std::string line;
	bool reading_command = false;

	while (std::getline(log_contents, line)) {
		std::istringstream line_content(line);

		std::string *data_tokens = tokenizeString(line_content);

		std::string address = data_tokens[ADDRESS_TOKEN_NUMBER];

		if (isCommandAddress(address)) {
			if (address == S_TO_D) {
				
			}
			else {
				
			}
		}
		else if (reading_command && isDataAddress(adress)) {
			
		}
	}
}
