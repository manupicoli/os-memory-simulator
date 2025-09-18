#include "Pagination.hpp"
#include "Process.hpp"
#include "../include/Logging.hpp"

#include <iostream>
#include <sstream>
#include <cmath>
#include <unordered_map>
#include <iomanip>

using namespace std;

int totalMemory;
int pageSize;
int numFrames;

unordered_map<string, PaginationProcess> processes;
vector<string> frames;

static void allocateProcess(PaginationProcess &newProcess);
static bool hasFreeFrames(int needed);
static void verifyNewProcess();
static void removeProcess();
static void viewPageTable();
static void viewMetrics();

void printSeparator() {
    cout << string(60, '-') << "\n";
}

void pagination() {
    int option = 0;
    totalMemory = 1024;

    logging(LogLevel::INFO, "Iniciando simulador de memoria...");
    logging(LogLevel::INFO, "Modo: Paginacao Pura!");

    logging(LogLevel::ACTION, "Digite o tamanho total da memoria: ");
    cin >> totalMemory;

    logging(LogLevel::ACTION, "Digite o tamanho da pagina (em KB): ");
    cin >> pageSize;

    logging(LogLevel::INFO, "Memoria Total: " + to_string(totalMemory) + " KB");
    logging(LogLevel::INFO, "Configuracao do Sistema de Paginacao:");

    numFrames = totalMemory / pageSize;
    frames.assign(numFrames, "...."); // inicializa os frames vazios

    logging(LogLevel::INFO, "Numero de frames disponivel: " + to_string(numFrames) + " (Memoria / Tamanho da pagina)");
    showFrames(frames);

    do {
        cout << "O que voce deseja fazer?\n"
        << "1. Criar novo processo\n"
        << "2. Remover processo\n"
        << "3. Visualizar tabela de paginas\n"
        << "4. Visualizar metricas\n"
        << "5. Voltar para o menu principal:\n"
        << "Digite sua opcao: ";

        cin >> option;

        switch (option) {
            case 1:
                verifyNewProcess();
                break;
            case 2:
                removeProcess();
                break;
            case 3:
                viewPageTable();
                break;
            case 4:
                viewMetrics();
                break;
            case 5:
                logging(LogLevel::INFO, "Voltando ao menu principal...");
                break;
            default:
                logging(LogLevel::INFO, "Opcao invalida, tente novamente.");
        }
    
    } while (option != 5);
}

void viewMetrics() {
    int usedFrames = 0;
    for (auto &f : frames) {
        if (f != "....") usedFrames++;
    }

    double occupancy = ((double)usedFrames / numFrames) * 100;
    
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(2) << occupancy;

    printSeparator();

    logging(LogLevel::METRICS, "Ocupacao da Memoria: " 
        + to_string(usedFrames) + "/" 
        + to_string(numFrames) + " frames usados ("
        + oss.str() + "%)");

    logging(LogLevel::METRICS, "Fragmentacao Externa: 0 KB (nao existe em paginacao)");

    int totalInternalFrag = 0;

    logging(LogLevel::METRICS, "Fragmentacao Interna:");

    for (auto& pair : processes) {
        PaginationProcess& p = pair.second;
        int lastPageUsedKB = p.sizeKB % pageSize;
        int internalFrag = lastPageUsedKB == 0 ? 0 : pageSize - lastPageUsedKB;
        totalInternalFrag += internalFrag;

        cout << p.pid << ": Ultima pagina usou " 
             << (lastPageUsedKB == 0 ? pageSize : lastPageUsedKB)
             << " KB de " << pageSize << " KB (Sobrou " 
             << internalFrag << " KB internos)\n";
    }

    logging(LogLevel::METRICS, "Total Fragmentacao Interna: " + to_string(totalInternalFrag) + " KB");
    printSeparator();
}

