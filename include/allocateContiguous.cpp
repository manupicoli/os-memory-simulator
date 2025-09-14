#include "ContiguousAllocation.hpp"
#include <iostream>

using namespace std;

void allocateContiguous() {
    int option = 0;
    do {
        cout << "\n- - - - - - ALOCAÇÃO CONTÍGUA - - - - - -\n";
        cout << "\nEscolha o modo de simulação:\n";
        cout << "1. First-Fit\n";
        cout << "2. Best-Fit\n";
        cout << "3. Worst-Fit\n";
        cout << "4. Circular-Fit:\n";
        cout << "5. Voltar para o menu principal:\n";
        cout << "Digite sua opção: ";
        cin >> option;

        switch (option) {
            case 1:
                cout << "Algoritmo First-Fit selecionado.\n";
                // allocateContiguousFirstFit();
                break;
            case 2:
                cout << "Algoritmo Best-Fit selecionado.\n";
                // allocateContiguousBestFit();
                break;
            case 3:
                cout << "Algoritmo Worst-Fit selecionado.\n";
                // allocateContiguousWorstFit();
                break;
            case 4:
                cout << "Algoritmo Circular-Fit selecionado.\n";
                // allocateContiguousCircularFit();
                break;
            case 5:
                cout << "Voltando ao menu principal...\n";
                break;
            default:
                cout << "Opção inválida, tente novamente.\n";
        }
    } while (option != 5);

}