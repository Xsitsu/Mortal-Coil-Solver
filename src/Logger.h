#ifndef LOGGER_H
#define LOGGER_H

#define nullptr NULL

#include <string>
#include <fstream>

#include "Switches.h"

#define DUPLICATE_OUTPUT_TO_COUT

const char output_file[] = "Log";
const char NEWLINE[] = "\n";
const char LINE[] = "______________________________________________________________________";

class Logger
{
private:
	static Logger* instance;

	std::ofstream fout;

protected:
	Logger(int num);
	~Logger();
	Logger(Logger const&){};
	Logger& operator=(Logger const&){};

public:
	static Logger& Instance(int num = 0);
	static void Cleanup();

	void BreakLine();

	Logger& operator<<(int data);
	Logger& operator<<(std::string data);
};

#endif
