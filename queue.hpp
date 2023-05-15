#ifndef __QUEUE_HPP__
#define __QUEUE_HPP__
#include "queueNode.hpp"
#include "column.hpp"

class Queue{

    private:
        QueueNode *head;
        QueueNode *tail;

        int size;
        int countOfItems;
    
    public:
        Queue(int countOfItems);
        void push(string *values);
        void pop();
        string *front();
        int getSize();

};

#endif