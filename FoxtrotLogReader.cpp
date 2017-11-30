#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>
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
	std::ofstream log_output(output_file);
	std::string line;
	int l = 1;
	int word = 0;
	int words = 0;
	int command = 1;
	int category = 0;
	double time_measure = 0;
	bool reverse_data = false;
	bool check_order = false;
	bool data_check = false;
	std::string smallest_address = "0x00000000";
	std::string data_size = "";
	DataRate data(0, 0);

	while (std::getline(log_contents, line) ) {
		std::string *data_tokens = tokenizeString(line);

		std::string address = "0x"+data_tokens[ADDRESS_TOKEN_NUMBER];

		if (data_check) {
			std::string time = data_tokens[TIME_TOKEN_NUMBER];
			std::string type_of_time = time.substr(time.length() - 2, 2);
			time_measure = std::stod (time.substr(0, time.length() - 2)); 
			data.inputData(category, time_measure, type_of_time, data_size);
			data_check = false;
		}

		if (isCommandAddress(address)) {
			std::string cycle = data_tokens[CYCLE_TOKEN_NUMBER];
			std::string data = data_tokens[DATA_TOKEN_NUMBER];
			word = 0;
			words = std::stoi(data, nullptr, 16) / 2;

			log_output << "Line " << l << ": " << getReadOrWrite(cycle) << " " << getCommandType(address) << " command: " << words << " words\n";
			command++;
			if (words) {
				check_order = true;
				smallest_address = (address == S_TO_D) ? S_TO_D_INITIAL_ADRESS : D_TO_S_INITIAL_ADRESS;
				reverse_data = false;
			}
			else {
				log_output << "\n";
			}
			data_check = true;
			(cycle == "Rd") ? category = 0 : category = 1;
			(address == S_TO_D) ? category += 2 : category += 4;
			
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
					log_output << "Line " << l << ": " << word_info;
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
				log_output << "\n";
			}
			
			data_check = true;
		}
		++l;
		
		if (data_check) {
			data_size = data_tokens[SIZE_TOKEN_NUMBER];
		}
	}
	data.print(log_output);
	log_contents.close();
	log_output.close();
}

void DataRate::inputData(int category, double time_measure, std::string type_of_time, std::string data_size) {
	switch(category) {
		case 2:
			r_s_to_d_time_value += timeConversion(time_measure, type_of_time);
			r_s_to_d_data_value += dataConversion(data_size);
			break;
		case 3:
			w_s_to_d_time_value += timeConversion(time_measure, type_of_time);
			w_s_to_d_data_value += dataConversion(data_size);
			break;
		case 4:
			r_d_to_s_time_value += timeConversion(time_measure, type_of_time);
			r_d_to_s_data_value += dataConversion(data_size);
			break;
		case 5:
			w_d_to_s_time_value += timeConversion(time_measure, type_of_time);
			w_d_to_s_data_value += dataConversion(data_size);
			break;
	}
}

long DataRate::dataConversion(std::string data_size) {
	return (data_size == "D32") ? 32 : 64;
}

double DataRate::timeConversion(double time_measure, std::string type_of_time) {
	if (type_of_time == "ms") {
		return (time_measure / 1000);
	}
	else if (type_of_time == "us") {
		return (time_measure / 1000000);
	}
	else if (type_of_time == "ns") {
		return (time_measure / 1000000000);
	}
}

void DataRate::print(std::ofstream &log_output) {
	log_output << "Read S-to-D: " << std::fixed << std::setprecision(2) << dataRateConversion(r_s_to_d_data_value, r_s_to_d_time_value) << "\n";
	log_output << "Read D-to-S: " << std::fixed << std::setprecision(2) << dataRateConversion(r_d_to_s_data_value, r_d_to_s_time_value) << "\n";
	log_output << "Write S-to-D: " << std::fixed << std::setprecision(2) << dataRateConversion(w_s_to_d_data_value, w_s_to_d_time_value) << "\n";
	log_output << "Write D-to-S: " << std::fixed << std::setprecision(2) << dataRateConversion(w_d_to_s_data_value, w_d_to_s_time_value) << "\n";
}

std::string DataRate::dataRateConversion(long data_value, double time_value) {
	if (time_value == 0) {
		return "N/A";
	}

	double data_rate = (data_value / time_value);
	int byte_type = 0;
	std::stringstream data_number;

	while (data_rate > 1000) {
		data_rate = (data_rate / 1000);
		byte_type++;
	}

	data_number << std::fixed << std::setprecision(2) << data_rate;

	switch(byte_type) {
		case 0: return data_number.str()+" Bits/sec";
		case 1: return data_number.str()+" Kilobits/sec";
		case 2: return data_number.str()+" Megabits/sec";
		case 3: return data_number.str()+" Gigabits/sec";
		case 4: return data_number.str()+" Terabits/sec";
		default: return "N/A";
	}
		
}
