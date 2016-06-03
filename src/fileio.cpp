#include "fileio.hpp"

#include <iostream>
#include <fstream>

void FileIO::ReadBoardData(int& lvl_num, int& size_x, int& size_y, std::string& board_data)
{
    std::ifstream myfile("board.dat");
    if (myfile.is_open())
    {
        myfile >> lvl_num;
        myfile >> size_x;
        myfile >> size_y;
        myfile >> board_data;
        
        myfile.close();
    }
}

void FileIO::WriteSolution(int start_x, int start_y, std::string path)
{
    std::ofstream myfile("solution.dat");
    if (myfile.is_open())
    {
        myfile << start_x << '\n' << start_y << '\n' << path << '\n';
        myfile.close();
    }
}
