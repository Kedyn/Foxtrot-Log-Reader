#include <string>
#include <iostream>
#include <sstream>

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
	}
}

std::string hexToBinary(const std::string& hex) {
	std::string result;
	for (std::size_t i = 0; i < hex.length(); ++i) {
		result += hexCharToBinary(hex[i]);
	}
	return result;
}

std::string fieldNameAndDescrip(int wordValue, std::string binaryString) {
	int binaryStrValue;
	std::stringstream statement;
	switch(wordValue) {
		case 0: 
			binaryStrValue = std::stoi(binaryString.substr(1,2), nullptr, 2);
			switch(binaryStrValue) {
				case 0:
					return "Word 0: Rec_Ctrl = 0 (no recording)\n";
				case 2:
					return "Word 0: Rec_Ctrl = 2 (no processing)\n";
				case 3:
					return "Word 0: Rec_Ctrl = 3 (processing & recording)\n";
				default:
					statement << "Word 0: Rec_Ctrl = " << binaryStrValue << " (unknown)\n";
					return statement.str();
			}
		case 1:
			binaryStrValue = std::stoi(binaryString.substr(0,3), nullptr, 2);
			switch(binaryStrValue) {
				case 4:
					return "Word 1: Cmd_Type = 0 (Type A)\n";
				case 5:
					return "Word 1: Cmd_Type = 2 (Type B)\n";
				case 6:
					return "Word 1: Cmd_Type = 3 (Type C)\n";
				default:
					statement << "Word 1: Cmd_Type = " << binaryStrValue << " (unknown)\n";
					return statement.str();
			}
		case 4:
			binaryStrValue = std::stoi(binaryString.substr(15,1), nullptr, 2);
			switch(binaryStrValue) {
				case 0:
					return "Word 4: Rec_Raw = 0 (disable)\n";
				case 1:
					return "Word 4: Rec_Raw = 1 (enable)\n";
				default:
					statement << "Word 4: Rec_Raw = " << binaryStrValue << " (unknown)\n";
					return statement.str();
			}
		case 5:
			binaryStrValue = std::stoi(binaryString.substr(9,7), nullptr, 2);
			statement << "Word 5: Cmd_ID = " << binaryStrValue << "\n";
			return statement.str();
		case 10:
			binaryStrValue = std::stoi(binaryString.substr(0,5), nullptr, 2);
			statement << "Word 10: Num_Responses = " << binaryStrValue << "\n";
			return statement.str();
		case 15:
			binaryStrValue = std::stoi(binaryString.substr(13,1), nullptr, 2);
			switch(binaryStrValue) {
				case 0:
					return "Word 15: Reset_Enable = 0 (disable)\n";
				case 1:
					return "Word 15: Reset_Enable = 1 (enable)\n";
				default:
					statement << "Word 15: Reset_Enable = " << binaryStrValue << " (unknown)\n";
					return statement.str();
			}
		case 22:
			binaryStrValue = std::stoi(binaryString.substr(12,1), nullptr, 2);
			switch(binaryStrValue) {
				case 0:
					return "Word 22: Direction = 0 (Right)\n";
				case 1:
					return "Word 22: Direction = 1 (Left)\n";
				default:
					statement << "Word 22: Direction = " << binaryStrValue << " (unknown)\n";
					return statement.str();
			}
		case 32:
			binaryStrValue = std::stoi(binaryString.substr(1,14), nullptr, 2);
			statement << "Word 32: Num_Samples = " << binaryStrValue << "\n";
			return statement.str();
		case 37:
			binaryStrValue = std::stoi(binaryString.substr(0,1), nullptr, 2);
			switch(binaryStrValue) {
				case 0:
					return "Word 37: Parity = 0 (even)\n";
				case 1:
					return "Word 37: Parity = 1 (odd)\n";
				default:
					statement << "Word 37: Parity = " << binaryStrValue << " (unknown)\n";
					return statement.str();
			}
		case 38:
			binaryStrValue = std::stoi(binaryString.substr(1,1), nullptr, 2);
			switch(binaryStrValue) {
				case 0:
					return "Word 38: Test = 0 (disable)\n";
				case 1:
					return "Word 38: Test = 1 (enable)\n";
				default:
					statement << "Word 38: Test = " << binaryStrValue << " (unknown)\n";
					return statement.str();
			}
		case 40:
			binaryStrValue = std::stoi(binaryString.substr(8,1), nullptr, 2);
			switch(binaryStrValue) {
				case 0:
					return "Word 40: Ctrl_Enable = 0 (disable)\n";
				case 1:
					return "Word 40: Ctrl_Enable = 1 (enable)\n";
				default:
					statement << "Word 40: Ctrl_Enable = " << binaryStrValue << " (unknown)\n";
					return statement.str();
			}
		case 41:
			binaryStrValue = std::stoi(binaryString.substr(1,7), nullptr, 2);
			statement << "Word 41: Code = " << binaryStrValue << "\n";
			return statement.str();
	}
}

int main() {
	std::cout << "1A02: " << fieldNameAndDescrip(0, hexToBinary("1A02"));
	std::cout << "2DFE: " << fieldNameAndDescrip(1, hexToBinary("2DFE"));
	std::cout << "0202: " << fieldNameAndDescrip(4, hexToBinary("0202"));
	std::cout << "0106: " << fieldNameAndDescrip(5, hexToBinary("0106"));
	std::cout << "A000: " << fieldNameAndDescrip(10, hexToBinary("A000"));
	std::cout << "0006: " << fieldNameAndDescrip(15, hexToBinary("0006"));
	std::cout << "0009: " << fieldNameAndDescrip(22, hexToBinary("0009"));
	std::cout << "0100: " << fieldNameAndDescrip(32, hexToBinary("0100"));
	std::cout << "9000: " << fieldNameAndDescrip(37, hexToBinary("9000"));
	std::cout << "6000: " << fieldNameAndDescrip(38, hexToBinary("6000"));
	std::cout << "0090: " << fieldNameAndDescrip(40, hexToBinary("0090"));
	std::cout << "4100: " << fieldNameAndDescrip(41, hexToBinary("4100"));

	return 0;
}
