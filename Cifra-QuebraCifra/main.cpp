#include <iostream>
#include <string>
#include <algorithm>  // Para random_shuffle
#include <ctime>      // Para time
#include <vector>
#include <fstream>
#include <locale>
#include <sstream>

using namespace std;

const string alfabeto = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
// Vetor para armazenar as letras em minúsculas
    std::vector<char> letrasEsperadas = {
        'e', 'a', 'r', 'i', 'o', 't', 'n', 's', 'l', 'c',
        'u', 'd', 'p', 'm', 'h', 'g', 'b', 'f', 'y', 'w',
        'k', 'v', 'x', 'z', 'j', 'q'
    };
    
    // Vetor para armazenar as frequências correspondentes
    std::vector<double> frequenciaEsperada = {
        11.1607, 8.4966, 7.5809, 7.5448, 7.1635, 6.9509, 6.6544, 5.7351, 5.4893, 4.5388,
        3.6308, 3.3844, 3.1671, 3.0129, 3.0034, 2.4705, 2.0720, 1.8121, 1.7779, 1.2899,
        1.1016, 1.0074, 0.2902, 0.2722, 0.1965, 0.1962
    };


/*Função para criar a chave de cifra */
string gerarChave(){
    string chave = alfabeto;
/*Gera uma chave pseudo-aleatória para a cifra*/
    random_shuffle(chave.begin(),chave.end());
    return chave;
}

void lerDicionario() {

    // Abrir o arquivo para leitura
    ifstream file("pt_BR.dic");

    // Verificar se o arquivo foi aberto com sucesso
    if (!file.is_open()) {
        cerr << "Erro ao abrir o arquivo!" << endl;
        return;
    }

    vector<string> dictionary;

    string line;
    while (getline(file, line)) {
        // Adicionar cada linha (palavra) ao conjunto
        dictionary.push_back(line);
    }

    // Fechar o arquivo
    file.close();
}

void transformarMinusculo(string &texto){
// Converte todos os caracteres para minúsculas
    transform(texto.begin(), texto.end(), texto.begin(), ::tolower);
}

/*Função para Criptografar o texto com base na chave gerada*/
string ciptrografarTexto(string& texto,string& chave){
    string textoCriptografado ;

/*Percorre cada caracter do texto*/
    for(char c: texto){
        if(isalpha(c)){/*Se c for um caracter do alfabeto*/
            bool eMaiusculo = isupper(c);
            char letraMaiuscula = toupper(c);/*converte a letra para maiuscula pois nossa chave é contem letras maiusculas*/
            int index = alfabeto.find(letraMaiuscula);/*index da letra no alfabeto para ser alterada a letra correspndente na chave*/
            char letraCriptografada = chave[index];/*criptografa a letra com base no index dela na chave*/

            if(!eMaiusculo){/*Caso a letra original não seja maiuscula*/
                letraCriptografada = tolower(letraCriptografada);/*converte a letra para minuscula*/
            }
            textoCriptografado += letraCriptografada;/*adciona a letra ao texto*/


        }else{/*Se c não for um valor alfabetico*/
            textoCriptografado += c;/*adicona o caracter ao texto criptografado*/
        }
    }
    return textoCriptografado;
}

void calcularFrequencia(const string& texto, vector<char>& letras, vector<double>& frequencias) {
    // Inicializa o vetor de letras de 'a' a 'z'
    int total = 0;
    for (char c = 'a'; c <= 'z'; ++c) {
        letras.push_back(c);
        frequencias.push_back(0);
    }

    // Conta a frequência de cada letra no texto
    for (char c : texto) {
        if (isalpha(c)) {
            frequencias[c - 'a']++;  // Incrementa a contagem da letra correspondente
            total++;
        }
    }
    for(auto c : letras){
        frequencias[c - 'a'] = frequencias[c - 'a']/(double)total*100;
    }
}

// Função para substituir as letras no texto criptografado
string substituirTexto(const string& texto, const vector<char>& original, const vector<char>& substituto) {
    string resultado = texto;

    // Para cada letra no texto, substitui conforme o mapeamento
    for (size_t i = 0; i < texto.size(); ++i) {
        for (size_t j = 0; j < original.size(); ++j) {  
            if(isalpha(texto[i])){
                if (texto[i] == original[j]) {
                    resultado[i] = substituto[j];
                    break;
                }
            }
        }
    }

    return resultado;
}

string descriptografarTexto(const string& textoCriptografado,vector<char>& letrasEsperadas, vector<double>& frequencias){

   // Vetores para armazenar as letras criptografadas e suas frequências
    vector<char> letrasCriptografadas;
    vector<double> frequenciasCriptografadas;

    // Calcula a frequência das letras no texto criptografado
    calcularFrequencia(textoCriptografado, letrasCriptografadas, frequenciasCriptografadas);

    // Ordena as letras criptografadas com base nas frequências (decrescente)
    for (size_t i = 0; i < frequenciasCriptografadas.size(); ++i) {
        for (size_t j = i + 1; j < frequenciasCriptografadas.size(); ++j) {
            if (frequenciasCriptografadas[j] > frequenciasCriptografadas[i]) {
                swap(frequenciasCriptografadas[i], frequenciasCriptografadas[j]);
                swap(letrasCriptografadas[i], letrasCriptografadas[j]);
            }
        }
    }

    for ( auto x : frequenciasCriptografadas){
        cout << x << endl;
    }
    for ( auto x : letrasCriptografadas){
        cout << x;
    }
    cout << endl << "------"  <<endl;
    for ( auto x : frequencias){
        cout << x << endl;
    }
    // Cria um vetor de substituição com base nas frequências esperadas
    vector<char> substituicoes(letrasCriptografadas.size());
    for (size_t i = 0; i < letrasCriptografadas.size(); ++i) {
        substituicoes[i] = letrasEsperadas[i];
    }
    cout << "------"  <<endl;
    for ( auto x : substituicoes){
        cout << x;
    }
    // Substitui as letras no texto criptografado
    string textoCOrreto = substituirTexto(textoCriptografado, letrasCriptografadas, substituicoes);
    return textoCOrreto;

    

}

int main (){

    locale::global(locale("pt_BR.UTF-8"));
    string chave = gerarChave();
    lerDicionario();
    cout << "Chave Criptografada: " << chave << endl;

    ifstream texto("texto1.txt"); //abrimos o arquivo de texto
    stringstream buff;
    buff << texto.rdbuf();       //Colocamos o texto todo em uma string
    string textoStr = buff.str();

    string textoCriptografado = ciptrografarTexto(textoStr,chave);

    //cout<< "texto criptografado:"<<endl;
    //cout << textoCriptografado << endl;

    transformarMinusculo(textoCriptografado);

    string textD = descriptografarTexto(textoCriptografado,letrasEsperadas,frequenciaEsperada);
    cout<< "texto descriptografado:"<<endl;
    //cout << textoCriptografado << endl;

}