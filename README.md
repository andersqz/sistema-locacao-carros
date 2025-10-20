# sistema-locacao-carros
Sistema desenvolvido em C++ de locação de carros com pré cadastro de locatário modularizado em funções em arquivos separados para trabalho da cadeira de Algoritmos B da faculdade de SI.

## Funcionalidades
- Cadastro de locatários (nome, CPF, endereço)
- Cadastro de carros (modelo, placa, cor, ano e valor)
- Aluguel de veículos com verificação de disponibilidade
- Listagem de carros cadastrados
- Armazenamento de dados em arquivos `.txt`

##  Tecnologias
- Linguagem: **C++**
- Manipulação de arquivos (`fstream`)
- Estruturas de dados (`struct`, `vector`)
- Funções e modularização

##  Como executar
1. Compile todos os arquivos:
   g++ main.cpp funcoes.cpp -o roda
