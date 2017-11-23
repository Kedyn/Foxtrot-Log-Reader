#include "FoxtrotLogReader.h"

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
