#include "column.hpp"

Column::Column(){
  this->values = new string[15];
  string valuesTemp[] = {"id","title","type","description","release_year","age_certification","runtime","genres","production_countries","seasons","imdb_id","imdb_score","imdb_votes","tmdb_popularity","tmdb_score"};

  for(int i = 0; i < 15; i++){
    this->values[i] = valuesTemp[i];
  }
  
}

Column::~Column(){
  this->clear();
}

void Column::clear(){
  delete[] this->values;
}

Column::Column(string *values){
  if(this->values != nullptr){
    delete[] this->values;
  }
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

