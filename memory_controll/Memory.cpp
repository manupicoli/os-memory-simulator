#include "Memory.hpp"
#include <iostream>
#include <climits>
#include <iomanip>

using namespace std;

Memory::Memory(int size, AllocationStrategy strat) {
    totalSize = size;
    strategy = strat;
    blocks.push_back(Block(0, size, true));
    logging(LogLevel::INFO, "Memoria criada com tamanho: " + to_string(size) + " KB");
}

bool Memory::allocate(Process& p, int size) {
    switch (strategy) {
    case AllocationStrategy::FirstFit:    return allocateFirstFit(p, size);
    case AllocationStrategy::BestFit:     return allocateBestFit(p, size);
    case AllocationStrategy::WorstFit:    return allocateWorstFit(p, size);
    case AllocationStrategy::CircularFit: return allocateCircularFit(p, size);
    }
    return false;
}

bool Memory::allocateFirstFit(Process& p, int size) {
    int processId = p.id;

    for (size_t i = 0; i < blocks.size(); i++) {
        if (blocks[i].free && blocks[i].size >= size) {
            if (blocks[i].size == size) {
                blocks[i].free = false;
                blocks[i].processId = processId;
            }
            else {
                Block allocated(blocks[i].start, size, false, processId);
                Block remaining(blocks[i].start + size, blocks[i].size - size, true);

                blocks[i] = allocated;
                blocks.insert(blocks.begin() + i + 1, remaining);
            }

            p.startAddress = blocks[i].start;
            p.endAddress = blocks[i].start + size - 1;
            return true;
        }
    }

    return false;
}

bool Memory::allocateBestFit(Process& p, int size) {
    int processId = p.id;
    int bestIndex = -1;
    int bestSize = INT_MAX;

    for (size_t i = 0; i < blocks.size(); i++) {
        if (blocks[i].free && blocks[i].size >= size && blocks[i].size < bestSize) {
            bestSize = blocks[i].size;
            bestIndex = (int)i;
        }
    }

    if (bestIndex == -1) return false;

    if (blocks[bestIndex].size == size) {
        blocks[bestIndex].free = false;
        blocks[bestIndex].processId = processId;
    }
    else {
        Block allocated(blocks[bestIndex].start, size, false, processId);
        Block remaining(blocks[bestIndex].start + size, blocks[bestIndex].size - size, true);

        blocks[bestIndex] = allocated;
        blocks.insert(blocks.begin() + bestIndex + 1, remaining);
    }

    p.startAddress = blocks[bestIndex].start;
    p.endAddress = blocks[bestIndex].start + size - 1;
    return true;
}

bool Memory::allocateWorstFit(Process& p, int size) {
    int processId = p.id;
    int worstIndex = -1;
    int worstSize = -1;

    for (size_t i = 0; i < blocks.size(); i++) {
        if (blocks[i].free && blocks[i].size >= size && blocks[i].size > worstSize) {
            worstSize = blocks[i].size;
            worstIndex = (int)i;
        }
    }

    if (worstIndex == -1) return false;

    if (blocks[worstIndex].size == size) {
        blocks[worstIndex].free = false;
        blocks[worstIndex].processId = processId;
    }
    else {
        Block allocated(blocks[worstIndex].start, size, false, processId);
        Block remaining(blocks[worstIndex].start + size, blocks[worstIndex].size - size, true);

        blocks[worstIndex] = allocated;
        blocks.insert(blocks.begin() + worstIndex + 1, remaining);
    }

    p.startAddress = blocks[worstIndex].start;
    p.endAddress = blocks[worstIndex].start + size - 1;
    return true;
}

bool Memory::allocateCircularFit(Process& p, int size) {
    int processId = p.id;
    size_t n = blocks.size();

    for (size_t offset = 0; offset < n; offset++) {
        size_t i = (lastIndex + offset) % n;

        if (blocks[i].free && blocks[i].size >= size) {
            if (blocks[i].size == size) {
                blocks[i].free = false;
                blocks[i].processId = processId;
            }
            else {
                Block allocated(blocks[i].start, size, false, processId);
                Block remaining(blocks[i].start + size, blocks[i].size - size, true);

                blocks[i] = allocated;
                blocks.insert(blocks.begin() + i + 1, remaining);
            }

            p.startAddress = blocks[i].start;
            p.endAddress = blocks[i].start + size - 1;
            lastIndex = i;
            return true;
        }
    }

    return false;
}

void Memory::deallocate(int processId) {
    for (size_t i = 0; i < blocks.size(); i++) {
        if (!blocks[i].free && blocks[i].processId == processId) {
            blocks[i].free = true;
            blocks[i].processId = -1;

            // Fundir com bloco à frente
            if (i + 1 < blocks.size() && blocks[i + 1].free) {
                blocks[i].size += blocks[i + 1].size;
                blocks.erase(blocks.begin() + i + 1);
            }

            // Fundir com bloco atrás
            if (i > 0 && blocks[i - 1].free) {
                blocks[i - 1].size += blocks[i].size;
                blocks.erase(blocks.begin() + i);
            }

            break;
        }
    }
}

double Memory::calculateExternalFragmentation() {
    int totalFree = 0;

    for (auto& b : blocks) {
        if (b.free) {
            totalFree += b.size;
        }
    }

    if (totalFree == 0) {
        return 0.0;
    }

    double fragmentation = ((double)(totalFree * 100.0) / totalSize);
    return fragmentation;
}

void Memory::showMemory() {
    cout << "\n--- ESTADO DA MEMORIA ---\n\n";
    int pos = 0;
    int cont = 0;

    for (auto& b : blocks) {
        cout << "Bloco " << cont << "[" << pos << " - " << pos + b.size - 1 << "] "
            << "(" << b.size << "): "
            << (b.free ? "LIVRE" : "P" + to_string(b.processId))
            << "\n";
        pos += b.size;
        cont++;
    }

    cout << "\nLegenda: '.' = Livre | '#' = Ocupado\n";
    cout << "\nVisualizacao grafica:\n";

    for (auto& b : blocks) {
        char symbol = b.free ? '.' : '#';
        for (int i = 0; i < b.size; i++) cout << symbol;
        cout << "|";
    }
    cout << "\n";

    cout << fixed << setprecision(2);
    cout << "\nFragmentacao externa atual: "
        << calculateExternalFragmentation() << "%\n";
}

string Memory::getStrategyName() const {
    switch (strategy) {
    case AllocationStrategy::FirstFit:    return "First Fit";
    case AllocationStrategy::BestFit:     return "Best Fit";
    case AllocationStrategy::WorstFit:    return "Worst Fit";
    case AllocationStrategy::CircularFit: return "Circular Fit";
    }
    return "Desconhecido";
}
