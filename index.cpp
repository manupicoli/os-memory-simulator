#include <iostream>
#include "include/ContiguousAllocation.hpp"
#include "include/Pagination.hpp"

using namespace std;

int main() {
    int option = 0;
    do {
        cout << "\n- - - - - SIMULADOR DE GERENCIAMENTO DE MEMORIA - - - - -\n"
        << "\nEscolha o modo de simulacao:\n"
        << "1. Alocacao Contigua Dinamica\n"
        << "2. Paginacao pura\n"
        << "3. Sair\n"
        << "\nDigite sua opcao: ";

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
                cout << "Opcao invalida, tente novamente.\n";
        }
    } while (option != 3);

    return 0;
}