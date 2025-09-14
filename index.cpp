#include <iostream>
#include "include/ContiguousAllocation.hpp"

using namespace std;

int main() {
    int option = 0;
    do {
        cout << "\n- - - - - SIMULADOR DE GERENCIAMENTO DE MEMÓRIA - - - - -\n";
        cout << "\nEscolha o modo de simulação:\n";
        cout << "1. Alocação Contígua Dinâmica\n";
        cout << "2. Paginação Pura\n";
        cout << "3. Sair\n";
        cout << "\nDigite sua opção: ";
        cin >> option;

        switch (option) {
            case 1:
                allocateContiguous();
                break;
            case 2:
                // ALocação por paginação pura
                break;
            case 3:
                cout << "Encerrando simulador...\n";
                break;
            default:
                cout << "Opção inválida, tente novamente.\n";
        }
    } while (option != 3);

    return 0;
}