#include "Logger.h"

#include <iostream>
#include <string>
#include <sstream>

Logger::Logger(int num)
{
    std::string fname = output_file;
    std::ostringstream convert;
    convert << num;
    fname = "logs/" + fname + "-";
    fname += convert.str();
    fname += ".txt";
    fout.open(fname.c_str());

#ifdef DEBUG_OUTPUT_CONSTRUCTORS
	std::cout << "Logger constructed: " << int(this) << NEWLINE;
#endif
}

Logger::~Logger()
{
	if (fout.is_open())
		fout.close();

#ifdef DEBUG_OUTPUT_CONSTRUCTORS
	std::cout << "Logger destroyed: " << int(this) << NEWLINE;
#endif
}

Logger* Logger::instance = nullptr;

Logger& Logger::Instance(int num)
{
    if (instance == nullptr)
        instance = new Logger(num);
    
	return *instance;
}

void Logger::Cleanup()
{
	if (instance != nullptr)
	{
		delete instance;
	}
}

void Logger::BreakLine()
{
	if (fout.is_open())
	{
		*instance << LINE << NEWLINE << NEWLINE;
	}

#ifdef DUPLICATE_OUTPUT_TO_COUT
	std::cout << LINE << NEWLINE << NEWLINE;
#endif

}

Logger& Logger::operator<<(int data)
{
	if (fout.is_open())
		fout << data;

#ifdef DUPLICATE_OUTPUT_TO_COUT
	std::cout << data;
#endif

	return *this;
}

Logger& Logger::operator<<(std::string data)
{
	if (fout.is_open())
	{
		if (data == NEWLINE)
		{
			fout << std::endl;
#ifdef DUPLICATE_OUTPUT_TO_COUT
			std::cout << std::endl;
#endif
		}
		else
		{
			fout << data;
#ifdef DUPLICATE_OUTPUT_TO_COUT
			std::cout << data;
#endif
		}
		
	}

	return *this;
}
