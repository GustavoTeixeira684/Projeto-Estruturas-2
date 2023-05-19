#ifndef __UTILIDADES_HPP__
#define __UTILIDADES_HPP__

#include <iostream>
#include <vector>

using namespace std;

int tamanho(string texto); // Retorna o tamanho da string

string toLower(string texto); // Converte os caracteres maiúsculos para minúsculos (Utilizado para padronização de checagem)

int stringCompare(string a, string b); // Compara qual string vem primeiro em ordem lexicográfica

void sortList(vector<float> *salario, vector<string> *nome); // Função para ordenar a lista de salario sincronizada com a lista de nome dos servidores

string substring(string text, int begin, int end); // Função que retorna uma string sobre um intervalo

int stringIndex(string text, char character, int begin); // Função que retorna o indice do primeiro caractere encontrado passado como argumento em uma string

string *strSplit(string text, char delimiter, int *length); // Função que quebra uma string em um array se baseando em um delimitador

string strReplace(string text, char oldChar, char newChar); // Função que substitui os caracteres

string *dropIndex(string *values, int index, int length); // Função que dropa um item do array se baseando no indice passado

bool isNull(string values); // Função que retorna true se existir algum item nulo no array

bool isNumber(string value); // Funcao para ver se ovalor inserido e numerico

void fillEmpty(string *values, int *length);

#endif