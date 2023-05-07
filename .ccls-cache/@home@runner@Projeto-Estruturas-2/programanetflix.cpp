#include "programanetflix.hpp"

ProgramaNetflix::ProgramaNetflix(){
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
  this->imdb_score = 0.0;
  this->imdb_votes = 0.0;
  this->tmdb_popularity = 0.0;
  this->tmdb_score = 0.0;
  this->father = nullptr;
  this->left = nullptr;
  this->right = nullptr;
}

ProgramaNetflix::ProgramaNetflix(string *values, ProgramaNetflix *father){
  this->id = values[0];
  this->title = values[1];
  this->type = values[2];
  this->description = values[3];
  this->release_year = stoi(values[4]);
  this->age_certification = values[5];
  this->runtime = stoi(values[6]);
  this->genres = values[7];
  this->production_countries = values[8];
  this->seasons = stoi(values[9]);
  this->imdb_score = stof(values[10]);
  this->imdb_votes = stof(values[11]);
  this->tmdb_popularity = stof(values[12]);
  this->tmdb_score = stof(values[13]);
  this->father = father;
}

string *ProgramaNetflix::getValues(){
  string *values = new string[14];
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
  values[10] = to_string(this->imdb_score);
  values[11] = to_string(this->imdb_votes);
  values[12] = to_string(this->tmdb_popularity);
  values[13] = to_string(this->tmdb_score);
  return values;
}

void ProgramaNetflix::updateValues(string *values){
  this->id = values[0];
  this->title = values[1];
  this->type = values[2];
  this->description = values[3];
  this->release_year = stoi(values[4]);
  this->age_certification = values[5];
  this->runtime = stoi(values[6]);
  this->genres = values[7];
  this->production_countries = values[8];
  this->seasons = stoi(values[9]);
  this->imdb_score = stof(values[10]);
  this->imdb_votes = stof(values[11]);
  this->tmdb_popularity = stof(values[12]);
  this->tmdb_score = stof(values[13]);
  delete(values);
  values = nullptr;
}

ProgramaNetflix *ProgramaNetflix::getLeft(){
  return this->left;
}

void ProgramaNetflix::setLeft(ProgramaNetflix *node){
  this->left = node;
  node = nullptr;
}

ProgramaNetflix *ProgramaNetflix::getRight(){
  return this->right;
}

void ProgramaNetflix::setRight(ProgramaNetflix *node){
  this->right = node;
  node = nullptr;
}

ProgramaNetflix *ProgramaNetflix::getFather(){
  return this->father;
}

void ProgramaNetflix::setFather(ProgramaNetflix *node){
  this->father = node;
  node = nullptr;
}

string ProgramaNetflix::getId(){
  return this->id;
}

