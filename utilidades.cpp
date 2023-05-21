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

string substring(string text, int begin, int end){ // Funcao para tirar uma substring de uma string
	string temp = "";
	for(int i = begin; i < end; i++){
		temp += text[i];
	}
	return temp;
}

int stringIndex(string text, char character, int begin){ // Funcao que encontra o indice da primeira ocorrencia de um caractere em uma string

	for(int i = begin; i < tamanho(text); i++){
		if(text[i] == character){
			return i;
		}
	}
	return tamanho(text) - 1;

}

string *strSplit(string text, char delimiter, int *length){ // Funcao que recebe uma string e um delimitador e retorna um vetor e o seu tamanho
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

string strReplace(string text, char oldChar, char newChar){ // Funcao que substitui caracteres de uma string
	int i = 0;
	while(text[i] != '\0'){
		if(text[i] == oldChar){
			text[i] = newChar;
		}
		i++;
	}
	return text;
}

string *dropIndex(string *values, int index, int length){ // Funcao que apaga o caractere em um determinado indice de uma string
	for(int i = index; i < length-1; i++){
		values[i] = values[i+1];
	}
	return values;
}

bool isNull(string values){ // Funcao que retorna true se a string tiver apenas caracteres considerados como nulo ou espaços em branco
	int i = 0;
	if(tamanho(values) > 0){
		while(values[i] != '\0'){
			if(values[i] != ' '){
				return false;
			}
			i++;
		}
		return true;
	}
	return true;
}

bool isNumber(string value){ // Funcao que retorna true se a string tiver somente caracteres numericos
  int i = 0;
  while(value[i] != '\0'){
    if((int)value[i] < 48 || (int)value[i] > 57){
      return false;
    }
    i++;
  }
  return true;
}

void fillEmpty(string *values, int *length){ // Funcao que substitui campos nulos em determinados indices do vetor para 0
	for(int i = 0; i < *length; i++){
		if(isNull(values[i])){
			if(i == 4 || i == 6 || i == 9 || i > 10){
				values[i] = "0";
			}
		}
	}
}

string clearChar(string value, char oldChar){ // Funcao que tira determinados caracteres indesejados de uma string
	for(int i = 0; i < tamanho(value); i++){
		if(value[i] == oldChar){
			for(int j = i; j < tamanho(value)-1; j++){
				value[j] = value[j+1];
			}
			value[tamanho(value)-1] = '\0';
		}
	}
	return value;
}