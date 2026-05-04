#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <locale>
#include <limits>

using namespace std;

struct Funcionario {
    int prontuario;
    string nome;
    double salario;
};

int buscarPorProntuario(const vector<Funcionario>& lista, int prontuario) {
    for (int i = 0; i < (int)lista.size(); i++) {
        if (lista[i].prontuario == prontuario)
            return i;
    }
    return -1;
}

void exibirFuncionario(const Funcionario& f) {
    cout << "  Prontuario : " << f.prontuario << "\n";
    cout << "  Nome       : " << f.nome       << "\n";
    cout << fixed << setprecision(2);
    cout << "  Salario    : R$ " << f.salario  << "\n";
}

void incluir(vector<Funcionario>& lista) {
    Funcionario f;

    cout << "\n--- INCLUIR FUNCIONARIO ---\n";
    cout << "Prontuario: ";
    cin  >> f.prontuario;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    if (buscarPorProntuario(lista, f.prontuario) != -1) {
        cout << "[ERRO] Ja existe um funcionario com esse prontuario.\n";
        return;
    }

    cout << "Nome      : ";
    getline(cin, f.nome);

    cout << "Salario   : ";
    cin  >> f.salario;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    lista.push_back(f);
    cout << "[OK] Funcionario incluido com sucesso.\n";
}

void excluir(vector<Funcionario>& lista) {
    cout << "\n--- EXCLUIR FUNCIONARIO ---\n";
    cout << "Informe o prontuario: ";
    int pron;
    cin  >> pron;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    int idx = buscarPorProntuario(lista, pron);
    if (idx == -1) {
        cout << "[ERRO] Funcionario nao encontrado.\n";
        return;
    }

    cout << "Funcionario encontrado:\n";
    exibirFuncionario(lista[idx]);

    cout << "Confirma exclusao? (s/n): ";
    char resp;
    cin >> resp;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    if (resp == 's' || resp == 'S') {
        lista.erase(lista.begin() + idx);
        cout << "[OK] Funcionario excluido com sucesso.\n";
    } else {
        cout << "Exclusao cancelada.\n";
    }
}

void pesquisar(const vector<Funcionario>& lista) {
    cout << "\n--- PESQUISAR FUNCIONARIO ---\n";
    cout << "Informe o prontuario: ";
    int pron;
    cin  >> pron;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    int idx = buscarPorProntuario(lista, pron);
    if (idx == -1) {
        cout << "[INFO] Funcionario nao encontrado.\n";
        return;
    }

    cout << "\nDados do funcionario:\n";
    exibirFuncionario(lista[idx]);
}

void listar(const vector<Funcionario>& lista) {
    cout << "\n--- LISTA DE FUNCIONARIOS ---\n";

    if (lista.empty()) {
        cout << "[INFO] Nenhum funcionario cadastrado.\n";
        return;
    }

    double totalSalarios = 0.0;

    cout << left
         << setw(12) << "Prontuario"
         << setw(30) << "Nome"
         << right << setw(14) << "Salario"
         << "\n";
    cout << string(56, '-') << "\n";

    for (const auto& f : lista) {
        cout << fixed << setprecision(2);
        cout << left
             << setw(12) << f.prontuario
             << setw(30) << f.nome
             << right << setw(10) << "R$ " << f.salario
             << "\n";
        totalSalarios += f.salario;
    }

    cout << string(56, '-') << "\n";
    cout << "Total de funcionarios : " << lista.size()   << "\n";
    cout << "Total de salarios     : R$ "
         << fixed << setprecision(2) << totalSalarios   << "\n";
}

void exibirMenu() {
    cout << "\n=============================\n";
    cout << "   GESTAO DE FUNCIONARIOS\n";
    cout << "=============================\n";
    cout << "  0. Sair\n";
    cout << "  1. Incluir\n";
    cout << "  2. Excluir\n";
    cout << "  3. Pesquisar\n";
    cout << "  4. Listar\n";
    cout << "-----------------------------\n";
    cout << "Opcao: ";
}

int main() {
    setlocale(LC_ALL, "C");

    vector<Funcionario> lista;
    int opcao;

    do {
        exibirMenu();
        cin >> opcao;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (opcao) {
            case 0: cout << "\nEncerrando o programa. Ate logo!\n"; break;
            case 1: incluir(lista);   break;
            case 2: excluir(lista);   break;
            case 3: pesquisar(lista); break;
            case 4: listar(lista);    break;
            default:
                cout << "[ERRO] Opcao invalida. Tente novamente.\n";
        }

    } while (opcao != 0);

    return 0;
}
