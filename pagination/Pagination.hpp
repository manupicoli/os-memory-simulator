#ifndef PAGINATION_HPP //ifndef é pra verificar se ALLOCCONTIGUOUS_HPP está definido
#define PAGINATION_HPP //define, se não estava

#include <vector>

struct PageEntry {
    int pageNumber;
    int frameNumber;
};

struct Process {
    string pid;
    int sizeKB;
    int numPages;
    vector<PageEntry> pageTable;
};

void pagination();

#endif //finaliza o ifndef