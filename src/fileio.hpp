#pragma once

#include <string>

class FileIO
{
private:
    FileIO() {}
    ~FileIO() {}
    
public:
    static void ReadBoardData(int& lvl_num, int& size_x, int& size_y, std::string& board_data);
    static void WriteSolution(int start_x, int start_y, std::string path);

};
