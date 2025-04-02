#pragma once

#include <string>

class FileIO
{
private:
    FileIO() {}
    ~FileIO() {}
    
public:
    static void ReadBoardData(std::string input_file_path, int& lvl_num, int& size_x, int& size_y, std::string& board_data);
    static void WriteSolution(std::string output_file_path, int start_x, int start_y, std::string path);

};
