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
    values = dropIndex(values,10, length);
    if(!isNull(values, length)){
      // cout << list->at(i) << endl;
      // for(int j = 0; j < length-1; j++){
      //   cout << values[j] << "|";
      // }
      // cout << endl << endl;
      // cout << list->at(i) << endl << endl;
      bst->insert(values, &step_bst);
      avl->insert(values, &step_avl);
    }
  }
  cout << "Passos Bst: " << step_bst << " com " << bst->getQntNodes() << " nós inseridos" << endl << "Passos Avl: " << step_avl << " com " << avl->getQntNodes() << " nós inseridos" << endl;
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
      values = "";
      for(int i = 0; i < 14; i++){
        if(i != 10){
          file.get(sep);
          if(sep != ';'){
            getline(file, result, ';');
            values += sep + result + ";";
          }else{
            values += ";";
          }
        }else{
          getline(file, result, ';');
        }
      }
      getline(file, result, '\n');
      values += result;
      lista.push_back(values);
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
  const string PATH = "dados/titles.csv";
  ProgramaNetflix *temp;
  BstTree *bst = new BstTree(); // Objeto do tipo Arvore BST
  AvlTree *avl = new AvlTree(); // Objeto do tipo Arvore AVL
  // readArchive(bst, avl, "dados/titles.csv");
  int option = -1, step_bst, step_avl; // Variavel que armazena a opcao do usuario
  string input, archivePath, id, *values = nullptr; // Variavel que contem o caminho do arquivo para ler

  cout << "Bem vindo ao programa de Analise/Ciencia de dados com Arvores BST e AVL\n\n";
  cout << "Desenvolvedores:\n\tGustavo Teixeira dos Santos  TIA 32197020\n\tCleverson Pereira da Silva\n\tVictor Junqueira\n\tFelipe Nakandakari\n\tPedro\n\n";
  
  while(option != 8){
    cout << "\n\nO que deseja:\n\t1 - Ler dados de arquivo\n\t2 - Opcoes de Analise\n\t3 - Inserir Programa\n\t4 - Buscar Programa\n\t5 - Remover Programa\n\t6 - Exibir a Altura das Árvores\n\t7 - Salvar dados em arquivo\n\t8 - Encerrar Programa\nEscolha: ";
    getline(cin, input);
    option = isNumber(input) ? stoi(input) : -1;
    switch(option){
      case 1: // Ler dados de arquivo
        cout << "Digite 1 para ler o arquivo padrao ou passe o caminho do arquivo: ";
        getline(cin, archivePath);
        if(archivePath == "1"){
          readArchive(bst, avl, PATH);
        }else{
          readArchive(bst, avl, archivePath);
        }
        cout << endl; // Insere uma quebra de linha
      break;
      case 2: // Opcoes de Analise
      break;
      case 3: // Inserir Programa
      break;
      case 4: // Buscar Programa
        cout << "Digite o codigo do programa que voce deseja pesquisar: ";
        getline(cin, id);
        step_bst = 0;
        step_avl = 0;
        temp = avl->search(id, &step_avl); // Ja que as duas arvores estao sincronizadas, so eh necessario um dos dois valores para exibir os resultadosdo Programa na tela
        if(temp != nullptr && bst->search(id, &step_bst) != nullptr){
          temp->printValue();
        }else{
          cout << "\n\nValor nao encontrado!\n";
        }
        cout << "\nQuantidade de passos da checagem:\n\tAVL: " << step_avl << "\n\tBST: " << step_bst << endl;
        temp = nullptr;
      break;
      case 5: // Remover Programa
        cout << "\nDigite o id do item que deseja remover: ";
        getline(cin, id);
        step_bst = 0;
        step_avl = 0;
        if(bst->remove(id, &step_bst) && avl->remove(id, &step_avl)){
          cout << "\nExcluido com sucesso!";
          cout << "\nQuantidade de passos da para remocao:\n\tAVL: " << step_avl << "\n\tBST: " << step_bst << endl;
        }else{
          cout << "\nValor nao encontrado!" << endl;
        }
      break;
      case 6: // Exibir altura das Arvores
        step_bst = 0;
        step_avl = 0;
        cout << "\nA altura da Arvore AVL eh: " << avl->getHeight(avl->getRoot(), &step_avl) << endl;
        cout << "A altura da Arvore BST eh: " << bst->getHeight(bst->getRoot(), &step_bst) << endl;
      break;
      case 7: // Salvar dados em arquivo
        
      break;
      case 8: // Encerrar Programa
        delete values;
        values = nullptr;
      break;
      default: // Caso o usuário selecione outros valores
        cout << "\n\nPor favor, Digite um valor valido!!\n\n";
      break;
    }
  }

}
