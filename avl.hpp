#ifndef __AVL_HPP__
#define __AVL_HPP__
#include <iostream>
#include "programanetflix.hpp"
using namespace std;

class AvlTree{

  private:
    // Atributos
    ProgramaNetflix *root;
    
  public:
    AvlTree();
    ProgramaNetflix *getRoot();
    void insert(string *values);
    void print();
    void print(ProgramaNetflix *node, int space);
    void remove(string id);
    ProgramaNetflix *search(string id);
    ProgramaNetflix *search(string id, ProgramaNetflix *father);
    int getHeight(ProgramaNetflix *node);
    int getBalance(ProgramaNetflix *node);
    void balanceTree(ProgramaNetflix *node);
    void leftRotate(ProgramaNetflix *node);
    void rightRotate(ProgramaNetflix *node);

};

#endif