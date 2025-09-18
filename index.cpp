#include <iostream>
#include <limits>

#include "contiguos_allocation/ContiguousAllocation.hpp"
#include "pagination/Pagination.hpp"

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

        if (!(option)) {
            cin.clear(); 
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            option = 0; 
        }

        switch (option) {
        case 1:
            allocateContiguous();
            break;
        case 2:
            pagination();
            break;
        case 3:
            cout << "\n==============================================" << endl;
            cout << "          ENCERRANDO SIMULADOR..." << endl;
            cout << "==============================================" << endl;
            cout << endl;
            break;
        default:
            cout << ">>> Opcao invalida, tente novamente. Digite:" << endl;
            cout << "    Entradas aceitas: 1, 2 e 3" << endl;
            cout << "    Exemplo de entrada: '1' para selecionar o modo de Alocacao Contigua Dinamica" << endl;
        }

        cout << endl;

    } while (option != 3);

    return 0;
}