#ifndef PROCESS_HPP
#define PROCESS_HPP

#include <string>
#include <vector>

struct PageEntry {
    int pageNumber;
    int frameNumber;
};

struct Process {
    std::string pid;
    int sizeKB;
    int numPages;
    std::vector<PageEntry> pageTable;
};

Process createProcess(const std::string& pid, int sizeKB, int pageSizeKB);
void removeProcess(Process& p);
void viewPageTable();
void showFrames();
void viewMetrics();


#endif