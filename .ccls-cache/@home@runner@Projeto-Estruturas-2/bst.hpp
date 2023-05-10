#ifndef __BST_HPP__
#define __BST_HPP__
#include <iostream>
#include "programanetflix.hpp"
#include "column.hpp"
using namespace std;

class BstTree{

  private:
    // Atributos
    ProgramaNetflix *root;
    Column *col;
    int qntNodes;
    
  public:
    BstTree();
    ProgramaNetflix *getRoot();
    void insert(string *values, int *step);
    void insertColumns(string *values);
    void updateColumn(string value, int index);
    int getQntNodes();
    void print();
    void print(ProgramaNetflix *node, int space);
    bool remove(string id, int *step);
    ProgramaNetflix *search(string id, int *step);
    ProgramaNetflix *search(string id, ProgramaNetflix *father);
    int getHeight(ProgramaNetflix *node, int *step);

};

#endif