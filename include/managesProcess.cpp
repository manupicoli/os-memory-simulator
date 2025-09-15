#include <iostream>
#include <string>
#include <vector>

#include "Logging.hpp"

using namespace std;
vector<struct Process> processList;

struct Process {
    string name;
    int size;
};

void createProcess();
void listProcesses();

int menuProcess() {
    int option = 0;
    do {
        cout << "\n- - - - - - - - - - - - - - - - - - - -\n";
        cout << "\nO que deseja fazer?:\n";
        cout << "1. Criar Processo\n";
        cout << "2. Deletar Processo\n";
        cout << "3. Listar Processos\n";
        cout << "4. Voltar ao menu anterior\n";
        cout << "Digite sua opção: ";
        cin >> option;

        switch(option) {
            case 1: 
                createProcess(); 
                break;
            case 2: 
                // deleteProcess(); 
                break;
            case 3: 
                listProcesses();
                break;
            case 4:
                cout << "Voltando ao menu anterior...\n"; 
                break;
            default: 
                cout << "Opção inválida!\n";
        }
    } while(option != 3);

    return 0;
}

void createProcess() {
    Process p;
    cout << "Digite o nome do processo: ";
    cin >> p.name;
    cout << "Digite o tamanho do processo: ";
    cin >> p.size;

    processList.push_back(p);
    logging(
        LogLevel::INFO,
        "Processo \"" + p.name + "\" de tamanho " + std::to_string(p.size) + " criado com sucesso!"
    );
}

void listProcesses() {
    cout << "\nProcessos criados:\n";
    for (const auto& p : processList) {
        logging(
            LogLevel::INFO,
            "Nome: " + p.name + " | Tamanho: " + to_string(p.size)
        );
    }
}