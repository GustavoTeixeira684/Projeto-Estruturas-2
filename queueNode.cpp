#include "queueNode.hpp"

QueueNode::QueueNode(){ // Construtor padrao
    this->values = nullptr;
    this->next = nullptr;
}

QueueNode::QueueNode(string *values, int length){ // Construtor com parametros
    this->values = new string[length];
    for(int i = 0; i < length; i++){
        this->values[i] = values[i];
    }
    this->next = nullptr;
}

QueueNode *QueueNode::getNext(){ // Retorna o proximo item da fila
    return this->next;
}

void QueueNode::setNext(QueueNode *next){ // Define o proximo item da fila
    this->next = next;
}

string *QueueNode::getValues(int length){ // Retorna um vetor com os valores da fila
     // Retorna um vetor temporario, pois como eh ponteiro, se a funcao que chamou esse metodo alterar o valor no vetor local, tambem altera na fila
    string *temp = nullptr;
    if(this->values != nullptr){
        temp= new string[length];
        for(int i = 0; i < length; i++){
            temp[i] = this->values[i];
        }
    }
    return temp;
}