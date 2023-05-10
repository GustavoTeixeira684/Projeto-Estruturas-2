#include "column.hpp"

Column::Column(){
  values = nullptr;
}

Column::Column(string *values){
  this->values = values;
}

// Fizemos dessa forma para ter segurança. Se somente dessemos o return no atributo, como é um ponteiro, a função que o chamou poderia alterar os dados. Pois o que passamos é um ponteiro
string *Column::getValues(){
  string *temp = new string[14];
  for(int i = 0; i < 14; i++){
    temp[i] = this->values[i];
  }
  return temp;
}

void Column::clear(){
  delete this->values;
}
