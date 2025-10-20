#include "funcoes.h"

int main() {
    setlocale(LC_ALL, "Portuguese");

    int opcao;

    do {
        cout << "\n======== MENU ========\n";
        cout << "01 - Cadastrar locatário\n";
        cout << "02 - Cadastrar carro\n";
        cout << "03- Alugar carro\n";
        cout << "04 - Listar carros\n";
        cout << "05 - Sair\n";
        cout << "==========================\n";
        cout << "Escolha uma opção: ";
        cin >> opcao;

        switch (opcao) {
            case 1: cadastroPessoa(); break;
            case 2: cadastrarCarro(); break;
            case 3: alugarCarro(); break;
            case 4: listarCarros(); break;
            case 5: cout << "Saindo do programa...\n"; break;
            default: cout << "Opção inválida!\n";
        }
    } while (opcao != 5);
    return 0;
}