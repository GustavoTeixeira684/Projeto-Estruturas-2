#include "queue.hpp"

Queue::Queue(int countOfItems){
    this->head = nullptr;
    this->tail = nullptr;
    this->size = 0;
    this->countOfItems = countOfItems;
}

Queue::~Queue(){
  this->clear();
}

void Queue::clear(){
  while(this->size > 0){
    this->pop();
  }
}

void Queue::push(string *values){
    QueueNode *temp = new QueueNode(values, this->countOfItems);
    if(this->head != nullptr){
        this->tail->setNext(temp);
        this->tail = temp;
    }else{
        this->head = temp;
        this->tail = temp;
    }
    this->size++;
    temp = nullptr;
}

void Queue::pop(){
    if(this->head != nullptr){
        QueueNode *temp = this->head;
        this->head = this->head->getNext();
        delete temp;
        temp = nullptr;
        this->size--;
    }
}

string *Queue::front(){
    return this->head->getValues(this->countOfItems);
}

int Queue::getSize(){
    return this->size;
}