void viewPageTable() {
    string processPid;

    printSeparator();

    cout << "Digite o nome (PID) do processo que deseja inspecionar: ";
    cin >> processPid;

    printSeparator();

    auto it = processes.find(processPid);
    if (it == processes.end()) {
        logging(LogLevel::ERROR, "Processo nao encontrado!");
        printSeparator();
        return;
    }

    PaginationProcess& p = it->second;
    int lastPageUsedKB = p.sizeKB % pageSize;
    int internalFrag = lastPageUsedKB == 0 ? 0 : pageSize - lastPageUsedKB;

    cout << "[PAGE TABLE] Processo " << p.pid 
         << " (" << p.numPages << " paginas, " << p.sizeKB << " KB)\n";

    for (auto& entry : p.pageTable) {
        cout << "Pagina " << entry.pageNumber << " -> Frame " << entry.frameNumber << "\n";
    }

    cout << "Fragmentacao Interna: " << internalFrag 
         << " KB (ultima pagina ocupou "
         << (lastPageUsedKB == 0 ? pageSize : lastPageUsedKB)
         << " KB do frame)\n";

    printSeparator();
}


void removeProcess() {
    string processPid;

    printSeparator();

    cout << "Digite o nome (PID) do processo que deseja remover: ";
    cin >> processPid;

    logging(LogLevel::ACTION, "Removendo processo: " + processPid);

    auto it = processes.find(processPid);
    if (it != processes.end()) {
        for (auto& entry : it->second.pageTable) {
            if (entry.frameNumber >= 0 && entry.frameNumber < frames.size()) {
                frames[entry.frameNumber] = "....";
            }
        }

        it->second.pageTable.clear();
        processes.erase(it);

        vector<int> freedFrames;
        for (auto& entry : it->second.pageTable) {
            frames[entry.frameNumber] = "....";
            freedFrames.push_back(entry.frameNumber);
        }

        ostringstream msg;
        msg << "Processo " << processPid << " removido. Frames liberados: ";

        for (size_t i = 0; i < freedFrames.size(); i++) {
            msg << freedFrames[i] << (i < freedFrames.size() - 1 ? ", " : "");
        }

        logging(LogLevel::SUCCESS, msg.str());
        showFrames(frames);
    } else {
        logging(LogLevel::ERROR, "Processo " + processPid + " nao encontrado!");
    }

    printSeparator();
}

void allocateProcess(PaginationProcess &newProcess){
    int allocated = 0;
    for (int i = 0; i < frames.size() && allocated < newProcess.numPages; i++) {
        if (frames[i] == "....") {
            frames[i] = newProcess.pid + "-" + std::to_string(allocated);
            newProcess.pageTable.push_back({allocated, i});

            logging(LogLevel::SUCCESS, "Pagina " + to_string(allocated) + " -> Frame " + to_string(i));
            allocated++;
        }
    }

    processes[newProcess.pid] = newProcess;
}

bool hasFreeFrames(int needed) {
    int freeFrames = 0;
    for (auto &f : frames) if (f == "....") freeFrames++;
    return freeFrames >= needed;
}

void verifyNewProcess() {
    string processPid;
    int processSize;

    printSeparator();

    cout << "Digite o nome do processo: ";
    cin >> processPid;
    cout << "Digite o tamanho do processo (KB): ";
    cin >> processSize;

    int pages = ceil((double)processSize / pageSize);

    logging(LogLevel::ACTION, "Criando Processo " + processPid + " (Tamanho: " + to_string(processSize) + " KB)...");
    logging(LogLevel::INFO, processPid + " necessita de " + to_string(pages) + " paginas.");

    if (!hasFreeFrames(pages)) {
        logging(LogLevel::ERROR, "Nao ha frames suficientes para criar esse processo!");
        return;
    }

    PaginationProcess p = createNewProcess(processPid, processSize, pageSize);
    allocateProcess(p);

    logging(LogLevel::SUCCESS, "Processo criado com sucesso!");
    showFrames(frames);
    printSeparator();
}