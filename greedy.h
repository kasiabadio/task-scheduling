#ifndef GREEDY_H_
#define GREEDY_H_
#include <vector>
#include <iostream>
#include "job.h"
#include "processor.h"
#include "time.h"

std::vector<Job> greedy(std::vector<Job> tabJob, std::vector<Processor> tabProcessors, size_t random_range);

#endif // GREEDY_H_