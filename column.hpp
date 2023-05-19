#ifndef __COLUMN_HPP__
#define __COLUMN_HPP__
#include <iostream>
using namespace std;

class Column{

  private:
    string *values;

  public:
  Column();
  ~Column();
  void clear();
  Column(string *values);
  string *getValues();
};

#endif