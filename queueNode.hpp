#ifndef __QUEUENODE_HPP__
#define __QUEUENODE_HPP__
#include <iostream>
using namespace std;
// Classe referente ao node da fila
// Desenvolvido de uma forma em que o usuario pode definir quantas colunas cada node da fila tera
class QueueNode{

    private:
        string *values; // Ponteiro que contem o vetor dos valores do node
        QueueNode *next; // Ponteiro para o proximo node da fila

    public:
        QueueNode();
        QueueNode(string *values, int length);
        QueueNode *getNext();
        void setNext(QueueNode *next);
        string *getValues(int length);
        

};

#endif