#include <iostream>
#include <string>
#include <algorithm>  // Para random_shuffle
#include <ctime>      // Para time
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

const string alfabeto = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
std::vector<char> letrasEsperadas = {
        'e', 't', 'a', 'o', 'i', 'n', 's', 'h', 'r', 'd', 
        'l', 'u', 'c', 'm', 'f', 'w', 'g', 'y', 'p', 'b', 
        'v', 'k', 'j', 'x', 'q', 'z'
    };

    std::vector<double> frequenciaEsperada = {
        12.702, 9.056, 8.167, 7.507, 6.966, 6.749, 6.327, 
        6.094, 5.987, 4.253, 4.025, 2.782, 2.758, 2.406, 
        2.360, 2.228, 2.015, 1.974, 1.929, 1.492, 0.978, 
        0.772, 0.153, 0.150, 0.095, 0.074
    };


/*Função para criar a chave de cifra */
string gerarChave(){
    string chave = alfabeto;
/*Gera uma chave pseudo-aleatória para a cifra*/
    random_shuffle(chave.begin(),chave.end());
    return chave;
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

    for ( auto x : letrasCriptografadas){
        cout << x;
    }

    cout << endl;

    for(int i = 0 ; i< 26 ; i++){
        cout << frequenciaEsperada[i] << " : " << frequenciasCriptografadas[i] << endl;
    }
    // Substitui as letras no texto criptografado
    //string textoCOrreto = substituirTexto(textoCriptografado, letrasCriptografadas, substituicoes);
    string textoCorreto;
    for(char c: textoCriptografado){
        if(isalpha(c)){/*Se c for um caracter do alfabeto*/
            for(int i = 0; i<26; i++){
                if(letrasCriptografadas[i] == c){
                    textoCorreto += letrasEsperadas[i];/*adciona a letra ao texto*/
                    break;
                }
                
            }
        }else{/*Se c não for um valor alfabetico*/
            textoCorreto += c;/*adicona o caracter ao texto criptografado*/
        }
    }

    return textoCorreto;   

}

int main (){

    string chave = gerarChave();
    cout << "ABCDEFGHIJKLMNOPQRSTUVWXyZ" << endl;
    cout << chave << endl;

    ifstream texto("texto1.txt"); //abrimos o arquivo de texto
    stringstream buff;
    buff << texto.rdbuf();       //Colocamos o texto todo em uma string
    string textoStr = buff.str();
    string textoCriptografado = ciptrografarTexto(textoStr,chave);

    std::ofstream arquivo("saida.txt");  // Abre o arquivo de saída
    
    if (arquivo.is_open()) {  
        arquivo << textoCriptografado;  // Escreve o TextoCrip no arquivo
        arquivo.close();  
    }


    transformarMinusculo(textoCriptografado);

    string textD = descriptografarTexto(textoCriptografado,letrasEsperadas,frequenciaEsperada);
    cout<< "texto descriptografado:"<<endl;
    cout << textD << endl;

}