
#ifndef READ_CONFIG_H_
#define READ_CONFIG_H_
#include <vector>
#include <string>
#include <limits.h>
#include "processor.h"
#include "job.h"


std::vector<Processor> read_processors(std::string file_name);
std::vector<Job> read_jobs(std::string file_name, int limit = INT_MAX);

#endif //READ_CONFIG_H