#include "HttpService.h"

#include <iostream>

HttpService::HttpService()
{

}

HttpService::~HttpService()
{

}

PuzzleData HttpService::GetPuzzle()
{
    PuzzleData ret;
    FileIO::ReadBoardData(ret.number, ret.x, ret.y, ret.data);

	Logger::Instance(ret.number) << "Data Check for puzzle: " << ret.number << "!" << NEWLINE;
	//Logger::Instance() << "1. Data: " << data << NEWLINE;
	Logger::Instance() << "1. Data: " << "x=" << ret.x << "&y=" << ret.y << "&board=" << ret.data << NEWLINE;

	return ret;
}

void HttpService::PostSolution(int x, int y, std::string path)
{
    FileIO::WriteSolution(x, y, path);
}
