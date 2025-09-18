#ifndef MEMORY_HPP
#define MEMORY_HPP

#include "../data_structures/Block.hpp"
#include "../data_structures/Process.hpp"
#include "../include/Logging.hpp"
#include <vector>
#include <string>

enum class AllocationStrategy {
    FirstFit,
    BestFit,
    WorstFit,
    CircularFit
};

class Memory {
private:
    int totalSize;
    std::vector<Block> blocks;
    AllocationStrategy strategy;
    size_t lastIndex = 0;

public:
    Memory(int size, AllocationStrategy strat);

    bool allocate(Process& p, int size);
    bool allocateFirstFit(Process& p, int size);
    bool allocateBestFit(Process& p, int size);
    bool allocateWorstFit(Process& p, int size);
    bool allocateCircularFit(Process& p, int size);
    double calculateExternalFragmentation();
    void deallocate(int processId);
    void showMemory();

    int getTotalSize() const { return totalSize; }
    std::string getStrategyName() const;
};

#endif
