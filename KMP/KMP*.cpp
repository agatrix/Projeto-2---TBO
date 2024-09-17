#include <iostream>
#include <vector>
#include <string>
#include <fstream> 
#include <sstream>
#include <set>
#include <algorithm> // Para std::transform //Usamos para marcar a palavra achaa
#include <cctype>    // Para std::tolower

using namespace std;

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

void transformarMinusculo(string &texto){
// Converte todos os caracteres para minúsculas
    transform(texto.begin(), texto.end(), texto.begin(), ::tolower);
}

void addMarcacao(string &texto, const int inicio, const int fim){
    for(int i = inicio; i < fim; i++){
        texto[i] = toupper(texto[i]);
    }
}

void failureFunction(const string& padrao, vector<vector<int>>& tabela) {
    vector<int> padraoInt = mapearPadrao(padrao);

    set<char> caracteresUnicos;
    int verifica = 1;
    for (char c : padrao) {
        caracteresUnicos.insert(c);
    }

    // Inicializar a tabela de falhas
    tabela.resize(caracteresUnicos.size(),
                    vector<int>(padrao.size(), 0));
    /*Essa tabela é inicida com a quantidade de
    linhas igual caracteresUnicos.size e colunas padrao.size, tudo em 0*/

    tabela[padraoInt[0]][0] = 1; 
    int x = 0; //esse x marca onde devemos voltar caso erre a sequencia
    for(int i = 1; i<padrao.size();i++){
        for(int j = 0; j<caracteresUnicos.size();j++){
            tabela[j][i] = tabela[j][x];
        }
        if(i+1 == padrao.size()){
            tabela[padraoInt[i]][i] = x;
        }else{
            tabela[padraoInt[i]][i]=i+1;
            x = tabela[padraoInt[i]][x];       
        }
    }

    for(int i = 0; i<caracteresUnicos.size();i++){
        for(int j = 0; j<padrao.size();j++){
            cout << tabela[i][j] << " ";
        }
        cout << endl;
    }
}

void KMP(string& texto, const string& padrao) {
    int m = padrao.size();

    vector<vector<int>> tabela;
    failureFunction(padrao, tabela);
    vector<int> padraoInt = mapearPadrao(padrao);
    int i = 0;  // Índice para o texto
    int j = 0;  // Índice para o padrão

    while (i < texto.size()) {
        bool verifica = false;
        if (texto[i] == padrao[j] || '*' == padrao[j]) {
            i++;
            j++;
            if (j == m) {
                cout << "Padrão encontrado na posição " << i - j << endl;
                addMarcacao(texto, i-j, i); //Colocamos a sequencia em maiuscula
                j = tabela[padraoInt[j - 1]][j - 1];
            }
        } else {
            if (j > 0) {
                for(int z = 0; z < padrao.size();z++){ //Verifica se a letra atual esta no padrao
                    if(padrao[z] == texto[i]){
                        verifica = true;
                    }
                }
                
                if(verifica){ // se estiver, ele pula pra posicao tabela falha
                    j = tabela[padraoInt[j - 1]][j - 1];
                    i++;
                }
                else         // se não, ele volta ao inicio sequencia
                    j = 0;
            } else {
                i++;
            }
        }
    }
}

int main() {
    ifstream texto("texto.txt"); //abrimos o arquivo de texto
    stringstream buff;
    buff << texto.rdbuf();       //Colocamos o texto todo em uma string
    string textoStr = buff.str();
    string padrao = "v*z*s"; //Padrão que o usuario está procurando

    transformarMinusculo(textoStr);
    transformarMinusculo(padrao);

    KMP(textoStr,padrao);

    cout << endl << textoStr;

    return 0;
}
