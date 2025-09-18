#include "Process.hpp"
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

// void removeProcess(PaginationProcess& p) {
//     for (auto& entry : p.pageTable) {
//         entry.frameNumber = -1;
//     }
// }

// void viewPageTable() {

// }


// void viewMetrics() {

// }