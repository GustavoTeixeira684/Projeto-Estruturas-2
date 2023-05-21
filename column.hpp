#ifndef __COLUMN_HPP__
#define __COLUMN_HPP__
#include <iostream>
using namespace std;

// Classe que armazena a coluna do arquivo que foi lido pela arvore
class Column{

  private:
    string *values; // Ponteiro para vetor que contem os valores

  public:
  Column(); // Construtor padrao
  ~Column(); // Destrutor Padrao
  void clear(); // Limpa o objeto
  Column(string *values); // Construtor que recebe como parametro os valores que serao inseridos na classe
  string *getValues(); // Retorna os valores da coluna
};

#endif