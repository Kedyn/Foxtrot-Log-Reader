#include <iostream>
#include <fstream>
#include "Tools.h"
#include "FoxtrotLogReader.h"

bool FoxtrotLogReader::isCommandAddress(const std::string& address) {
	return (address == S_TO_D || address == D_TO_S);
}

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

std::string FoxtrotLogReader::getReadOrWrite(const std::string& cycle) {
	return (cycle == "Rd") ? "Read" : "Write";
}

int FoxtrotLogReader::getNumberOfWords(const std::string& hex) {
	return std::stoi(hex, nullptr, 16) / 2;
}

std::string FoxtrotLogReader::getCommandType(const std::string& address) {
	return (address == S_TO_D) ? "S-to-D" : "D-to-S";
}


void FoxtrotLogReader::parseLog() {
	std::ifstream log_contents(log_file);
	std::string line;
	bool reading_command = false;
	int l = 1;
	int command = 1;

	while (std::getline(log_contents, line) && command < 11) {

		std::string *data_tokens = tokenizeString(line);

		std::string address = "0x"+data_tokens[ADDRESS_TOKEN_NUMBER];

		if (isCommandAddress(address)) {
			std::string cycle = data_tokens[CYCLE_TOKEN_NUMBER];
			std::string data = data_tokens[DATA_TOKEN_NUMBER];
			if (address == S_TO_D) {
				
			}
			else {
				
			}
			std::cout << "Line: " << l << " has a " << getReadOrWrite(cycle) << " " << getCommandType(address) << "command: " << getNumberOfWords(data) << " words\n";
			command++;
		}
		else if (reading_command && isDataAddress(address)) {
			
		}
		++l;
	}
	log_contents.close();
}
