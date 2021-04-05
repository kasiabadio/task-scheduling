#ifndef PROCESSOR_H_
#define PROCESSOR_H_
#include <string>

class Processor{
    int m_id;
    int m_finish_time; // we set this


public:
    Processor(int _id);
    void finish_time(int _finish_time);
    int id() const;
    int finish_time() const;
    std::string to_string() const;

};

#endif //PROCESSOR_H_