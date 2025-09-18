#include "ContiguousAllocation.hpp"

#include "../include/Logging.hpp"
#include "../memory_controll/Memory.hpp"
#include "../memory_controll/process_controll/ProcessManagement.hpp"

#include <iostream>
#include <string>
#include <vector>

using namespace std;

Memory createMemory(AllocationStrategy strategy);

static void firstFit();
static void bestFit();
static void worstFit();
static void circularFit();

static void logSelectedAlgorithm(const string& algorithm);

static void allocateContiguous() {
    int option = 0;
    do {
        cout << "\n==============================================" << endl;
        cout << "          ALOCACAO CONTIGUA" << endl;
        cout << "==============================================" << endl << endl;

        cout << "Escolha o algoritmo de alocacao:" << endl << endl;
        cout << "  [1] First-Fit" << endl;
        cout << "  [2] Best-Fit" << endl;
        cout << "  [3] Worst-Fit" << endl;
        cout << "  [4] Circular-Fit" << endl;
        cout << "  [5] Voltar para o menu principal" << endl << endl;

        cout << "Digite sua opcao: ";
        cin >> option;

        if (!(option)) {
            cin.clear(); 
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            option = 0; 
        }

        cout << endl;

        switch (option) {
        case 1:
            firstFit();
            break;
        case 2:
            bestFit();
            break;
        case 3:
            worstFit();
            break;
        case 4:
            circularFit();
            break;
        case 5:
            logging(LogLevel::INFO, "Voltando ao menu principal...");
            break;
        default:
            logging(LogLevel::INFO, "Opcao invalida, tente novamente.");
        }

    } while (option != 5);
}

Memory createMemory(AllocationStrategy strategy) {
    int memorySize;
    cout << "\nDigite o tamanho total da memoria: ";
    cin >> memorySize;

    Memory mem(memorySize, strategy);
    return mem;
}

void firstFit() {
    AllocationStrategy strategy = AllocationStrategy::FirstFit;
    logSelectedAlgorithm("FIRST FIT");

    Memory mem = createMemory(strategy);
    menuProcess(mem);
}

void bestFit() {
    AllocationStrategy strategy = AllocationStrategy::BestFit;
    logSelectedAlgorithm("BEST FIT");

    Memory mem = createMemory(strategy);
    menuProcess(mem);
}

void worstFit() {
    AllocationStrategy strategy = AllocationStrategy::WorstFit;
    logSelectedAlgorithm("WORST FIT");

    Memory mem = createMemory(strategy);
    menuProcess(mem);
}

void circularFit() {
    AllocationStrategy strategy = AllocationStrategy::CircularFit;
    logSelectedAlgorithm("CIRCULAR FIT");

    Memory mem = createMemory(strategy);
    menuProcess(mem);
}

static void logSelectedAlgorithm(const string& algorithm) {
    cout << endl;
    logging(LogLevel::INFO, "Modo selecionado: ALOCACAO CONTIGUA");
    logging(LogLevel::INFO, "Algoritmo " + algorithm + " selecionado");
    cout << "\n==============================================" << endl;
    cout << "          INICIANDO SIMULACAO" << endl;
    cout << "==============================================" << endl << endl;
}
