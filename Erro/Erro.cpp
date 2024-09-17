#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cctype> // Para funções de manipulação de caracteres

using namespace std;

// Definição do nó da Trie
class TrieNode {
public:
    TrieNode* filho[26];  // Um array para armazenar os ponteiros dos filhos (26 letras do alfabeto)
    bool isFimDaPalavra;

    TrieNode() {
        for (int i = 0; i < 26; i++) {
            filho[i] = nullptr;
        }
        isFimDaPalavra = false;
    }
};

class Trie {
private:
    TrieNode* raiz;

public:
    Trie() {
        raiz = new TrieNode();
    }

    // Função para converter um caractere em um índice de 0 a 25
    int charParaIndex(char ch) const {
        return tolower(ch) - 'a';
    }
    
    // Função qque insere uma palavra na Trie
    void insert(const string& palavra) {
        TrieNode* node = raiz;
        for (char ch : palavra) {
            int index = charParaIndex(ch);
            if (index < 0 || index >= 26) {
                continue;  // Ignora caracteres que não são letras
            }
            if (node->filho[index] == nullptr) {
                node->filho[index] = new TrieNode();
            }
            node = node->filho[index];
        }
        node->isFimDaPalavra = true;
    }

    // Função para buscar uma palavra na Trie
    bool busca(const string& word) const {
        TrieNode* node = raiz;
        for (char ch : word) {
            int index = charParaIndex(ch);
            if (index < 0 || index >= 26) {
                return false;  // Palavras com caracteres não alfabéticos são inválidas
            }
            if (node->filho[index] == nullptr) {
                return false;
            }
            node = node->filho[index];
        }
        return node != nullptr && node->isFimDaPalavra;
    }
};

// Função para carregar o dicionário do arquivo e inserir as palavras na Trie
void carregarDicionario(Trie& trie, const string& caminhoArquivo) {
    ifstream arquivo(caminhoArquivo);
    string palavra;
    if (arquivo.is_open()) {
        while (getline(arquivo, palavra)) {
            if (!palavra.empty()) {
                trie.insert(palavra);
            }
        }
        arquivo.close();
    } else {
        cerr << "Não foi possível abrir o arquivo " << caminhoArquivo << endl;
    }
}

// Função para remover as pontuacoes
string tiraPontuacao(const string& palavra) {
    string limpa;
    for (char ch : palavra) {
        if (isalnum(ch)) { // ignora pontuacao
            limpa += ch;
        }
    }
    return limpa;
}

// Função para verificar quais palavras de um texto estão erradas
vector<string> verificarTexto(const Trie& trie, const string& texto) {
    vector<string> palavrasErradas;
    string palavraAtual;
    for (char ch : texto) {
        if (isspace(ch)) {
            if (!palavraAtual.empty()) {
                string palavraSemPontuacao = tiraPontuacao(palavraAtual);
                if (!trie.busca(palavraSemPontuacao)) {
                    palavrasErradas.push_back(palavraSemPontuacao);
                }
                palavraAtual.clear();
            }
        } else {
            palavraAtual += ch;
        }
    }
    // Verificar a última palavra
    if (!palavraAtual.empty()) {
        string palavraSemPontuacao = tiraPontuacao(palavraAtual);
        if (!trie.busca(palavraSemPontuacao)) {
            palavrasErradas.push_back(palavraSemPontuacao);
        }
    }
    return palavrasErradas;
}

int main() {
    Trie trie;

    // Carregar o dicionário
    carregarDicionario(trie, "pt_BR.dic");

    // Texto a ser verificado
    string texto = "Este e um exmplo de teexto com palvras palvras   ew erradas.";

    // Verificar o texto
    vector<string> palavrasErradas = verificarTexto(trie, texto);

    // Pega o vector de palavras erradas e printa
    if (!palavrasErradas.empty()) {
        cout << "Palavras erradas: ";
        for (const string& palavra : palavrasErradas) {
            cout << palavra << endl;
        }
        cout << endl;
    } else {
        cout << "Não foi encontrada nenhuma palavra errada" << endl;
    }

    return 0;
}
