#include "utilidades.hpp"

int tamanho(string texto){ // Retorna o tamanho da string
	
	int i = 0; // Inicia variável que será utilizada na contagem
	while(texto[i] != '\0'){ // Laço até o fim da string
		i++; // Incremento na variável contadora
	}
	return i; // Retorna valor correspondente ao tamanho da string
}

string toLower(string texto){ // Converte os caracteres maiúsculos para minúsculos (Utilizado para padronização de checagem)
	
	for(int i = 0; i < tamanho(texto); i++){ // Laço para percorrer toda a string
		
		if(texto[i] >= 'A' && texto[i] <= 'Z'){ // Se o caractere atual for um charactere alfabético maiúsculo
			texto[i] = (int) texto[i] + 32; // Converte para o caractere minúsculo
		}
	}
	return texto; // Retorna a nova string
}



int stringCompare(string a, string b){ // 1 Se a for menor, -1 se b for menor e 0 se forem iguais
	
	int i = 0; // Inicia variável que servirá como contador
	a = toLower(a); // Transforma a string em minúscula
	b = toLower(b); // Transforma a string em minúscula
	
	while(i < tamanho(a) || i < tamanho(b)){ // Laço que itera até chegar ao fim de uma das duas strings
		
		if(a[i] < b[i]){ // Se o caractere da primeira string for alfabeticamente menor que o da segunda
			return 1; // Retorna 1
		}else if(a[i] > b[i]){ // Se o caractere da primeira string for alfabeticamente maior que o da segunda
			return -1; // Retorna -1
		}
		i++; // Incrementa contador
	}
	if(tamanho(a) < tamanho(b)){ // Se chegar ao fim de uma das strings e o tamanho de a for menor que o de b
		return 1; // Retorna 1
	}else if(tamanho(a) > tamanho(b)){ // Se o tamanho de a for maior que o de b
		return -1; // Retorna -1
	}else{ // Se o tamanho também for igual
		return 0; // Retorna 0
	}
}

bool notNull(string texto){
	
	int index = 0;
	if(tamanho(texto) > 0){
		while(texto[index] != '\0'){
			if(texto[index] != ' '){
				return true;
			}
			index++;
		}
	}
	return false;
}
void sortList(vector<float> *salario, vector<string> *nome){ // Função para ordenar os vetores com sincronismo
	
	float temp_salario;
	string temp_nome;
	
	for(int i = 0; i < salario->size(); i++){
		for(int k = i+1; k < salario->size(); k++){
			if(salario->at(k) < salario->at(i)){
				temp_salario = salario->at(i); // Insere os valores em uma variável temporária
				temp_nome = nome->at(i);
				// Troca valores
				salario->insert(salario->begin() + i, salario->at(k));
				salario->erase(salario->begin() + i + 1);
				nome->insert(nome->begin() + i, nome->at(k));
				nome->erase(nome->begin() + i + 1);
				salario->insert(salario->begin() + k, temp_salario);
				salario->erase(salario->begin() + k + 1);
				nome->insert(nome->begin() + k, temp_nome);
				nome->erase(nome->begin() + k + 1);
			}
		}
	}
	
}

string substring(string text, int begin, int end){
	string temp = "";
	for(int i = begin; i < end; i++){
		temp += text[i];
	}
	return temp;
}

int stringIndex(string text, char character, int begin){

	for(int i = begin; i < tamanho(text); i++){
		if(text[i] == character){
			return i;
		}
	}
	return tamanho(text) - 1;

}

string *strSplit(string text, char delimiter, int *length){
	string *values, temp;
	int count = 0, index = 0;
	for(int i = 0; i < tamanho(text); i++){
		if(text[i] == delimiter){
			count++;
		}
	}
	count++;
	values = new string[count];
	for(int i = 0; i < count; i++){
		temp = "";
		while( index < tamanho(text) && text[index] != delimiter){
			temp += text[index];
			index++;
		}
		values[i] = temp;
		index++;
	}
	*length = count;
	return values;
}

string strReplace(string text, char oldChar, char newChar){
	int i = 0;
	while(text[i] != '\0'){
		if(text[i] == oldChar){
			text[i] = newChar;
		}
		i++;
	}
	return text;
}

string *dropIndex(string *values, int index, int length){
	for(int i = index; i < length-1; i++){
		values[i] = values[i+1];
	}
	return values;
}

bool isNull(string *values, int length){
	for(int i = 0; i < length; i++){
		if(!notNull(values[i])){
			return true;
		}
	}
	return false;
}

bool isNumber(string value){
  int i = 0;
  while(value[i] != '\0'){
    if((int)value[i] < 48 || (int)value[i] > 57){
      return false;
    }
    i++;
  }
  return true;
}