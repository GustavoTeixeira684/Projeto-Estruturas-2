// Gustavo Teixeira dos Santos 

#include <iostream>
#include <fstream>
#include <vector>
#include <locale.h>
#include "avl.hpp"
#include "bst.hpp"
using namespace std;

void populateBst(BstTree *bst, AvlTree *avl, vector<string> *list){
  string *values;
  int length, step_bst, step_avl;
  step_bst = 0;
  step_avl = 0;
  for(int i = 0; i < list->size(); i++){
    values = strSplit(list->at(i), ';', &length);
    values = dropIndex(values,9, length);
    if(!isNull(values, length)){
      // cout << list->at(i) << endl;
      // for(int j = 0; j < length-1; j++){
      //   cout << values[j] << "|";
      // }
      // cout << endl << endl;
      bst->insert(values, &step_bst);
      avl->insert(values, &step_avl);
    }
  }
  cout << "Passos Bst: " << step_bst << endl << "Passos Avl: " << step_avl << endl;
}

void readArchive(BstTree *bst, AvlTree *avl, string path){ // Função para ler o arquivo
  ifstream file;
  int count, length;
  char sep;
  string result, values, *joj;
  vector<string> lista;
  file.open(path);
  if(!file.fail()){
    getline(file, result, '\n');
    int k = 0;
    while(file.peek() != EOF){
      getline(file, result, '\n');
      lista.push_back(result);
      k++;
    }
  }
  populateBst(bst, avl, &lista);

}

/*void teste(){
  AvlTree *avl = new AvlTree();
  string option = "-1";
  string values[15] = {"3","1","1","1","1","1","1","1","1","1","1","1","1","1"};
  avl->insert(values);
  string values1[15] = {"2","1","1","1","1","1","1","1","1","1","1","1","1","1"};
  avl->insert(values1);
  string values2[15] = {"1","1","1","1","1","1","1","1","1","1","1","1","1","1"};
  avl->insert(values2);
  string values3[15] = {"5","1","1","1","1","1","1","1","1","1","1","1","1","1"};
  avl->insert(values3);
  string values4[15] = {"4","1","1","1","1","1","1","1","1","1","1","1","1","1"};
  avl->insert(values4);
  string values5[15] = {"6","1","1","1","1","1","1","1","1","1","1","1","1","1"};
  avl->insert(values5);
  string values6[15] = {"9","1","1","1","1","1","1","1","1","1","1","1","1","1"};
  avl->insert(values6);
  string values7[15] = {"7","1","1","1","1","1","1","1","1","1","1","1","1","1"};
  avl->insert(values7);
  string values8[15] = {"8","1","1","1","1","1","1","1","1","1","1","1","1","1"};
  avl->insert(values8);
  avl->print();
  
  while(option != "0"){
    cout << "\nDigite o valor do nó que deseja retirar: ";
    cin >> option;
    avl->remove(option);
    avl->print();
  }
}*/

int main() {
  setlocale(LC_ALL, "Portuguese");
  BstTree *bst = new BstTree();
  AvlTree *avl = new AvlTree();
  readArchive(bst, avl, "dados/titles.csv");
  // avl->print();
  // teste();
  // bst->print();

}
