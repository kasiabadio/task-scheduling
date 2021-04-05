#include "job.h"
#include <limits.h>
#include <iostream>

Job::Job(int _id, int _ready_time, int _processing_time, int _processors_needed):
    m_id{_id}, 
    m_ready_time{_ready_time},
    m_processing_time{_processing_time},
    m_processors_needed{_processors_needed},
    m_min_time_all_processors{INT_MAX}
{}
  

Job::Job(std::vector<int> tabJob):
    m_id{tabJob[0]}, 
    m_ready_time{tabJob[1]},
    m_processing_time{tabJob[3]},
    m_processors_needed{tabJob[4]},
    m_min_time_all_processors{INT_MAX}
{}

int Job::id() const{
    return m_id;
}

int Job::ready_time() const{
    return m_ready_time;
}

int Job::processing_time() const{
    return m_processing_time;
}

int Job::processors_needed() const{
    return m_processors_needed;
}


int Job::wait_time() const{
    return m_min_time_all_processors - m_ready_time - m_processing_time;
}

int Job::min_time_all_processors() const{
    return m_min_time_all_processors;
}

void Job::min_time_all_processors(int _min_time_all_processors){
    m_min_time_all_processors = _min_time_all_processors;
}

std::vector<int> Job::on_processors() const{
    return m_on_processors;
}

void Job::on_processors(const std::vector<int> &_on_processors){
    m_on_processors.clear();
    for(const auto &processor_ind: _on_processors){
        m_on_processors.emplace_back(processor_ind);
    }
}

std::string Job::to_string() const{
    return std::to_string(m_id) + ": ready_time=" + std::to_string(m_ready_time) +
    " proccessing_time=" + std::to_string(m_processing_time) +
    " processors_needed=" + std::to_string(m_processors_needed) +
    " wait_time=" + std::to_string(wait_time()) +
    " min_time_all_processors=" + std::to_string(m_min_time_all_processors);
}


std::string Job::to_string_out() const{
    int start_time = m_ready_time + wait_time();
    int end_time = m_min_time_all_processors;
    return std::to_string(m_id) + " " + std::to_string(start_time) + " " +
    std::to_string(end_time);
}