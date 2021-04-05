#include "input_change.h"
#include <algorithm>


void sum_times(std::vector<Job> &job_vector){
    long long sum_times = 0;
    int i = 0;
    while(i < job_vector.size()){
        sum_times += job_vector[i].min_time_all_processors();
        i++;
    }
    std::cout << "Jakosc rozwiazania: " << sum_times << std::endl;

}


// if job_vector2 has smaller SumCj, then the function returns false, else true
bool compare_quality(std::vector<Job> &job_vector1, std::vector<Job> &job_vector2, int &same_results_counter, int &best_sum_of_times_current){
    long long sum_of_times_job_vector1 = 0;
    long long sum_of_times_job_vector2 = 0;
    int i = 0;
    while (i < job_vector1.size()){
        sum_of_times_job_vector1 += job_vector1[i].min_time_all_processors();
        sum_of_times_job_vector2 += job_vector2[i].min_time_all_processors();
        i++;
    }
    std::cout << "QUALITY vector1: " << sum_of_times_job_vector1 << " vector2: " << sum_of_times_job_vector2 << std::endl;
    if (sum_of_times_job_vector1 >= best_sum_of_times_current){
        same_results_counter++;
    } else {
        same_results_counter = 0;
        best_sum_of_times_current = sum_of_times_job_vector1;
    }
    if(sum_of_times_job_vector1 <= sum_of_times_job_vector2){
        return true;
    }
    return false;
}


// void sort_solutions(std::vector<std::vector<Job>> &start_population, int n){
//     std::sort(start_population.begin(), start_population.end(), [](std::vector<Job> &job_vector1, std::vector<Job> &job_vector2){

//         return compare_quality(job_vector1, job_vector2);

//     });
// }


// swap two jobs
void swap_jobs(std::vector<Job> &jobs, int random_index, int random_index1){
    //std::cout << "Before swap:  \n" << jobs[random_index].to_string() << "\n" << jobs[random_index1].to_string() << std::endl;
    Job temp = jobs[random_index];
    Job temp1 = jobs[random_index1];
    jobs[random_index] = temp1;
    jobs[random_index1] = temp;
    //std::cout << "After swap: \n" << jobs[random_index].to_string() << "\n" << jobs[random_index1].to_string() << std::endl << std::endl;
}


std::vector<Job> change_input_vector(std::vector<Job> jobs, int num){
    if (num == 0){
        num = 1;
    }
    int how_many_mutations = num;
    int random_index, random_index1, random_num;
    int start_index = 0;
    int i = 0;
    while (i < how_many_mutations){
        random_index = rand() % jobs.size();
        random_num = rand() % 40 + 1;
        if (jobs.size() <= 41){
            random_index1 = rand() % jobs.size();

        } else if (random_index > 41) {
            random_index1 = random_index - random_num;

        } else if (jobs.size() - random_index >= 41) {
            random_index1 = random_index + random_num;

        } else {
            random_index1 = rand() % jobs.size();

        }
        
        swap_jobs(jobs, random_index, random_index1);
        i++;
    }
    return jobs;
}


