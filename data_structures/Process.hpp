#ifndef PROCESS_HPP
#define PROCESS_HPP

#include <string>

struct Process {
    int id;
    std::string name;
    int size;
    int startAddress;
    int endAddress;
    bool allocated = false;
};

#endif