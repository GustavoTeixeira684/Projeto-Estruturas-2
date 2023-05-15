#include "queueNode.hpp"

QueueNode::QueueNode(){
    this->values = nullptr;
    this->next = nullptr;
}

QueueNode::QueueNode(string *values, int length){
    this->values = new string[length];
    for(int i = 0; i < length; i++){
        this->values[i] = values[i];
    }
    this->next = nullptr;
}

QueueNode *QueueNode::getNext(){
    return this->next;
}

void QueueNode::setNext(QueueNode *next){
    this->next = next;
}

string *QueueNode::getValues(int length){
    string *temp = nullptr;
    if(this->values != nullptr){
        temp= new string[length];
        for(int i = 0; i < length; i++){
            temp[i] = this->values[i];
        }
    }
    return temp;
}