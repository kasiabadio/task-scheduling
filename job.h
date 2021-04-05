#ifndef JOB_H_
#define JOB_H_
#include <vector>
#include <string>

class Job{
    int m_id;
    int m_ready_time;
    int m_processing_time;
    int m_processors_needed;
    std::vector<int> m_on_processors; //we set this
    int m_min_time_all_processors; // we set this
    

public:
    Job(int _id, int _ready_time, int _processing_time, int _processors_needed);
    // 0-id, 1-ready_time, 3-processing_time, 4-processors_needed, 2-wait_time
    Job(std::vector<int> tabJob);
    int id() const;
    int ready_time() const;
    int processing_time() const;
    int processors_needed() const;
    int wait_time() const;
    int min_time_all_processors() const;
    std::vector<int> on_processors() const;
    void min_time_all_processors(int _min_time_all_processors);
    void on_processors(const std::vector<int> &_on_processors);
    std::string to_string() const;
    std::string to_string_out() const;


};


#endif //JOB_H_