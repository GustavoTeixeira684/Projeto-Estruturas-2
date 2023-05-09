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
    void insert(string *values, int *step);
    void print();
    void print(ProgramaNetflix *node, int space);
    bool remove(string id, int *step);
    ProgramaNetflix *search(string id, int *step);
    ProgramaNetflix *search(string id, ProgramaNetflix *father);
    int getHeight(ProgramaNetflix *node, int *step);

};

#endif