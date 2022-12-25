#include "Map_Handler.hpp"
#include <fstream>
#include <iostream>

class File_Exception {};

Map Map_Handler::read_map(std::string address)
{
    Map new_map;
    std::ifstream map_file;
    map_file.open(address);
    if(!map_file.good())
        throw File_Exception();
    std::string s;
    while(!map_file.eof())
    {
        std::getline(map_file,s);
        if (s.size() == 0) 
            break;
        std::vector<char> row(s.size());
        for (int i = 0; i < s.size(); i++)
            row[i] = s[i];
        new_map.push_back(row);
    }
    map_file.close();  
    return new_map;
}