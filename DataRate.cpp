#include <ofstream>
#include <iomanip>
#include <sstream>
#include "DataRate.h"

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

void DataRate::print(std::ofstream &log_output) {
	log_output << "Read S-to-D: " << std::fixed << std::setprecision(2) << dataRateConversion(r_s_to_d_data_value, r_s_to_d_time_value) << "\n";
	log_output << "Read D-to-S: " << std::fixed << std::setprecision(2) << dataRateConversion(r_d_to_s_data_value, r_d_to_s_time_value) << "\n";
	log_output << "Write S-to-D: " << std::fixed << std::setprecision(2) << dataRateConversion(w_s_to_d_data_value, w_s_to_d_time_value) << "\n";
	log_output << "Write D-to-S: " << std::fixed << std::setprecision(2) << dataRateConversion(w_d_to_s_data_value, w_d_to_s_time_value) << "\n";
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
