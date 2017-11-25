#ifndef FOXTROT_LOG_READER_H
#define FOXTROT_LOG_READER_H

#include <string>

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

#endif
