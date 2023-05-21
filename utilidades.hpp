#ifndef __UTILIDADES_HPP__
#define __UTILIDADES_HPP__

#include <iostream>
#include <vector>

using namespace std;

int tamanho(string texto); // Retorna o tamanho da string

string toLower(string texto); // Converte os caracteres maiúsculos para minúsculos (Utilizado para padronização de checagem)

int stringCompare(string a, string b); // Compara qual string vem primeiro em ordem lexicográfica

string substring(string text, int begin, int end); // Função que retorna uma string sobre um intervalo

int stringIndex(string text, char character, int begin); // Função que retorna o indice do primeiro caractere encontrado passado como argumento em uma string

string *strSplit(string text, char delimiter, int *length); // Função que quebra uma string em um array se baseando em um delimitador

string strReplace(string text, char oldChar, char newChar); // Função que substitui os caracteres

string *dropIndex(string *values, int index, int length); // Função que dropa um item do array se baseando no indice passado

bool isNull(string values); // Função que retorna true se existir algum item nulo no array

bool isNumber(string value); // Funcao para ver se ovalor inserido e numerico

void fillEmpty(string *values, int *length); // Prenche os campos nulos no vetor para inserir na arvore

string clearChar(string value, char oldChar); // Limpa caracteres indesejados na string (Existe pois o replace não permite como argumento: '')

#endif