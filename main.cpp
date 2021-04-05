#include <algorithm>
#include <string>
#include <vector>
#include <iostream>
#include <chrono>
#include <functional>
#include "job.h"
#include "processor.h"
#include "read_config.h"
#include "greedy.h"
#include "write_config.h"
#include "input_change.h"



// looking for the best solution in time of ~5 minutes
void execute(std::vector<Job> &jobs, const std::vector<Processor> processors, std::vector<Job> &best_solution, std::chrono::steady_clock::time_point time_zero, int num_of_swaps){
    float deadline = 4.5f*60.0f;
    float max_time = -1;
    int i = 1;
    std::vector<Job> jobs_input = jobs;
    // best_solution = greedy(jobs, processors, 1);
    // wypisywanie jakości pierwszego znalezionego rozwiązania greedy
    // sum_times(best_solution);

    
    std::vector<Job> solution_greedy;
    srand(time(NULL));
    int j = 0;
    int same_results_counter = 0;
    int best_sum_of_times_current = 0;
    while (true && same_results_counter < 20000){
        auto start_greedy = std::chrono::steady_clock::now();
        std::cout << j << std::endl;

        solution_greedy = greedy(jobs, processors, 1);
        if (best_solution.empty()){
            best_solution = solution_greedy;

        } else if (compare_quality(solution_greedy, best_solution, same_results_counter, best_sum_of_times_current)){
            best_solution = solution_greedy;

        }

        auto end_greedy = std::chrono::steady_clock::now();
        std::chrono::duration<float> elapsed_seconds_greedy = end_greedy - start_greedy;
        std::cout << "Greedy time = " << elapsed_seconds_greedy.count() << std::endl;

        // zmutuj listę jobs - szukanie w sąsiedztwie w następnej iteracji greedy
        auto start_swaps = std::chrono::steady_clock::now();
        jobs = change_input_vector(jobs_input, num_of_swaps);
        auto end_swaps = std::chrono::steady_clock::now();

        std::chrono::duration<float> elapsed_seconds_swapping = end_swaps - start_swaps;
        std::cout << "Swapping time = " << elapsed_seconds_swapping.count() << std::endl;
         std::cout << "Time left = " << deadline - static_cast<std::chrono::duration<float>>(end_swaps - time_zero).count() << std::endl;

        if(elapsed_seconds_greedy.count() + elapsed_seconds_swapping.count() > max_time){
            max_time = elapsed_seconds_greedy.count() + elapsed_seconds_swapping.count();
        }

        if(deadline - static_cast<std::chrono::duration<float>>(end_swaps - time_zero).count() < max_time){
            sum_times(best_solution);
            return;
        }

        j++;
    }
    // wypisywanie jakości najlepszego rozwiązania
    sum_times(best_solution);

    return;
}


int main(int argc, char **argv)
{   
    
    if (argc == 1 || argc > 4)
    {
        std::cerr << "Usage: " << std::string(argv[0]) << " <config_file> [jobs_limit]" << std::endl;
        return -1;
    }
    auto start = std::chrono::steady_clock::now();

    std::vector<Job> jobs;
    
    if (argc == 3)
    {
        jobs = read_jobs(argv[1]);
        
    }
    else
    { // argc == 4
        jobs = read_jobs(argv[1], std::stoi(argv[3]));

    }
    //reading processors
    std::vector<Processor> processors = read_processors(argv[1]);
    
    auto end_read = std::chrono::steady_clock::now();

    //sorting input data
    std::sort(jobs.begin(), jobs.end(), [](const Job& j1, const Job& j2){
        if (j1.ready_time() == j2.ready_time()) {
            return j1.processors_needed() < j2.processors_needed();
        }
        return j1.ready_time() < j2.ready_time();
        
    });

    auto end = std::chrono::steady_clock::now();

    //measuring time for reading data and sorting data
    //std::chrono::duration<float> time_left_quick = end_quick - end_read;
    std::chrono::duration<float> time_left_sort = end - end_read;
    std::chrono::duration<float> time_left_read = end_read - start;
    std::cout << "Read time: " << time_left_read.count() << std::endl;
    std::cout << "Sort time: " << time_left_sort.count() << std::endl;

    //looking for the best solution
    std::vector<Job> solution;
    int size_of_jobs = jobs.size();
    int num_of_swaps = static_cast<int>(size_of_jobs*0.02);
    execute(jobs, processors, solution, start, num_of_swaps);

    //writing data to a file
    write_jobs(argv[2], solution);

    return 0;
}
