#include <fstream>
#include <sstream>
#include <iostream>
#include "read_config.h"


std::vector<Processor> read_processors(std::string file_name)
{
    std::ifstream file;
    file.open(file_name);
    if (file.is_open())
    {
        std::string line;
        int procs;
        while (std::getline(file, line))
        {
            size_t pos = line.find("MaxProcs: ");
            if (pos != -1)
            {
                auto found = line.find_first_of("123456789");
                if (found != std::string::npos){
                   procs = std::stoi(line.substr(found));
                }
            }
        }
        file.close();
        std::vector<Processor> result;
        for (int i = 0; i < procs; i++)
        {
            result.emplace_back(i);
        }
        return result;
    }
    else
    {
        throw "Cannot open file: " + file_name;
    }
}

std::vector<int> findNumbers(std::string jobLine)
{
    std::stringstream s;
    s << jobLine; 
    std::string temp;
    std::vector<int> result;
    int found, x = 0;
    // 5 because there are this many job variables
    while (!s.eof() && x < 5)
    {
        s >> temp;
        if (std::stringstream(temp) >> found)
        {
            result.emplace_back(found);
        }
        temp = "";
        x++;
    }
    return result;
}

std::vector<Job> read_jobs(std::string file_name, int limit)
{
    std::ifstream file;
    file.open(file_name);

    if (file.is_open())
    {
        std::string line;
 
        std::vector<Job> result;
        while (std::getline(file, line) && result.size() < limit)
        {
            size_t pos = line.find(";", 0, 1);
            if (pos == -1)
            {
                std::vector<int> tabJob = findNumbers(line);
                if (!tabJob.empty())
                {
                    // tabJob[3]=run time
                    if (tabJob[0] >= 0 && tabJob[1] >= 0 && tabJob[3] > 0 && 
                    tabJob[4] > 0)
                    {
                        result.emplace_back(tabJob);
                    }
                    
                }
            }
        }
        file.close();
        return result;
    }
    else
    {
        throw "Cannot open file: " + file_name;
    }
}