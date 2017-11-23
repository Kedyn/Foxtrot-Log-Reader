#include <iostream>
#include <string>
#include "Tools.h"

bool isDataAddress(const std::string& address) {
	long address_number = std::stoul(address, nullptr, 16);
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

int main() {

	std::string hex_numbers[] = {"0x40000819", "0x40000817", "0x4000086C", "0x40000C21", "0x40000C19", "0x40000C74"};

	for(std::string hex : hex_numbers) {
		std::cout << hex << " is ";
		if (!isDataAddress(hex)) {
			std::cout << "not ";
		}
		std::cout << "a data address\n";
	}
}
