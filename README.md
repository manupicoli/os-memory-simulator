# Memory Allocation Simulator

A C++ simulator for studying memory management techniques:
- Contiguous Allocation (First-Fit, Best-Fit, Worst-Fit, Circular-Fit)
- Pure Paging

## Como executar o simulador

Compile o programa utilizando o **g++** (com suporte a C++17 ou superior):

```bash
g++ -std=c++17 index.cpp include/Logging.cpp memory_controll/Memory.cpp memory_controll/process_controll/ProcessManagement.cpp pagination/pagination.cpp pagination/paginationProcess.cpp -o index

index
```
