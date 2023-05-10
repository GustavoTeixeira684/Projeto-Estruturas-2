#ifndef __PROGRAMANETFLIX_HPP__
#define __PROGRAMANETFLIX_HPP__
#include <iostream>
#include "utilidades.hpp"
using namespace std;

class ProgramaNetflix{

  private:
    string id;
    string title;
    string type;
    string description;
    int release_year;
    string age_certification;
    int runtime;
    string genres;
    string production_countries;
    float seasons;
    float imdb_score;
    float imdb_votes;
    float tmdb_popularity;
    float tmdb_score;
    ProgramaNetflix *left;
    ProgramaNetflix *right;
    ProgramaNetflix *father;

  public:
    ProgramaNetflix();
    ProgramaNetflix(string *values, ProgramaNetflix *father);
    ProgramaNetflix *getLeft();
    void setLeft(ProgramaNetflix *node);
    ProgramaNetflix *getRight();
    void setRight(ProgramaNetflix *node);
    ProgramaNetflix *getFather();
    void setFather(ProgramaNetflix *node);
    string getId();
    string *getValues();
    void updateValues(string *values);
    void printValue();
    
};

#endif