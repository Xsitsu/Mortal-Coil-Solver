#include <iostream>
#include <string>
#include <string.h>
#include <stdlib.h>

#include "Exceptions.h"
#include "Controller.h"
#include "Switches.h"

#include "http/http_handler.hpp"

std::string prog_name;
void usage();
int main_login(int argc, char** argv);
int main_level_data(int argc, char** argv);

int main(int argc, char** argv)
{
	prog_name = argv[0];
	if (argc < 2)
	{
		usage();
		return -1;
	}

	if (strcmp(argv[1], "--data") == 0)
		return main_level_data(argc, argv);
	else
		return main_login(argc, argv);
}

void run_prog(Controller *controller)
{
	try
	{
		while (controller->GetState() != CSTATE_DONE)
			controller->Step();
	}
	catch (...)
	{
		std::cout << "Something bad happened!" << std::endl;
	}
}

int main_login(int argc, char** argv)
{
	if (argc != 4)
	{
		usage();
		return -1;
	}

	std::string username = argv[1];
	std::string password = argv[2];
	std::string level_num = argv[3];

	int start_level = atoi(level_num.c_str());
	HttpHandler handler(username, password, "./level-cache/");
	Controller controller(&handler, start_level, 0, 0);
	
	run_prog(&controller);

	return 0;
}

int main_level_data(int argc, char** argv)
{
	if (argc != 3)
	{
		usage();
		return -1;
	}

	std::string puzzle_data = argv[2];
	Controller controller(nullptr, 0, 0, 0);
	controller.OverwritePuzzleData(puzzle_data);

	run_prog(&controller);
	
	return 0;
}

void usage()
{
    std::cout << "Usage: " + prog_name + " <username> <password> <level_number>" << std::endl;
	std::cout << "       " + prog_name + " --data <puzzle_data>" << std::endl;
}