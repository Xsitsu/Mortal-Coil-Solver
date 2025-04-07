#include <iostream>
#include <string>
#include <stdlib.h>

#include "Exceptions.h"
#include "Controller.h"
#include "Switches.h"

#include "http/http_handler.hpp"

void usage(std::string prog_name);

int main(int argc, char** argv)
{
	if (argc != 4)
	{
		usage(argv[0]);
		return -1;
	}

	std::string username = argv[1];
	std::string password = argv[2];
	std::string level_num = argv[3];

    int n, x, y;
    std::string s;
    
    int start_x = 0;
    int start_y = 0;
	int start_level = atoi(level_num.c_str());

	HttpHandler handler(username, password, "./level-cache/");

	try
	{
		Controller controller(&handler, start_level, start_x, start_y);
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
					std::cout << "Error: Board is already loaded!" << std::endl;
					break;
				case EX_BOARD_NOT_LOADED:
					std::cout << "Error: Board is not currently loaded!" << std::endl;
					break;
				case EX_BAD_BOARD_LOAD_ATTEMPT:
					std::cout << "Error: Improper values used for creation of board!" << std::endl;
					break;
				case EX_FAIL_FILE_OPEN:
					std::cout << "Error: Could not open board input file!" << std::endl;
					break;
				case EX_OUT_OF_BOARD_RANGE:
					std::cout << "Error: Read square was outside of board range!" << std::endl;
					break;
				case EX_ILLEGAL_BOARD_OPERATION:
					std::cout << "Error: Illegal board operation!" << std::endl;
					break;
				default:
					std::cout << "Error: Unknown exception: " << ex << "!" << std::endl;
					break;
				}
			}
		}
	}
	catch (...)
	{
		std::cout << "Something bad happened!" << std::endl;
	}

    return(0);
}



void usage(std::string prog_name)
{
    std::cout << "Usage: " + prog_name + " <username> <password> <level_number>" << std::endl;
}