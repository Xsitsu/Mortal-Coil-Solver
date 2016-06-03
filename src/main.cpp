#include <iostream>
#include <string>
#include <stdlib.h>

#include "Exceptions.h"
#include "Controller.h"
#include "Logger.h"
#include "fileio.hpp"

#include "Switches.h"

int main(int argc, char** argv)
{
    int n, x, y;
    std::string s;
    FileIO::ReadBoardData(n, x, y, s);
    
    Logger::Instance(n);

    int start_x = 0;
    int start_y = 0;
    if (argc == 3)
    {
        start_x = atoi(argv[1]);
        start_y = atoi(argv[2]);
    }

	try
	{
		Controller controller(start_x, start_y);
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
