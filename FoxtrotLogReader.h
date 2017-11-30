#ifndef FOXTROT_LOG_READER_H
#define FOXTROT_LOG_READER_H

#include <string>
#include <fstream>

class FoxtrotLogReader {
	public:
		FoxtrotLogReader() { }
		FoxtrotLogReader(const std::string& reading_file, const std::string& writing_file)
			: log_file(reading_file), output_file(writing_file) { }

		void setLogFile(const std::string& file) { log_file = file; }
		std::string getLogFile() { return log_file; }
		void setOutputFile(const std::string& file) { output_file = file; }
		std::string getOutputFile() { return output_file; }

		void parseLog();

	private:
		bool isCommandAddress(const std::string& address);

		bool isDataAddress(const std::string& address);

		std::string getReadOrWrite(const std::string& cycle);

		std::string getCommandType(const std::string& address);

		std::string fieldNameAndDescription(int word, std::string data);

		std::string log_file;
		std::string output_file;
};

class DataRate {
	public:
		DataRate() { }
		DataRate(const long x, const double y)
			: r_s_to_d_data_value(x), r_d_to_s_data_value(x), w_s_to_d_data_value(x), w_d_to_s_data_value(x), r_s_to_d_time_value(y), r_d_to_s_time_value(y), w_s_to_d_time_value(y), w_d_to_s_time_value(y) { } 

		void inputData(int category, double time_measure, std::string type_of_time, std::string data_size);
		long dataConversion(std::string data_size);
		double timeConversion(double time_measure, std::string type_of_time);
		void print(std::ofstream &log_output);
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
