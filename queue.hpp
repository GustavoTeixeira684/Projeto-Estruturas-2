#ifndef __QUEUE_HPP__
#define __QUEUE_HPP__
#include "queueNode.hpp"
#include "column.hpp"

// Classe da fila que desenvolvemos no contexto do projeto
// Desenvolvida de forma em que a funcao que a chamar pode definir quantas colunas a fila tera
class Queue{

    private:
        QueueNode *head; // Ponteiro para o primeiro item
        QueueNode *tail; // Ponteiro para o ultimo item

        int size; // Tamanho
        int countOfItems; // Atributo que contem a quantidade de colunas em cada node da fila
    
    public:
        Queue(int countOfItems); // Construtor padrao
        ~Queue(); // Destrutor
        void clear(); // Funcao para limpar a fila
        void push(string *values); // Inserir elemento no fim da fila
        void pop(); // retirar o elemento do inicio da fila
        string *front(); // Retorna um vetor com os valores do primeiro item da fila
        int getSize(); // Retorna o tamanho da fila

};

#endif