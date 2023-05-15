#ifndef __AVL_HPP__
#define __AVL_HPP__
#include <iostream>
#include "programanetflix.hpp"
#include "column.hpp"
using namespace std;

class AvlTree{

  private:
    // Atributos
    ProgramaNetflix *root;
    Column *col;
    int qntNodes;
    
  public:
    AvlTree();
    ProgramaNetflix *getRoot();
    Column *getColumn();
    void insert(string *values, int *step);
    void insertColumns(string *values);
    void updateColumn(string value, int index);
    int getQntNodes();
    void print();
    void print(ProgramaNetflix *node, int space);
    bool remove(string id, int *step);
    ProgramaNetflix *search(string id, int *step);
    ProgramaNetflix *search(string id, ProgramaNetflix *father);
    int getHeight(ProgramaNetflix *node);
    int getBalance(ProgramaNetflix *node);
    void balanceTree(ProgramaNetflix *node);
    void leftRotate(ProgramaNetflix *node);
    void rightRotate(ProgramaNetflix *node);

};

#endif