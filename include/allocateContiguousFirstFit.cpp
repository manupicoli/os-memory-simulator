#include "ContiguousAllocation.hpp"
#include "ManagesProcess.hpp"
#include "Logging.hpp"

#include <iostream>

using namespace std;

void allocateContiguousFirstFit() {

    logging(LogLevel::INFO, "Processos disponíveis para alocação: " + std::to_string(processList.size()));

    // currentMemoryState();

    menuProcess();

}