

#include "funcoes.h"


//funçao para pegar data e hora atuais
string dataHoraAtual() 
{
    time_t agora = time(0);

    tm *tempoLocal = localtime(&agora);

    stringstream ss;
    ss << tempoLocal->tm_mday << "/"
        << tempoLocal->tm_mon + 1 << "/"
        << tempoLocal->tm_year + 1900 << " - "
        << tempoLocal->tm_hour << ";"
        << tempoLocal->tm_min << ":"
        << tempoLocal->tm_sec;

    return ss.str(); //retorna a string c a data e a hora formatada
}


//===============================================


//função para validar o cpf
bool validarCpf(string cpf)
{
    cpf.erase(remove(cpf.begin(), cpf.end(), '.'), cpf.end());
    cpf.erase(remove(cpf.begin(), cpf.end(), '-'), cpf.end());

    if (cpf.length() != 11) {
        return false;
    }
    return true;
}



//================================================


//funçao para veririfcar se o usuario ja existe no arquivo
bool usuarioExiste(string cpf) {
    ifstream arquivo("locatarios.txt"); //abre o arquivo p leitura
    if (!arquivo.is_open()) return false;

    string linha;
    while (getline(arquivo, linha)) {
        stringstream ss(linha);
        string nome, cpfArq, endereco;

        getline(ss, nome, ';');
        getline(ss, cpfArq, ';');
        getline(ss, endereco, ';');

        if (cpfArq == cpf) {
            arquivo.close();
            return true;
        }
    }

    arquivo.close();
    return false;
}



//==============================================


//função para cadastrar o cliente (nome, cpf e endereço) coloquei o validarcpf aq dentro
Pessoa cadastroPessoa()
{
    Pessoa p;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "==== CADASTRO DO LOCATÁRIO ====" << endl;
    cout << "Qual seu nome?" << endl;
    getline(cin, p.nome);

    do {
        cout << "Digite seu CPF (somente números, 11 dígitos): " << endl;
        getline(cin, p.cpf);
        if (!validarCpf(p.cpf)) {
            cout << "CPF inválido! O CPF deve conter exatamente 11 dígitos." << endl;
        }
    } while (!validarCpf(p.cpf));

    cout << "Digite seu endereço (Nome da rua e número da casa): " << endl;
    getline(cin, p.endereco);

    //salvando os locatarios num arquivo txt
    ofstream arquivo("locatarios.txt", ios::app); //abre no modo append?   
    if (!arquivo) {
        cout << "Erro ao abrir o arquivo de locatários!" << endl;
    } else {
        arquivo << p.nome << ";" << p.cpf << ";" << p.endereco << ";" << "\n";
        arquivo.close();
        cout << "\nLocatário salvo com sucesso em 'locatarios.txt'!" << endl;
    }
    return p;
}




//=========================================================



//função para cadastrar o carro
void cadastrarCarro()
    {
        Carro c;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin.ignore();

        cout << "\n==== CADASTRO DE CARRO ====\n";
        cout << "Modelo: ";
        getline(cin, c.modelo);

        cout << "Placa: ";
        getline(cin, c.placa);

        cout << "Cor: ";
        getline(cin, c.cor);

        cout << "Ano: ";
        cin >> c.ano;

        cout << "Valor do aluguel (por dia): ";
        cin >> c.valor;

        c.alugado = false; //por padrao ele ja eh cadastrado como disponivel p aluguel
        c.horaEntrada = dataHoraAtual();

        //salva o carro em outro arquivo 'carros.txt'
        ofstream arquivo("carros.txt", ios::app);
        if (arquivo.is_open()) {
            arquivo << c.modelo << ";" << c.placa << ";" << c.cor << ";"
                    << c.ano << ";" << c.valor << ";" << c.horaEntrada << ";" << c.alugado << "\n";
            arquivo.close();
            cout << "Carro cadastrado com sucesso!\n";
        } else {
            cout << "Erro ao abrir o arquivo de carros!\n";
        }
    }



    //===========================================================



    //função para listar os carros cadastrados
