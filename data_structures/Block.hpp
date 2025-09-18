#ifndef BLOCK_HPP
#define BLOCK_HPP

#include <string>

struct Block {
    int start;
    int size;
    bool free;
    int processId;

    Block(int start, int size, bool free = true, int processId = -1)
        : start(start), size(size), free(free), processId(processId) {
    }
};

#endif