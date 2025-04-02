#include <iostream>
#include <string>
#include <stdlib.h>

#include "Exceptions.h"
#include "Controller.h"
#include "Logger.h"
#include "fileio.hpp"

#include "Switches.h"

void usage(std::string prog_name);

int main(int argc, char** argv)
{
	if (argc != 3)
	{
		usage(argv[0]);
		return -1;
	}

	std::string input_file_path = argv[1];
	std::string output_file_path = argv[2];

    int n, x, y;
    std::string s;
    FileIO::ReadBoardData(input_file_path, n, x, y, s);
    
    Logger::Instance(n);

    int start_x = 0;
    int start_y = 0;

	try
	{
		Controller controller(input_file_path, output_file_path, start_x, start_y);
		while (controller.GetState() != CSTATE_DONE)
		{
			try
			{
				controller.Step();
			}
			catch (EXCEPTION ex)
			{
				switch (ex)
				{
				case EX_BOARD_ALREADY_LOADED:
					Logger::Instance() << "Error: Board is already loaded!" << NEWLINE;
					break;
				case EX_BOARD_NOT_LOADED:
					Logger::Instance() << "Error: Board is not currently loaded!" << NEWLINE;
					break;
				case EX_BAD_BOARD_LOAD_ATTEMPT:
					Logger::Instance() << "Error: Improper values used for creation of board!" << NEWLINE;
					break;
				case EX_FAIL_FILE_OPEN:
					Logger::Instance() << "Error: Could not open board input file!" << NEWLINE;
					break;
				case EX_OUT_OF_BOARD_RANGE:
					Logger::Instance() << "Error: Read square was outside of board range!" << NEWLINE;
					break;
				case EX_ILLEGAL_BOARD_OPERATION:
					Logger::Instance() << "Error: Illegal board operation!" << NEWLINE;
					break;
				default:
					Logger::Instance() << "Error: Unknown exception: " << ex << "!" << NEWLINE;
					break;
				}
			}
		}
	}
	catch (...)
	{
		Logger::Instance() << "Something bad happened!" << NEWLINE;
	}

	// Cleanup Singletons
	Logger::Cleanup();

    return(0);
}



void usage(std::string prog_name)
{
	std::cout << "Usage: " + prog_name + " <board_file> <solution_file>" << std::endl;
}