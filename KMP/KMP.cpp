#include <iostream>
#include <vector>
#include <string>
#include <fstream> 
#include <sstream>
#include <set>

using namespace std;

// // Função para criar a tabela de prefixo
// void tabelaPrefixo(const string& padrao, vector<int>& lps) {
//     int length = 0;
//     lps[0] = 0; // lps[0] é sempre 0
//     int i = 1;

//     while (i < padrao.size()) {
//         if (padrao[i] == padrao[length]) {
//             length++;
//             lps[i] = length;
//             i++;
//         } else {
//             if (length != 0) {
//                 length = lps[length - 1];
//             } else {
//                 lps[i] = 0;
//                 i++;
//             }
//         }
//     }
// }

// // Função para realizar a busca KMP
// void procurarKMP(const string& text, const string& padrao) {
//     int n = text.size();
//     int m = padrao.size();

//     vector<int> lps(m); // Vetor de lps
//     tabelaPrefixo(padrao, lps);

//     int i = 0; // índice que acompanha o texto
//     int j = 0; // índice que acompanha o padrao

//     while (i < n) {
//         if (padrao[j] == text[i]) {
//             i++;
//             j++;
//         }

//         if (j == m) {
//             cout << "Padrão encontrado no índice " << i - j << endl;
//             j = lps[j - 1];
//         } else if (i < n && padrao[j] != text[i]) {
//             if (j != 0) {
//                 j = lps[j - 1];
//             } else {
//                 i++;
//             }
//         }
//     }
// }
vector<int> mapearPadrao(const string& sequencia) {
    vector<int> resultado;
    string caracteresVistos;

    for (char c : sequencia) {
        // Verifica se o caractere já apareceu anteriormente
        size_t pos = caracteresVistos.find(c);
        if (pos == string::npos) { //Quando fazemos uma funcao fin, ele retorn npos se nao achar o vaolr
            // Se não apareceu, adiciona ao conjunto de caracteres vistos
            caracteresVistos += c;
            pos = caracteresVistos.size() - 1; // Nova posição do caractere
        }
        resultado.push_back(pos);
    }


    return resultado;
}

void failureFunction(const string& padrao){
    vector<int> padraoInt = mapearPadrao(padrao);

    set<char> caracteresUnicos;
    for (char c : padrao) {
        if (c != ' ') { // Ignorar espaços
            caracteresUnicos.insert(c);
        }
    }

    int tabela[caracteresUnicos.size()][padrao.size()];

    for(int i=0; i<=caracteresUnicos.size()-1;i++){
        tabela[i][0] = 0;
    }

    tabela[padraoInt[0]][0] = 1; 
    int x = 0; //esse x marca onde devemos voltar caso erre a sequencia
    for(int i = 1; i<padrao.size();i++){
        for(int j = 0; j<caracteresUnicos.size();j++){
            tabela[j][i] = tabela[j][x];
        }
        tabela[padraoInt[i]][i]=i+1;
        x = tabela[padraoInt[i]][x];
    }

    for(int i = 0; i<=caracteresUnicos.size()-1;i++){
        for(int j = 0; j<=padrao.size()-1;j++){
            cout << tabela[i][j] << " ";
        }
        cout << endl;
    }
}



int main() {
    ifstream texto("texto.txt"); //abrimos o arquivo de texto
    stringstream buff;
    buff << texto.rdbuf();       //Colocamos o texto todo em uma string
    string textoStr = buff.str();

    string padrao = "ababac"; //Padrão que o usuario está procurando
    failureFunction(padrao);

    return 0;
}
