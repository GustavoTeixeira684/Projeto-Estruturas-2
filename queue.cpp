#include "queue.hpp"

Queue::Queue(int countOfItems){ // Construtor. Recebe como parametro 
    this->head = nullptr;
    this->tail = nullptr;
    this->size = 0;
    this->countOfItems = countOfItems;
}

Queue::~Queue(){ // Destrutor da Fila
  this->clear();
}

void Queue::clear(){ // Funcao que limpa os valores da fila
  while(this->size > 0){
    this->pop();
  }
}

void Queue::push(string *values){ // Funcao que insere um novo item no fim da fila
    QueueNode *temp = new QueueNode(values, this->countOfItems); // instancia o node em um ponteiro temporario
    if(this->head != nullptr){ // Se a fila nao estiver vazia
        this->tail->setNext(temp); // Coloca o novo item como o proximo do ultimo
        this->tail = temp; // Define o novo item como o ultimo da lista
    }else{ // Caso contratio
        this->head = temp; // Como eh um unico elemento, ele eh o primeiro e o ultimo
        this->tail = temp;
    }
    this->size++;
    temp = nullptr;
}

void Queue::pop(){ // Funcao que remove o primeiro item da fila
    if(this->head != nullptr){ // So executa se a fila nao estiver vazia
        QueueNode *temp = this->head;
        this->head = this->head->getNext();
        delete temp;
        temp = nullptr;
        this->size--;
    }
}

string *Queue::front(){ // Funcao que retorna os valores do primeiro item da fila
    return this->head->getValues(this->countOfItems);
}

int Queue::getSize(){ // Funcao que retorna o tamanho da Fila
    return this->size;
}
