// ============ funcoes.h ============
#ifndef FUNCOES_H   // Evita inclusão duplicada
#define FUNCOES_H

#include <iostream>
#include <string>
#include <algorithm>
#include <fstream>
#include <ctime>
#include <sstream>
#include <vector>
#include <clocale>
#include <limits>

using namespace std;

// ======== STRUCTS ========

// Estrutura do tipo Carro
typedef struct {
    string placa;
    string horaEntrada;
    float valor;
    int ano;
    string cor;
    bool alugado;
    string modelo;
} Carro;

// Estrutura do tipo Pessoa (locatário)
typedef struct {
    string nome;
    string cpf;
    string endereco;
} Pessoa;

// ======== PROTÓTIPOS ========
string dataHoraAtual();
bool validarCpf(string cpf);
bool usuarioExiste(string cpf);
Pessoa cadastroPessoa();
void cadastrarCarro();
void listarCarros();
void alugarCarro();

#endif
