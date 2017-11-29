#include <iostream>
#include <fstream>
#include "definitions.h"
#include "Tools.h"
#include "FoxtrotLogReader.h"

bool FoxtrotLogReader::isCommandAddress(const std::string& address) {
	return (address == S_TO_D || address == D_TO_S);
}

bool FoxtrotLogReader::isDataAddress(const std::string& address) {
	unsigned long address_number = std::stoul(address, nullptr, 16);
	if ((address_number >= std::stoul(S_TO_D_INITIAL_ADRESS, nullptr, 16) &&
		address_number <= std::stoul(S_TO_D_FINAL_ADRESS, nullptr, 16)) ||
		(address_number >= std::stoul(D_TO_S_INITIAL_ADRESS, nullptr, 16) &&
		address_number <= std::stoul(D_TO_S_FINAL_ADRESS, nullptr, 16))) {
		return true;
	}
	else {
		return false;
	}
}

std::string FoxtrotLogReader::getReadOrWrite(const std::string& cycle) {
	return (cycle == "Rd") ? "Read" : "Write";
}

std::string FoxtrotLogReader::getCommandType(const std::string& address) {
	return (address == S_TO_D) ? "S-to-D" : "D-to-S";
}


std::string FoxtrotLogReader::fieldNameAndDescription(int word, std::string data) {
	int data_value;
	//std::cout << "Word " << word << '\n';
	switch(word) {
		case 0:
			data_value = std::stoi(data.substr(1,2), nullptr, 2);
			switch(data_value) {
				case 0: return "Word 0: Rec_Ctrl = 0 (no recording)\n";
				case 2: return "Word 0: Rec_Ctrl = 2 (no processing)\n";
				case 3: return "Word 0: Rec_Ctrl = 3 (processing & recording)\n";
				default: return "Word 0: Rec_Ctrl = "+std::to_string(data_value)+" (unknown)\n";
			}
		case 1:
			data_value = std::stoi(data.substr(0,3), nullptr, 2);
			switch(data_value) {
				case 4: return "Word 1: Cmd_Type = 4 (Type A)\n";
				case 5: return "Word 1: Cmd_Type = 5 (Type B)\n";
				case 6: return "Word 1: Cmd_Type = 6 (Type C)\n";
				default: return "Word 1: Cmd_Type = "+std::to_string(data_value)+" (unknown)\n";
			}
		case 4:
			data_value = std::stoi(data.substr(15,1), nullptr, 2);
			switch(data_value) {
				case 0: return "Word 4: Rec_Raw = 0 (disable)\n";
				case 1: return "Word 4: Rec_Raw = 1 (enable)\n";
				default: return "Word 4: Rec_Raw = "+std::to_string(data_value)+" (unknown)\n";
			}
		case 5: return "Word 5: Cmd_ID = "+std::to_string(std::stoi(data.substr(9,7), nullptr, 2))+"\n";
		case 10: return "Word 10: Num_Responses = "+std::to_string(std::stoi(data.substr(0,5), nullptr, 2))+"\n";
		case 15:
			data_value = std::stoi(data.substr(13,1), nullptr, 2);
			switch(data_value) {
				case 0: return "Word 15: Reset_Enable = 0 (disable)\n";
				case 1: return "Word 15: Reset_Enable = 1 (enable)\n";
				default: return "Word 15: Reset_Enable = "+std::to_string(data_value)+" (unknown)\n";
			}
		case 22:
			data_value = std::stoi(data.substr(12,1), nullptr, 2);
			switch(data_value) {
				case 0: return "Word 22: Direction = 0 (Right)\n";
				case 1: return "Word 22: Direction = 1 (Left)\n";
				default: return "Word 22: Direction = "+std::to_string(data_value)+" (unknown)\n";
			}
		case 32:
			return "Word 32: Num_Samples = "+std::to_string(std::stoi(data.substr(1,15), nullptr, 2))+"\n";
		case 37:
			data_value = std::stoi(data.substr(0,1), nullptr, 2);
			switch(data_value) {
				case 0: return "Word 37: Parity = 0 (even)\n";
				case 1: return "Word 37: Parity = 1 (odd)\n";
				default: return "Word 37: Parity = "+std::to_string(data_value)+" (unknown)\n";
			}
		case 38:
			data_value = std::stoi(data.substr(1,1), nullptr, 2);
			switch(data_value) {
				case 0: return "Word 38: Test = 0 (disable)\n";
				case 1: return "Word 38: Test = 1 (enable)\n";
				default: return "Word 38: Test = "+std::to_string(data_value)+" (unknown)\n";
			}
		case 40:
			data_value = std::stoi(data.substr(8,1), nullptr, 2);
			switch(data_value) {
				case 0: return "Word 40: Ctrl_Enable = 0 (disable)\n";
				case 1: return "Word 40: Ctrl_Enable = 1 (enable)\n";
				default: return "Word 40: Ctrl_Enable = "+std::to_string(data_value)+" (unknown)\n";
			}
		case 41: return "Word 41: Code = "+std::to_string(std::stoi(data.substr(1,7), nullptr, 2))+"\n";
		default: return "";
	}
}

void FoxtrotLogReader::parseLog() {
	std::ifstream log_contents(log_file);
	std::string line;
	int l = 1;
	int word = 0;
	int words = 0;
	int command = 1;
	double time_measure = 0;
	bool reverse_data = false;
	bool check_order = false;
	std::string smallest_address = "0x00000000";

	while (std::getline(log_contents, line) && command < 12) {
		std::string *data_tokens = tokenizeString(line);

		std::string address = "0x"+data_tokens[ADDRESS_TOKEN_NUMBER];

		if (isCommandAddress(address)) {
			std::string cycle = data_tokens[CYCLE_TOKEN_NUMBER];
			std::string data = data_tokens[DATA_TOKEN_NUMBER];
			word = 0;
			words = std::stoi(data, nullptr, 16) / 2;

			std::cout << "Line " << l << ": " << getReadOrWrite(cycle) << " " << getCommandType(address) << " command: " << words << " words\n";
			command++;
			if (words) {
				check_order = true;
				smallest_address = (address == S_TO_D) ? S_TO_D_INITIAL_ADRESS : D_TO_S_INITIAL_ADRESS;
				reverse_data = false;
			}
			else {
				std::cout << "\n";
			}
		}
		else if (words && isDataAddress(address)) {
			if (check_order) {
				check_order = false;
				if (address != smallest_address) {
					reverse_data = true;
					word = words - 1;
				}
			}
			std::string data = data_tokens[DATA_TOKEN_NUMBER];
			if (reverse_data) {
				data = hexStringReverse(data);
			}
			for (size_t i = 0; i <  data.length(); i += 4) {
				std::string word_info = fieldNameAndDescription(word, hexToBinary(data.substr(i, 4)));
				if (word_info != "") {
					std::cout << "Line " << l << ": " << word_info;
				}
				if (reverse_data) {
					--word;
				}
				else {
					++word;
				}
				words--;
			}
			if (!words) {
				std::cout << "\n";
			}
			std::string time = data_tokens[TIME_TOKEN_NUMBER];
			std::string type_of_time = time.substr(time.length() - 2, 2);
			time_measure = std::stod (time.substr(0, time.length() - 2)); 
			// std::cout << time << "\n" << time_measure << type_of_time << "\n";
		}
		++l;
	}
	log_contents.close();
}
