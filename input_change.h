#ifndef INPUT_CHANGE_H_
#define INPUT_CHANGE_H_
#include <algorithm>
#include <string>
#include <vector>
#include <iostream>
#include <chrono>
#include <stdbool.h>
#include <time.h>
#include <stdlib.h>
#include "job.h"
#include "processor.h"


bool compare_quality(std::vector<Job> &job_vector1, std::vector<Job> &job_vector2, int &same_results_counter, int &best_sum_of_times_current);
//void sort_solutions(std::vector<std::vector<Job>> &start_population, int n);
std::vector<Job> change_input_vector(std::vector<Job> jobs, int num);
void sum_times(std::vector<Job> &job_vector);


#endif // INPUT_CHANGE_H_