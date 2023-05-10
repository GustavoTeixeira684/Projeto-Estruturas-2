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
    bst->insertColumns(dropIndex(strSplit(result, ';', &length),10, length));
    avl->insertColumns(dropIndex(strSplit(result, ';', &length),10,length));
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

void populateVector(ProgramaNetflix *node, vector<string*> *list){
  if(node != nullptr){
    populateVector(node->getLeft(), list);
    list->push_back(node->getValues());
    populateVector(node->getRight(), list);
  }
}

void writeArchive(AvlTree *avl, string path){
  ofstream fout(path);
  vector<string*> list;
  string *values = avl->getColumn()->getValues();
  populateVector(avl->getRoot(), &list);
  for(int i = 0; i < 1; i++){
    fout << values[i] << ";";
  }
  fout << values[13] << "\n";
  
  for(int i = 0; i < list.size(); i++){
    for(int j = 0; j < 13; j++){
      fout << list.at(i)[j] << ";";
    }
    fout << list.at(i)[13] << "\n";
  }

  // delete values;
  values = nullptr;
  
}

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
        cout << "Digite 1 se deseja salvar em um arquivo bkp padronizado (dados/titles_output.csv) ou digite o caminho para o novo arquivo: ";
        getline(cin, archivePath);
        if(archivePath == "1"){
          writeArchive(avl, "dados/titles_output.csv");
        }else{
          writeArchive(avl, archivePath);
        }
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
