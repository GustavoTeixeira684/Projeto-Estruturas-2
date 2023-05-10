#ifndef __AVL_HPP__
#define __AVL_HPP__
#include <iostream>
#include "programanetflix.hpp"
using namespace std;

class AvlTree{

  private:
    // Atributos
    ProgramaNetflix *root;
    int qntNodes;
    
  public:
    AvlTree();
    ProgramaNetflix *getRoot();
    void insert(string *values, int *step);
    int getQntNodes();
    void print();
    void print(ProgramaNetflix *node, int space);
    bool remove(string id, int *step);
    ProgramaNetflix *search(string id, int *step);
    ProgramaNetflix *search(string id, ProgramaNetflix *father);
    int getHeight(ProgramaNetflix *node, int *step);
    int getBalance(ProgramaNetflix *node, int *step);
    void balanceTree(ProgramaNetflix *node, int *step);
    void leftRotate(ProgramaNetflix *node);
    void rightRotate(ProgramaNetflix *node);

};

#endif