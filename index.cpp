#include <iostream>
#include "contiguos_allocation/ContiguousAllocation.hpp"
#include "include/Pagination.hpp"

using namespace std;

int main() {
    int option = 0;
    do {
        cout << "\n==============================================" << endl;
        cout << "   SIMULADOR DE GERENCIAMENTO DE MEMORIA" << endl;
        cout << "==============================================" << endl;
        cout << endl;

        cout << "Escolha o modo de simulacao:" << endl << endl;

        cout << "  [1] Alocacao Contigua Dinamica" << endl;
        cout << "  [2] Paginacao Pura" << endl;
        cout << "  [3] Sair" << endl;

        cout << endl << "Digite sua opcao: ";
        cin >> option;

        cout << endl;

        switch (option) {
        case 1:
            allocateContiguous();
            break;
        case 2:
            memoryPagination();
            break;
        case 3:
            cout << ">>> Encerrando simulador..." << endl;
            break;
        default:
            cout << ">>> Opção invalida, tente novamente." << endl;
        }

        cout << endl;

    } while (option != 3);

    return 0;
}