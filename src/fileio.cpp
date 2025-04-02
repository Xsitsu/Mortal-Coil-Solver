#include "fileio.hpp"

#include <iostream>
#include <fstream>

void FileIO::ReadBoardData(std::string input_file_path, int& lvl_num, int& size_x, int& size_y, std::string& board_data)
{
    std::ifstream myfile(input_file_path);
    if (myfile.is_open())
    {
        myfile >> lvl_num;
        myfile >> size_x;
        myfile >> size_y;
        myfile >> board_data;
        
        myfile.close();
    }
}

void FileIO::WriteSolution(std::string output_file_path, int start_x, int start_y, std::string path)
{
    std::ofstream myfile(output_file_path);
    if (myfile.is_open())
    {
        myfile << start_x << '\n' << start_y << '\n' << path << '\n';
        myfile.close();
    }
}
