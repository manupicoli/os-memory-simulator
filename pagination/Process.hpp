#ifndef PROCESS_HPP
#define PROCESS_HPP

#include <string>
#include <vector>

struct PageEntry {
    int pageNumber;
    int frameNumber;
};

struct PaginationProcess {
    std::string pid;
    int sizeKB;
    int numPages;
    std::vector<PageEntry> pageTable;
};

PaginationProcess createNewProcess(const std::string& pid, int sizeKB, int pageSizeKB);
void showFrames(const std::vector<std::string>& frames);
void viewPageTable(const PaginationProcess& p, int pageSize);

#endif