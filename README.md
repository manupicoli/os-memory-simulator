# Simulador de Gerenciamento de Memória

Este simulador foi desenvolvido em C++ para fins acadêmicos, focado no estudo e visualização de técnicas de gerenciamento de memória utilizadas por sistemas operacionais. O programa oferece uma interface de linha de comando (CLI) para interagir com duas abordagens fundamentais de alocação de memória:

1.  **Alocação Contígua:** Simula a alocação de processos em blocos contínuos de memória, implementando os seguintes algoritmos de ajuste (fitting algorithms):
    * First-Fit
    * Best-Fit
    * Worst-Fit
    * Circular-Fit (Next-Fit)
2.  **Paginação Pura:** Simula a divisão do espaço de endereçamento lógico de um processo em páginas de tamanho fixo, que são alocadas em molduras de página (frames) na memória física.

O objetivo é fornecer uma ferramenta interativa que demonstre o funcionamento de cada método de gerenciamento.

* **Linguagem de Programação:** **C++**, utilizando o padrão **C++17** para aproveitar recursos modernos da linguagem.
* **Interface:** A interação com o simulador é feita inteiramente via **CLI (Command-Line Interface)**, garantindo portabilidade e foco na lógica dos algoritmos.

## Instruções de Compilação e Execução

Para compilar e executar o simulador, siga os passos abaixo.
### Pré-requisitos

Certifique-se de ter o compilador g++ instalado. Em sistemas baseados em Debian/Ubuntu, você pode instalá-lo com:

```bash
sudo apt-get update
sudo apt-get install build-essential
```

* Dentro da pasta do projeto, execute os comandos a seguir:

```bash
g++ -std=c++17 index.cpp include/Logging.cpp memory_controll/Memory.cpp memory_controll/process_controll/ProcessManagement.cpp pagination/pagination.cpp pagination/paginationProcess.cpp -o index

index
```

## Dependências e Bibliotecas

* Um compilador C++ com suporte ao padrão C++17 (ex: **g++** ou **Clang**).
* A **Biblioteca Padrão do C++** (Standard Library).

## Estrutura do Projeto

O projeto está organizado de forma modular para separar as diferentes responsabilidades da aplicação, como a lógica de cada tipo de alocação, as estruturas de dados e os controles centrais de memória e processos.

```
.
├── index.cpp                   # Ponto de entrada principal da aplicação (contém a função main e o menu)
│
├── contiguos_allocation/       # Módulo da simulação de Alocação Contígua
│   ├── ContiguousAllocation.cpp
│   └── ContiguousAllocation.hpp
│
├── pagination/                 # Módulo da simulação de Paginação Pura
│   ├── pagination.cpp
│   ├── Pagination.hpp
│   ├── paginationProcess.cpp
│   └── PaginationProcess.hpp
│
├── memory_controll/            # Componentes centrais para gerenciar a memória e processos
│   ├── Memory.cpp
│   ├── Memory.hpp
│   └── process_controll/
│       ├── ProcessManagement.cpp
│       └── ProcessManagement.hpp
│
├── data_structures/            # Definições de estruturas de dados base
│   ├── Block.hpp               # Representa um bloco de memória (livre ou ocupado)
│   └── Process.hpp             # Representa um processo a ser alocado
│
├── include/                    # Módulos e utilitários gerais
│   ├── logging.cpp
│   └── Logging.hpp
│
├── .gitignore                  # Arquivo para ignorar arquivos e pastas no Git (ex: executáveis)
└── README.md                   # Documentação do projeto (este arquivo)
```
## Decisões de Projeto e Arquitetura

#### Prioridades: organização, manutenibilidade e clareza do código. 

As principais decisões arquiteturais adotadas foram:

### 1. Arquitetura Modular e Separação de Responsabilidades

O projeto foi dividido em módulos distintos: desacopla o código e facilita o desenvolvimento e a manutenção.

### 2. Abordagem Orientada a Objetos (OOP)

Mapeamento de conceitos do domínio do problema (gerenciamento de memória) para entidades de software.

### 3. Centralização das Estruturas de Dados (Modelos)

O diretório `data_structures/` foi criado para abrigar as definições de `Process` e `Block`. Dessa forma, tanto o módulo de alocação contígua quanto o de paginação podem reutilizar essas estruturas, seguindo o princípio DRY (Don't Repeat Yourself).

## Screenshots 

![texto alternativo](caminho/para/imagem.png)
![texto alternativo](caminho/para/imagem.png)
![texto alternativo](caminho/para/imagem.png)

## Integrantes

* *Fernanda Japur Ihjaz*
* *Manuela Picoli Antunes*