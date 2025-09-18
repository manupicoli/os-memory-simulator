#include "PaginationProcess.hpp"
#include "../include/Logging.hpp"

#include <sstream>
#include <iostream>
#include <string>
#include <cmath>

void showFrames(const std::vector<std::string>& frames) {
    logging(LogLevel::VISUAL, "Estado Atual da Memoria (Frames):");

    for (int i = 0; i < frames.size(); i++) {
        std::cout << "Frame[" << i << "]: ";

        if (frames[i] == "....") {
            std::cout << "[....]";
        } else {
            std::cout << "[" << frames[i] << "]";
        }

        std::cout << "\n";
    }
}

PaginationProcess createNewProcess(const std::string& pid, int sizeKB, int pageSizeKB) {
    PaginationProcess p;
    p.pid = pid;
    p.sizeKB = sizeKB;
    p.numPages = ceil((double)sizeKB / pageSizeKB);

    return p;
}

void viewPageTable(const PaginationProcess& p, int pageSize) {
    int lastPageUsedKB = p.sizeKB % pageSize;
    int internalFrag = lastPageUsedKB == 0 ? 0 : pageSize - lastPageUsedKB;

    std::cout << "[PAGE TABLE] Processo " << p.pid 
              << " (" << p.numPages << " paginas, " << p.sizeKB << " KB)\n";

    for (auto& entry : p.pageTable) {
        std::cout << "Pagina " << entry.pageNumber << " -> Frame " << entry.frameNumber << "\n";
    }

    std::cout << "Fragmentacao Interna: " << internalFrag 
              << " KB (ultima pagina ocupou "
              << (lastPageUsedKB == 0 ? pageSize : lastPageUsedKB)
              << " KB do frame)\n";
}