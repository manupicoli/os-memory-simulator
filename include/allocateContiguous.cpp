#include "ContiguousAllocation.hpp"
#include "ManagesProcess.hpp"
#include "Logging.hpp"

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
                logging(LogLevel::INFO, "Algoritmo First-Fit selecionado");

                cout << "\n- - - - - - INICIANDO SIMULAÇÃO - - - - - -\n";
                logging(LogLevel::INFO, "Modo: ALOCAÇÃO CONTÍGUA.");
                logging(LogLevel::INFO, "Algoritmo de Alocação: First-Fit.");

                allocateContiguousFirstFit();

                break;
            case 2:
                logging(LogLevel::INFO,"Algoritmo Best-Fit selecionado.");

                cout << "\n- - - - - - INICIANDO SIMULAÇÃO - - - - - -\n";
                logging(LogLevel::INFO, "Modo: ALOCAÇÃO CONTÍGUA.");
                logging(LogLevel::INFO, "Algoritmo de Alocação: Best-Fit.");

                // allocateContiguousBestFit();
                break;
            case 3:
                logging(LogLevel::INFO,"Algoritmo Worst-Fit selecionado.");

                cout << "\n- - - - - - INICIANDO SIMULAÇÃO - - - - - -\n";
                logging(LogLevel::INFO, "Modo: ALOCAÇÃO CONTÍGUA.");
                logging(LogLevel::INFO, "Algoritmo de Alocação: Worst-Fit.");

                // allocateContiguousWorstFit();
                break;
            case 4:
                logging(LogLevel::INFO,"Algoritmo Circular-Fit selecionado.");

                cout << "\n- - - - - - INICIANDO SIMULAÇÃO - - - - - -\n";
                logging(LogLevel::INFO, "Modo: ALOCAÇÃO CONTÍGUA.");
                logging(LogLevel::INFO, "Algoritmo de Alocação: Circular-Fit.");

                // allocateContiguousCircularFit();
                break;
            case 5:
                logging(LogLevel::INFO,"Voltando ao menu principal...");
                break;
            default:
                logging(LogLevel::INFO,"Opção inválida, tente novamente.");
        }
    } while (option != 5);

}