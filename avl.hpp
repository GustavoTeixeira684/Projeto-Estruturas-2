#ifndef __AVL_HPP__
#define __AVL_HPP__
#include <iostream>
#include "programanetflix.hpp"
#include "column.hpp"
using namespace std;

// Classe que representa a arvore AVL.
// Construimos ela de forma a tentar manter a maioria dos metodos iterativos e nao recursivos

class AvlTree{

  private:
    ProgramaNetflix *root; // Ponteiro para o primeiro elemento da arvore
    Column *col; // Ponteiro para a coluna da arvore
    int qntNodes; // Atributo que armazerna a quantidade de nos na arvore
    void clear(ProgramaNetflix *node); // metodo para limpar a arvore
    
  public:
    AvlTree(); // Construtor padrao
    ~AvlTree(); // Destrutor padrao
    void clear(); // Metodo para limpar a arvore
    ProgramaNetflix *getRoot(); // Retorna o primeiro elemento da arvore
    Column *getColumn(); // Retorna os valores contidos nas 'colunas' da arvore
    void insert(string *values, int *step); // Insere um novo elemento na arvore
    void insertColumns(string *values); // Insere valores nas 'colunas' da arvore (iterativo)
    void updateColumn(string value, int index); // Atualiza os valores da coluna
    int getQntNodes(); // Retorna a quantidade de nodes na arvore
    bool remove(string id, int *step); // Metodo para remover um node da arvore (iterativo)
    ProgramaNetflix *search(string id, int *step); // Metodo para buscar um item na arvore 
    int getHeight(ProgramaNetflix *node); // Metodo para retornar a altura da arvore
    int getBalance(ProgramaNetflix *node); // Metodo para pegar fator de balanceamento da sub-arvore
    void balanceTree(ProgramaNetflix *node); // Metodo para de fato balancar a arvore
    void leftRotate(ProgramaNetflix *node); // Metodo para girar a subarvore para a esquerda
    void rightRotate(ProgramaNetflix *node); // Metodo para girar a subarvore para a direita

};

#endif