void listarCarros() 
{
    ifstream arquivo("carros.txt");
    if (!arquivo.is_open()) {
        cout << "Nenhum carro cadastrado.\n";
        return;
    }

    string linha;
    cout << "\n==== LISTA DE CARROS ====\n";
    while (getline(arquivo, linha)) {
        stringstream ss(linha);
        Carro c;

       /* getline(ss, c.modelo, ';');
        getline(ss, c.placa, ';');
        getline(ss, c.cor, ';');
        ss >> c.ano;
        ss.ignore();
        ss >> c.valor;
        ss.ignore();
        getline(ss, c.horaEntrada, ';');
        ss >> c.alugado;*/

        getline(ss, c.modelo, ';');
        getline(ss, c.placa, ';');
        getline(ss, c.cor, ';');
        
        string anoStr, valorStr, alugadoStr;
        getline(ss, anoStr, ';');
        getline(ss, valorStr, ';');
        getline(ss, c.horaEntrada, ';');
        getline(ss, alugadoStr, ';');

        c.ano = stoi(anoStr);
        c.valor = stof(valorStr);
        c.alugado = (alugadoStr == "1");


        cout << "Modelo: " << c.modelo
             << "| Placa: " << c.placa
             << "| Cor: " << c.cor
             << "| Ano: " << c.ano
             << "| Valor: R$" << c.valor
             << "| Cadastro: " << c.horaEntrada
             << "| Status: " << (c.alugado ? "Alugado" : "Disponível") << endl;
    }
    arquivo.close();
}



//==========================================================================



//função para alugar o carro
void alugarCarro()
{
    string cpf, placa;
    cin.ignore();

    cout << "\n==== ALUGAR CARRO ====\n";
    cout << "Digite seu CPF: ";
    getline(cin, cpf);

    if (!usuarioExiste(cpf)) {
        cout << "Usuário não encontrador! Deseja se cadastrar? (responda com (S/N)): ";
        char opc;
        cin >> opc;

        if (toupper(opc) == 'S') {
            cadastroPessoa();
        } else {
            cout << "Aluguel cancelado.\n";
            return;
        }
        cin.ignore();
    }

    cout << "Digite a PLACA do carro que deseja alugar: ";
    getline(cin, placa);

    ifstream arqIn("carros.txt");
    if (!arqIn.is_open()) {
        cout << "Nenhum carro cadastrado.\n";
        return;
    }

    vector<Carro> carros;
    string linha;
    while (getline(arqIn, linha)) {
        stringstream ss(linha);
        Carro c;
    string anoStr, valorStr, alugadoStr;

    getline(ss, c.modelo, ';');
    getline(ss, c.placa, ';');
    getline(ss, c.cor, ';');
    getline(ss, anoStr, ';');
    getline(ss, valorStr, ';');
    getline(ss, c.horaEntrada, ';');
    getline(ss, alugadoStr, ';');

    c.ano = stoi(anoStr);
    c.valor = stof(valorStr);
    c.alugado = (alugadoStr == "1");

    carros.push_back(c);
}
    arqIn.close();

    bool encontrado = false;

    //for pra percoeer os carros para encontrar oq o usuario quer
    for (auto &c : carros) {
        if (c.placa == placa) {
            encontrado = true;

            if (c.alugado) {
                cout << "Este carro já está alugado!\n";
            } else {
                c.alugado = true;
                string horaAluguel = dataHoraAtual();

                //isso aq registra o aluguel no arquivo 'alugueis.txt'
                ofstream arqAluguel("alugueis.txt", ios::app);
                if (arqAluguel.is_open()) {
                    arqAluguel << cpf << ";" << c.modelo << ";" << c.placa << ";"
                               << horaAluguel << "\n";
                    arqAluguel.close();
                    cout << "Carro alugado com sucesso!\n"; 
                } else {
                    cout << "Erro ao salvar o aluguel!\n";
                }
            }
            break;
        }
    }

    if (!encontrado) {
        cout << "Carro não encontrado!\n";
        return;
    }

    //isso aq atualiza o status dos carros no arquivo
    ofstream arqOut("carros.txt");
    for (auto &c : carros) {
        arqOut << c.modelo << ";" << c.placa << ";" << c.cor << ";" << c.ano << ";"
               << c.valor << ";" << c.horaEntrada << ";" << c.alugado << "\n";
    }
    arqOut.close();
}



//===========================================