#include "processor.h"

Processor::Processor(int _id):
    m_id{_id},
    m_finish_time{0}
{}

void Processor::finish_time(int _finish_time){
    m_finish_time = _finish_time;
}

int Processor::finish_time() const{
    return m_finish_time;
}

int Processor::id() const{
    return m_id;
}

std::string Processor::to_string() const{
    return std::to_string(m_id) + ": m_finish_time=" + std::to_string(m_finish_time);
}

