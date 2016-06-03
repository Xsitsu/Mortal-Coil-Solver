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

	PuzzleData GetPuzzle();
	void PostSolution(int x, int y, std::string path);
	
};

#endif
