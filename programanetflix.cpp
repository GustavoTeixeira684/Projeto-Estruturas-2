#include "programanetflix.hpp"

ProgramaNetflix::ProgramaNetflix(){ // Construtor Padrao
  this->id = "";
  this->title = "";
  this->type = "";
  this->description = "";
  this->release_year = 0;
  this->age_certification = "";
  this->runtime = 0;
  this->genres = "";
  this->production_countries = "";
  this->seasons = 0;
  this->imdb_id = "";
  this->imdb_score = 0.0;
  this->imdb_votes = 0.0;
  this->tmdb_popularity = 0.0;
  this->tmdb_score = 0.0;
  this->father = nullptr;
  this->left = nullptr;
  this->right = nullptr;
}

ProgramaNetflix::~ProgramaNetflix(){ // Destrutor (definido por padrao)
  
}

ProgramaNetflix::ProgramaNetflix(string *values, ProgramaNetflix *father){ // Construtor que recebe como parametro os valores a serem inseridos e o pai do node
  this->id = values[0];
  this->title = values[1];
  this->type = values[2];
  this->description = values[3];
  this->release_year = stoi(values[4]);
  this->age_certification = values[5];
  this->runtime = stoi(values[6]);
  this->genres = values[7];
  this->production_countries = values[8];
  this->seasons = stof(strReplace(values[9],'.',','));
  this->imdb_id = values[10];
  this->imdb_score = stof(strReplace(values[11],'.',','));
  this->imdb_votes = stof(strReplace(values[12],'.',','));
  this->tmdb_popularity = stof(strReplace(values[13],'.',','));
  this->tmdb_score = stof(strReplace(values[14],'.',','));
  this->father = father;
  this->left = nullptr;
  this->right = nullptr;
}

string *ProgramaNetflix::getValues(){ // Metodo que retorna um vetor com todos os valores presente no node
  string *values = new string[15];
  values[0] = this->id;
  values[1] = this->title;
  values[2] = this->type;
  values[3] = this->description;
  values[4] = to_string(this->release_year);
  values[5] = age_certification;
  values[6] = to_string(this->runtime);
  values[7] = this->genres;
  values[8] = this->production_countries;
  values[9] = to_string(this->seasons);
  values[10] = this->imdb_id;
  values[11] = to_string(this->imdb_score);
  values[12] = to_string(this->imdb_votes);
  values[13] = to_string(this->tmdb_popularity);
  values[14] = to_string(this->tmdb_score);
  return values;
}

void ProgramaNetflix::updateValues(string *values){ // Metodo para atualizar os valores do node
  this->id = values[0];
  this->title = values[1];
  this->type = values[2];
  this->description = values[3];
  this->release_year = stoi(values[4]);
  this->age_certification = values[5];
  this->runtime = stoi(values[6]);
  this->genres = values[7];
  this->production_countries = values[8];
  this->seasons = stof(strReplace(values[9],'.',','));
  this->imdb_id = values[10];
  this->imdb_score = stof(strReplace(values[11],'.',','));
  this->imdb_votes = stof(strReplace(values[12],'.',','));
  this->tmdb_popularity = stof(strReplace(values[13],'.',','));
  this->tmdb_score = stof(strReplace(values[14],'.',','));
  values = nullptr;
}

ProgramaNetflix *ProgramaNetflix::getLeft(){ // Retorna o filho a esquerda
  return this->left; 
}

void ProgramaNetflix::setLeft(ProgramaNetflix *node){ // Define o filho a esquerda
  this->left = node;
}

ProgramaNetflix *ProgramaNetflix::getRight(){ // Retorna o filho a direita
  return this->right;
}

void ProgramaNetflix::setRight(ProgramaNetflix *node){ // Define o filho a direita
  this->right = node;
}

ProgramaNetflix *ProgramaNetflix::getFather(){ // Retorna o pai do node
  return this->father;
}

void ProgramaNetflix::setFather(ProgramaNetflix *node){ // Define o pai do node
  this->father = node;
}

string ProgramaNetflix::getId(){ // Retorna o ID do node
  return this->id;
}

string ProgramaNetflix::getTitle(){ // Retorna o titulo do node
  return this->title;
}

string ProgramaNetflix::getType(){ // Retorna o tipo do Programa
  return this->type;
}

int ProgramaNetflix::getYear(){ // Retorna o Ano de Lancamento do programa
  return this->release_year;
}

float ProgramaNetflix::getImdbScore(){ // Retorna o IMDB Score do Programa
  return this->imdb_score;
}

void ProgramaNetflix::printValue(){ // Printa os valores do node
  string *values = this->getValues();
  for(int i = 0; i <  15; i++){
    cout << values[i] << " | ";
  }
  cout <<endl;
}