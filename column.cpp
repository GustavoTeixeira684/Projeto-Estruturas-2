#include "column.hpp"

Column::Column(){ // Construtor padrao. Insere valores padrao para a coluna
  this->values = new string[15];
  string valuesTemp[] = {"id","title","type","description","release_year","age_certification","runtime","genres",
  "production_countries","seasons","imdb_id","imdb_score","imdb_votes","tmdb_popularity","tmdb_score"};

  for(int i = 0; i < 15; i++){
    this->values[i] = valuesTemp[i];
  }
  
}

Column::~Column(){ // Destrutor
  this->clear();
}

void Column::clear(){ // Funcao para limpar a coluna
  delete[] this->values;
}

Column::Column(string *values){ // Construtor que recebe como parametro os valores que serao inseridos na coluna
  this->values = new string[15];
  for(int i = 0; i < 15; i++){
    this->values[i] = values[i];
  }
}

// Fizemos dessa forma para ter segurança. Se somente dessemos o return no atributo, como é um ponteiro, a função que o chamou poderia alterar os dados. Pois o que passamos é um ponteiro
string *Column::getValues(){
  string *temp = new string[15];
  for(int i = 0; i < 15; i++){
    temp[i] = this->values[i];
  }
  return temp;
}

