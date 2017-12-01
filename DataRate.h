#ifndef DATA_RATE_H
#define DATA_RATE_H

#include <string>

class DataRate {
	public:
		DataRate() { }
		DataRate(const long x, const double y)
			: r_s_to_d_data_value(x), r_d_to_s_data_value(x), w_s_to_d_data_value(x), w_d_to_s_data_value(x), r_s_to_d_time_value(y), r_d_to_s_time_value(y), w_s_to_d_time_value(y), w_d_to_s_time_value(y) { } 

		void inputData(int category, double time_measure, std::string type_of_time, std::string data_size);
		void print(std::ofstream &log_output);

		long dataConversion(std::string data_size);
		double timeConversion(double time_measure, std::string type_of_time);

		std::string dataRateConversion(long data_value, double time_value);
		
	private:
		long r_s_to_d_data_value;
		long r_d_to_s_data_value;
		long w_s_to_d_data_value;
		long w_d_to_s_data_value;

		double r_s_to_d_time_value;
		double r_d_to_s_time_value;
		double w_s_to_d_time_value;
		double w_d_to_s_time_value;	
};

#endif
