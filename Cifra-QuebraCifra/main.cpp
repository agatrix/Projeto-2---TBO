#include <iostream>
#include <string>
#include <algorithm>  // Para random_shuffle
#include <ctime>      // Para time

using namespace std;

const string alfabeto = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

/*Função para criar a chave de cifra */
string gerarChave(){
    string chave = alfabeto;
/*Gera uma chave pseudo-aleatória para a cifra*/
    random_shuffle(chave.begin(),chave.end());
    return chave;
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

int main (){

    
    string texto;
    string chave = gerarChave();

    cout << "Chave Criptografada: " << chave << endl;

    cout<< "texto: ";
    getline(cin,texto);
    /* cout << texto << endl; */
    string textoCriptografado = ciptrografarTexto(texto,chave);

    cout<< "texto criptografado:"<<endl;
    cout << textoCriptografado << endl;

}