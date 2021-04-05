#include <fstream>
#include <vector>
#include "write_config.h"


void write_jobs(std::string file_name, const std::vector<Job> &solution){
    std::ofstream file;
    file.open(file_name);
    if(file.is_open()){
        for (const auto &job: solution){
            file << job.to_string_out();
            for (const auto &id: job.on_processors()){
                file << " " + std::to_string(id);
            }
            file << std::endl;
        }
        file.close();
    }
    else
    {
        throw "Cannot open file: " + file_name;
    }

}