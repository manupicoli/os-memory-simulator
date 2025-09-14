#include "Pagination.hpp"
#include <iostream>

using namespace std;

void memoryPagination() {
    int option = 0;
    do {
        cout << "\n- - - - - - PAGINACAO - - - - - -\n"
        << "\nO que voce deseja fazer?\n"
        << "1. Criar novo processo\n"
        << "2. Remover processo\n"
        << "3. Visualizar tabela de paginas\n"
        << "4. Visualizar metricas\n"
        << "5. Voltar para o menu principal:\n"
        << "Digite sua opção: ";

        cin >> option;

        switch (option) {
            case 1:
                cout << "Criacao de novo processo selecionada\n";
                // createProccess();
                break;
            case 2:
                cout << "Remocao de processo da memoria selecionada.\n";
                // removeProccess();
                break;
            case 3:
                cout << "Visualizacao de tabela de paginas selecionada\n";
                // viewPageTable();
                break;
            case 4:
                cout << "Visualizacao de metricas selecionada\n";
                // viewMetrics();
                break;
            case 5:
                cout << "Voltando ao menu principal...\n";
                break;
            default:
                cout << "Opcao inválida, tente novamente.\n";
        }
    } while (option != 5);
}