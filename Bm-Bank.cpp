#include <iostream>
#include <fstream>
#include <string>

using namespace std;

const int maxNome = 100;
struct Usuario {
    int id;
    string nome;
    int idade;
    double saldoAtual;
};
typedef struct Usuario User;

User* usuarios = nullptr;
int qntUsuarios = 0;
int capacidade = 0;
int IDG = 1;

void CarregarArquivo(const string& nomeArquivo);
void LerDadosDaLinha(const string& linha, User& usuario);

int GeradorID() {
    return IDG++;
}

void garantirCapacidade() {
    if (qntUsuarios == capacidade) {
        int novaCapacidade = (capacidade == 0) ? 10 : capacidade * 2;
        User* novoVetor = new User[novaCapacidade];
        for (int i = 0; i < qntUsuarios; ++i) {
            novoVetor[i] = usuarios[i];
        }
        delete[] usuarios;
        usuarios = novoVetor;
        capacidade = novaCapacidade;
    }
}

int BuscarID(int id) {
    for (int i = 0; i < qntUsuarios; ++i) {
        if (usuarios[i].id == id) {
            return i;
        }
    }
    return -1;
}

void AdicionarUsuario() {
    garantirCapacidade();
    User& novoUsuario = usuarios[qntUsuarios];

    cout << "Digite o nome: ";
    getline(cin, novoUsuario.nome);

    if (novoUsuario.nome.length() > maxNome) {
        cout << "Erro: O nome excede 100 caracteres. Operacao cancelada." << endl;
        return;
    }

    cout << "Digite a idade: ";
    cin >> novoUsuario.idade;
    
    cout << "Digite o saldo atual: ";
    cin >> novoUsuario.saldoAtual;

    if (novoUsuario.saldoAtual < 0) {
        cout << "Erro: Saldo nao pode ser negativo. Operacao cancelada." << endl;
        return;
    }

    novoUsuario.id = GeradorID();
    qntUsuarios++;
    cout << "Usuario inserido com id " << novoUsuario.id << "." << endl;
}

void VariosUsuarios() {
    int quantidade;
    cout << "Digite quantos usuarios deseja adicionar: ";
    cin >> quantidade;
    
    cin.ignore();

    if (quantidade <= 0) {
        cout << "Quantidade invalida." << endl;
        return;
    }

    int primeiroIdInserido = -1;
    int ultimoIdInserido = -1;

    for (int i = 0; i < quantidade; ++i) {
        cout << "\n--- Dados do usuario " << i + 1 << " ---" << endl;
        garantirCapacidade();
        User& novoUsuario = usuarios[qntUsuarios];

        cout << "Digite o nome: ";
        getline(cin, novoUsuario.nome);

        if (novoUsuario.nome.length() > maxNome) {
            cout << "Erro: O nome excede 100 caracteres. Pulando este usuario." << endl;
            continue;
        }

        cout << "Digite a idade: ";
        cin >> novoUsuario.idade;
        cout << "Digite o saldo atual: ";
        cin >> novoUsuario.saldoAtual;

        cin.ignore();

        if (novoUsuario.saldoAtual < 0) {
            cout << "Erro: Saldo nao pode ser negativo. Pulando este usuario." << endl;
            continue;
        }

        novoUsuario.id = GeradorID();
        if(primeiroIdInserido == -1) primeiroIdInserido = novoUsuario.id;
        ultimoIdInserido = novoUsuario.id;
        
        qntUsuarios++;
    }
    if(primeiroIdInserido != -1){
        if(quantidade == 1){
            cout << "Usuario inserido com id " << primeiroIdInserido << "." << endl;
        } else {
            cout << "Usuarios inseridos (IDs de " << primeiroIdInserido << " a " << ultimoIdInserido << ")." << endl;
        }
    }
}

void BuscarUsuario(int id) {
    int indice = BuscarID(id);
    if (indice != -1) {
        cout << "Usuario " << usuarios[indice].id << " tem saldo de R$" << usuarios[indice].saldoAtual << "." << endl;
    } else {
        cout << "Erro: Usuario " << id << " nao encontrado." << endl;
    }
}

void TransferirUsuario() {
    int idOrigem, idDestino;
    double quantia;

    cout << "Digite o id de origem: ";
    cin >> idOrigem;
    cout << "Digite o id de destino: ";
    cin >> idDestino;
    cout << "Digite a quantia: ";
    cin >> quantia;

    if (quantia <= 0) {
        cout << "Erro: A quantia deve ser positiva." << endl;
        return;
    }

    int indiceOrigem = BuscarID(idOrigem);
    int indiceDestino = BuscarID(idDestino);

    if (indiceOrigem == -1) {
        cout << "Erro: Usuario de origem " << idOrigem << " nao encontrado." << endl;
        return;
    }
    if (indiceDestino == -1) {
        cout << "Erro: Usuario de destino " << idDestino << " nao encontrado." << endl;
        return;
    }
    if (usuarios[indiceOrigem].saldoAtual < quantia) {
        cout << "Erro: Saldo insuficiente na conta de origem." << endl;
        return;
    }

    usuarios[indiceOrigem].saldoAtual -= quantia;
    usuarios[indiceDestino].saldoAtual += quantia;

    cout << "Transferencia realizada com sucesso." << endl;
}

