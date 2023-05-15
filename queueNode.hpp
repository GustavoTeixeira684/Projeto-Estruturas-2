#ifndef __QUEUENODE_HPP__
#define __QUEUENODE_HPP__
#include <iostream>
using namespace std;

class QueueNode{

    private:
        string *values;
        QueueNode *next;

    public:
        QueueNode();
        QueueNode(string *values, int length);
        QueueNode *getNext();
        void setNext(QueueNode *next);
        string *getValues(int length);
        

};

#endif