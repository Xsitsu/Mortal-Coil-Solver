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
			controller.Step();
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