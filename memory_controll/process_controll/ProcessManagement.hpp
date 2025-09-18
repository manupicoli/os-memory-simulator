#ifndef PROCESSMANAGEMENT_HPP
#define PROCESSMANAGEMENT_HPP

#include "../../data_structures/Process.hpp"
#include "../Memory.hpp"
#include <vector>

extern std::vector<Process> processList;

int menuProcess(Memory& mem);
void createProcess(Memory& mem);
void deleteProcess(Memory& mem);
void listProcesses();

#endif