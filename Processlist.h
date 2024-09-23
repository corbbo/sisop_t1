#ifndef PROCESSLIST_HPP
#define PROCESSLIST_HPP

#include "Process.h"
#include <list>
class ProcessList {
public:
    std::list<Process>::iterator it;
    ProcessList();
    void add(Process p);
    void sort(int n);
    void print();
    Process top();
    Process erase(std::list<Process>::iterator p_it);
    Process pop_front();
    std::list<Process>::iterator begin();
    std::list<Process>::iterator end();
private:
    std::list<Process> processos; //mapa que armazena processos
};

#endif // PROCESSLIST_HPP