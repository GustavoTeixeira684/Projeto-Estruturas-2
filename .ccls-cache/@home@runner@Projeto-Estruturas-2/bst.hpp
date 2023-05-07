#ifndef __BST_HPP__
#define __BST_HPP__
#include <iostream>
#include "programanetflix.hpp"
using namespace std;

class BstTree{

  private:
    // Atributos
    ProgramaNetflix *root;

    // Métodos
    


    
  public:
    BstTree();
    ProgramaNetflix *getRoot();
    void insert(string *values);
    void print();
    void print(ProgramaNetflix *node, int space);
    void remove(string id);
    ProgramaNetflix *search(string id);
    ProgramaNetflix *search(string id, ProgramaNetflix *father);

};

#endif