void RemoverUsuario(int id) {
    int indice = BuscarID(id);

    if (indice != -1) {
        usuarios[indice] = usuarios[qntUsuarios - 1];
        qntUsuarios--;
        cout << "Usuario " << id << " removido com sucesso." << endl;
    } else {
        cout << "Erro: Usuario " << id << " nao encontrado." << endl;
    }
}

void SalvarArquivo(const string& nomeArquivo) {
    ofstream arquivo(nomeArquivo);
    if (!arquivo.is_open()) {
        cout << "Erro ao abrir arquivo para salvar." << endl;
        return;
    }

    arquivo << qntUsuarios << endl;

    for (int i = 0; i < qntUsuarios; ++i) {
        arquivo << usuarios[i].nome << ","
                << usuarios[i].idade << ","
                << usuarios[i].saldoAtual << endl;
    }
    arquivo.close();
}

void LerDadosDaLinha(const string& linha, User& usuario) {
    size_t pos1 = linha.find(',');
    if (pos1 == string::npos) return;
    usuario.nome = linha.substr(0, pos1);

    size_t pos2 = linha.find(',', pos1 + 1);
    if (pos2 == string::npos) return;
    
    string idadeStr = linha.substr(pos1 + 1, pos2 - (pos1 + 1));
    size_t primeiroNaoEspacoIdade = idadeStr.find_first_not_of(" \t");
    if(string::npos != primeiroNaoEspacoIdade) {
        idadeStr = idadeStr.substr(primeiroNaoEspacoIdade);
    }
    usuario.idade = stoi(idadeStr);

    string saldoStr = linha.substr(pos2 + 1);
    size_t primeiroNaoEspacoSaldo = saldoStr.find_first_not_of(" \t");
     if(string::npos != primeiroNaoEspacoSaldo) {
        saldoStr = saldoStr.substr(primeiroNaoEspacoSaldo);
    }
    usuario.saldoAtual = stod(saldoStr);
}

void CarregarArquivo(const string& nomeArquivo) {
    ifstream arquivo(nomeArquivo);
    if (!arquivo.is_open()) {
        return;
    }

    delete[] usuarios;
    usuarios = nullptr;
    qntUsuarios = 0;
    capacidade = 0;
    IDG = 1; 
    
    int totalUsuariosNoArquivo = 0;
    arquivo >> totalUsuariosNoArquivo;
    if (arquivo.fail()) {
        arquivo.close();
        return;
    }

    string linha;
    getline(arquivo, linha); 

    for (int i = 0; i < totalUsuariosNoArquivo; ++i) {
        if (!getline(arquivo, linha)) break;
        if (linha.empty()) {
            i--; 
            continue;
        }

        garantirCapacidade();
        User& novoUsuario = usuarios[qntUsuarios];
        
        LerDadosDaLinha(linha, novoUsuario);
        
        novoUsuario.id = GeradorID();
        qntUsuarios++;
    }
    
    arquivo.close();
}

void CarregarArquivoPeloMenu() {
    string nomeArquivo;
    cout << "Digite o nome do arquivo para carregar: ";
    cin >> nomeArquivo;
    cin.ignore();
    
    ifstream arquivoTeste(nomeArquivo);
    if (!arquivoTeste.is_open()) {
        cout << "ERRO: Nao foi possivel encontrar ou abrir o arquivo '" << nomeArquivo << "'." << endl;
        return;
    }
    arquivoTeste.close();

    CarregarArquivo(nomeArquivo);
    
    cout << "Arquivo '" << nomeArquivo << "' carregado com sucesso. " << qntUsuarios << " usuarios em memoria." << endl;
}

void ExibeMenu() {
    cout << "\n1. Inserir novo usuario" << endl;
    cout << "2. Inserir varios usuarios" << endl;
    cout << "3. Buscar um usuario por id" << endl;
    cout << "4. Transferir entre usuarios" << endl;
    cout << "5. Remover usuario por id" << endl;
    cout << "6. Carregar arquivo de usuarios" << endl;
    cout << "0. Sair e Salvar" << endl;
    cout << "Escolha uma opcao: ";
}

void Menu() {
    int opcao;
    int id;

    do {
        ExibeMenu();
        cin >> opcao;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Opcao invalida. Tente novamente." << endl;
            continue;
        }
        
        cin.ignore(); 

        switch (opcao) {
            case 1:
                AdicionarUsuario();
                break;
            case 2:
                VariosUsuarios();
                break;
            case 3:
                cout << "Digite o id para busca: ";
                cin >> id;
                cin.ignore();
                BuscarUsuario(id);
                break;
            case 4:
                TransferirUsuario();
                break;
            case 5:
                cout << "Digite o id para remocao: ";
                cin >> id;
                cin.ignore();
                RemoverUsuario(id);
                break;
            case 6:
                CarregarArquivoPeloMenu();
                break;
            case 0:
                SalvarArquivo("BmBank.txt");
                cout << "Dados salvos em BmBank.txt. Encerrando." << endl;
                break;
            default:
                cout << "Opcao invalida. Tente novamente." << endl;
                break;
        }
    } while (opcao != 0);
}

int main() {
    CarregarArquivo("BmBank.txt"); 
    Menu();
    delete[] usuarios;
    return 0;
}