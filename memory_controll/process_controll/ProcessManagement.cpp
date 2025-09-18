#include "ProcessManagement.hpp"
#include "../../include/Logging.hpp"
#include "../process_controll/ProcessManagement.hpp"

#include <iostream>
#include <iomanip>
#include <string>
#include <algorithm>

using namespace std;

vector<Process> processList;
int nextId = 1;

int menuProcess(Memory& mem) {
    int option = 0;
    do {
        cout << "\n==============================================" << endl;
        cout << "       MENU DE PROCESSOS (" << mem.getStrategyName() << ")" << endl;
        cout << "==============================================" << endl << endl;

        cout << "  [1] Criar Processo" << endl;
        cout << "  [2] Deletar Processo" << endl;
        cout << "  [3] Listar Processos" << endl;
        cout << "  [4] Mostrar Memoria" << endl;
        cout << "  [5] Voltar ao menu anterior" << endl << endl;

        cout << "Digite sua opcao: ";
        cin >> option;
        cout << endl;

        switch (option) {
        case 1:
            createProcess(mem);
            break;
        case 2:
            deleteProcess(mem);
            break;
        case 3:
            listProcesses();
            break;
        case 4:
            mem.showMemory();
            break;
        case 5:
            logging(LogLevel::INFO, "Voltando ao menu anterior...");
            nextId = 1;
            processList.clear();
            break;
        default:
            logging(LogLevel::WARN, "Opcao invalida! Tente novamente.");
        }

    } while (option != 5);

    return 0;
}

void createProcess(Memory& mem) {
    Process p;
    cout << "Digite o nome do processo: ";
    cin >> p.name;
    cout << "Digite o tamanho do processo (KB): ";
    cin >> p.size;
    p.id = nextId++;

    if (mem.allocate(p, p.size)) {
        p.allocated = true;
        processList.push_back(p);
        logging(LogLevel::INFO, "Processo \"" + p.name + "\" (" + to_string(p.size) + " KB) alocado com sucesso!");
    }
    else {
        nextId--;
        logging(LogLevel::WARN, "Nao foi possivel alocar o processo \"" + p.name + "\". Memoria insuficiente ou fragmentada.");
    }
}

void deleteProcess(Memory& mem) {
    int id;
    cout << "Digite o ID do processo a ser removido: ";
    cin >> id;

    auto it = find_if(processList.begin(), processList.end(), [id](const Process& p) { return p.id == id; });

    if (it != processList.end()) {
        mem.deallocate(id);
        logging(LogLevel::INFO, "Processo \"" + it->name + "\" desalocado da memoria.");
        processList.erase(it);
    }
    else {
        logging(LogLevel::ERROR, "Processo com ID " + to_string(id) + " nao encontrado.");
    }
}

void listProcesses() {
    if (processList.empty()) {
        cout << "\nNenhum processo criado ainda.\n";
        return;
    }

    cout << "\n====================== PROCESSOS CRIADOS ======================" << endl;
    cout << left
        << setw(5) << "ID"
        << setw(20) << "Nome"
        << setw(10) << "Tamanho"
        << setw(10) << "Alocado"
        << setw(12) << "Inicio"
        << setw(12) << "Fim" << endl;
    cout << "----------------------------------------------------------------" << endl;

    for (const auto& p : processList) {
        cout << left
            << setw(5) << p.id
            << setw(20) << p.name
            << setw(10) << p.size
            << setw(10) << (p.allocated ? "Sim" : "Nao")
            << setw(12) << (p.allocated ? to_string(p.startAddress) : "-")
            << setw(12) << (p.allocated ? to_string(p.endAddress) : "-") << endl;
    }

    cout << "================================================================" << endl;
}
