#ifndef __PROGRAMANETFLIX_HPP__
#define __PROGRAMANETFLIX_HPP__
#include <iostream>
#include "utilidades.hpp"
using namespace std;

// Classe que representa o node das arvores BST e AVL
class ProgramaNetflix{

  private: // Atributos
    string id;
    string title;
    string type;
    string description;
    int release_year;
    string age_certification;
    int runtime;
    string genres;
    string production_countries;
    float seasons;
    string imdb_id;
    float imdb_score;
    float imdb_votes;
    float tmdb_popularity;
    float tmdb_score;
    ProgramaNetflix *left;
    ProgramaNetflix *right;
    ProgramaNetflix *father;

  public:
    ProgramaNetflix(); // Construtor padrao
    ~ProgramaNetflix(); // Destrutor
    ProgramaNetflix(string *values, ProgramaNetflix *father); // Construtor que recebe os valores para ser inseriro e o pai do novo node
    ProgramaNetflix *getLeft(); // Retorna o filho a esquerda
    void setLeft(ProgramaNetflix *node); // Define o filho a esquerda
    ProgramaNetflix *getRight(); // Retorna o filho a direita
    void setRight(ProgramaNetflix *node); // Define o filho a direita
    ProgramaNetflix *getFather(); // Retorna o node pai do atual
    void setFather(ProgramaNetflix *node); // Define o node pai do atual
    string getId(); // Retorna o ID do Programa
    string getTitle(); // Retorna o Titulo do Programa
    string getType(); // Retorna o Tipo do Programa
    int getYear(); // Retorna o ano de lançamento do Programa
    float getImdbScore(); // Retorna o IMDB Score
    string *getValues(); // Retorna um vetor com todos os valores presente no node
    void updateValues(string *values); // Atualiza os valores do node (Utilizado no metodo de remocao)
    void printValue(); // Exibe os valores do node na tela
    
};

#endif