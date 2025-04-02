#ifndef HTTPSERVICE_H
#define HTTPSERVICE_H

#include "Exceptions.h"
#include <string>

#include "Logger.h"
#include "GameBoard.h"
#include "fileio.hpp"

class HttpService
{
private:

public:
	HttpService();
	~HttpService();

	PuzzleData GetPuzzle(std::string input_file_path);
	void PostSolution(std::string output_file_path, int x, int y, std::string path);
	
};

#endif
