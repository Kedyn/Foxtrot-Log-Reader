#ifndef FOXTROT_LOG_READER_H
#define FOXTROT_LOG_READER_H

#include <fstream>
#include <sstream>
#include <string>

class FoxtrotLogReader {
	public:
		FoxtrotLogReader() { }
		FoxtrotLogReader(const std::string& reading_file, const std::string& writing_file)
			: log_file(reading_file), output_file(writing_file) { }

		void setLogFile(const std::string& file): log_file(file) { }
		std::string getLogFile() { return log_file; }
		void setOutputFile(const std::string& file): output_file(file) { }
		std::string getOutputFile() { return output_file; }

		void parseLog();

	private:
		bool isCommandAddress(const std::string& address) {
			return (address == S_TO_D || address == D_TO_S);
		}

		bool isDataAddress(const std::string& address) {
			return 
		}

		std::string log_file;
		std::string output_file;
}

#endif
