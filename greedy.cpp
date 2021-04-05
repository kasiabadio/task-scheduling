#include "greedy.h"
#include <limits.h>
#include <algorithm>
#include <chrono>

bool not_on_processors(std::vector<int> &tabProcInd, int processor_id)
{
    for (const auto &id : tabProcInd)
    {
        if (processor_id == id)
        {
            return false;
        }
    }
    return true;
}

void random_put_job(Job &job, std::vector<Processor> &tabProcessors)
{
    std::vector<int> tabProcInd;
    int max_finish_time = -1;

    //choosing random processors for a job
    for (int i = 0; i < job.processors_needed(); i++)
    {
        int random_index = rand() % tabProcessors.size();
        while (!not_on_processors(tabProcInd, tabProcessors[random_index].id()))
        {
            random_index = rand() % tabProcessors.size();
        }
        tabProcInd.emplace_back(tabProcessors[random_index].id());
        if (tabProcessors[random_index].finish_time() > max_finish_time)
        {
            max_finish_time = tabProcessors[random_index].finish_time();
        }
    }
    //updating time in a job
    job.on_processors(tabProcInd);
    if (max_finish_time < job.ready_time())
    {
        max_finish_time = job.ready_time();
    }
    job.min_time_all_processors(max_finish_time + job.processing_time());

    //updating jobs on processors
    for (auto id : tabProcInd)
    {
        auto found_it = std::find_if(tabProcessors.begin(), tabProcessors.end(), [id](const Processor &p) {
            return id == p.id();
        });
        found_it->finish_time(job.min_time_all_processors());
    }
}

void sort_processors(std::vector<Processor> &tabProcessors, int n)
{
    std::sort(tabProcessors.begin(), tabProcessors.end(), [](const Processor &j1, const Processor &j2) {
        return j1.finish_time() < j2.finish_time();
    });
}

void put_job(Job &job, std::vector<Processor> &tabProcessors, int tabProcessors_size, int &first_element_index, int &last_element_index)
{
    //adding processors for a job, then updating list of processors and sorting them in the right order

    // update first index
    first_element_index = last_element_index;

    // if we went through all processors then sort
    // update index of first element to 0 and last element to 0 + number of elements
    if (first_element_index + job.processors_needed() > tabProcessors_size)
    {
        auto start = std::chrono::steady_clock::now();

        sort_processors(tabProcessors, job.processors_needed());

        auto end = std::chrono::steady_clock::now();
        std::chrono::duration<float> time_sort_procs = end - start;
        //std::cout << "Procs sort time: " << time_sort_procs.count() << std::endl;

        first_element_index = 0;
        last_element_index = first_element_index + job.processors_needed();
    }
    else
    {
        // if we didn't go through all processors, then update index of last element to be first_el_ind + number of elements
        last_element_index = first_element_index + job.processors_needed();
    }

    std::vector<int> tabProcInd;

    // start from index of first element till the element which has index: last_element_index - 1
    for (int i = first_element_index; i < first_element_index + job.processors_needed(); i++)
    {
        tabProcInd.emplace_back(tabProcessors[i].id());
    }
    if (tabProcessors[first_element_index + job.processors_needed() - 1].finish_time() < job.ready_time())
    {
        job.min_time_all_processors(job.ready_time() + job.processing_time());
    }
    else
    {
        job.min_time_all_processors(tabProcessors[first_element_index + job.processors_needed() - 1].finish_time() + job.processing_time());
    }

    // updating processors
    for (int i = first_element_index; i < first_element_index + job.processors_needed(); i++)
    {
        tabProcessors[i].finish_time(job.min_time_all_processors());
    }

    job.on_processors(tabProcInd);
}

std::vector<Job> greedy(std::vector<Job> tabJob, std::vector<Processor> tabProcessors, size_t random_range)
{
    int lenProcessorsTab = tabProcessors.size();
    int first_element_index = 0;
    int last_element_index = 0;

    std::vector<Job> tabJobResult;
    while (!tabJob.empty())
    {
        // choosing random job
        int random_index = rand() % std::min((size_t)random_range, tabJob.size());
        tabJobResult.emplace_back(tabJob[random_index]);
        tabJob.erase(tabJob.begin() + random_index);
        //random_put_job(tabJobResult.back(), tabProcessors);
        put_job(tabJobResult.back(), tabProcessors, lenProcessorsTab, first_element_index, last_element_index);
        //std::cout << tabJobResult.back().to_string() << std::endl;
    }

    return tabJobResult;
}