#include "bst.hpp"

BstTree::BstTree(){
  this->root = nullptr;
  this->col = nullptr;
  this->qntNodes = 0;
}

void BstTree::print(){
  print(this->root, 0);
}

int BstTree::getQntNodes(){
  return this->qntNodes;
}

void BstTree::print(ProgramaNetflix *node, int space){
 	if (node != nullptr){	
    print(node->getRight(), space + 5);
    for (int k = 0; k < space; ++k){
	 	  cout << " ";
    }
    cout << node->getId() << "\n";
    print(node->getLeft(), space + 5);
  }
}

ProgramaNetflix *BstTree::getRoot(){
  return this->root;
}

int BstTree::getHeight(ProgramaNetflix *node, int *step){
  int alturaEsquerda, alturaDireita;
  (*step)++;
  if(node == nullptr){
    return -1;
  }
  alturaEsquerda = getHeight(node->getLeft(), step);
  alturaDireita = getHeight(node->getRight(), step);
  return alturaEsquerda > alturaDireita ? alturaEsquerda + 1 : alturaDireita + 1;
}

ProgramaNetflix *BstTree::search(string id, int *step){
  ProgramaNetflix *aux = this->root;
  int compare;
  while( aux != nullptr && aux->getId() != id){
    (*step)++;
    compare = stringCompare(id, aux->getId());
    if(compare == -1){ // Valor procurado maior que o do nó atual
      aux = aux->getRight();
    }else if(compare == 1){ // Valor procurado menor que o do nó atual
      aux = aux->getLeft();
    }
  }
  return aux;
}

ProgramaNetflix *BstTree::search(string id, ProgramaNetflix *father){
  ProgramaNetflix *aux = this->root;
  int compare;
  while( aux != nullptr && aux->getId() != id){
    father = aux;
    compare = stringCompare(id, aux->getId());
    if(compare == -1){ // Valor procurado maior que o do nó atual
      aux = aux->getRight();
    }else if(compare == 1){ // Valor procurado menor que o do nó atual
      aux = aux->getLeft();
    }
  }
  return aux;
}



void BstTree::insert(string *values, int *step){
  ProgramaNetflix *aux = this->root;
  ProgramaNetflix *temp;
  int compare;
  if(aux == nullptr){
    temp = new ProgramaNetflix(values, nullptr);
    this->root = temp;
    (*step)++;
  }else{
    while(1){
      compare = stringCompare(values[0], aux->getId());
      if(compare == -1){ // Significa que o valor que estamos tentando inserir é maior que o que estamos comparando
        if(aux->getRight() != nullptr){
          aux = aux->getRight();
        }else{
          temp = new ProgramaNetflix(values, aux);
          aux->setRight(temp);
          break;
        }
      }else if(compare == 1){ // Significa que o valor que estamos tentando inserir é menor que o que estamos comparando
        if(aux->getLeft() != nullptr){
          aux = aux->getLeft();
        }else{
          temp = new ProgramaNetflix(values, aux);
          aux->setLeft(temp);
          break;
        }
      }else{ // Significa que o valor é o mesmo. Assim, não iremos inserir
        break;
      }
      (*step)++;
    }
  }
  aux = nullptr;
  temp = nullptr;
  this->qntNodes++;
}

bool BstTree::remove(string id, int *step){
  ProgramaNetflix *father, *aux, *newNode;
  aux = search(id, step);
  if(aux != nullptr){
    father = aux->getFather();
    if(aux->getLeft() != nullptr && aux->getRight() != nullptr){ // Nó com dois filhos
      newNode = aux->getLeft();
      while(newNode->getRight() != nullptr){
        newNode = newNode->getRight();
      }
      string *values = newNode->getValues();
      newNode->updateValues(aux->getValues());
      aux->updateValues(values);
      aux = newNode;
      father = aux->getFather();
      values = nullptr;
      newNode = nullptr;
    }

    if(aux->getLeft() == nullptr || aux->getRight() == nullptr){ // Nó com um filho ou nó folha
      newNode = aux->getLeft() ? aux->getLeft() : aux->getRight();
      if(newNode != nullptr){ // Se o nó tiver um filho
        newNode->setFather(father);
      }
    }

    if(aux != this->root){
      if(father->getLeft() == aux){
        father->setLeft(newNode);
      }else{
        father->setRight(newNode);
      }
    }else{
      this->root = newNode;
    }
    delete(aux);
    aux = nullptr;
    father = nullptr;
    newNode = nullptr;
    this->qntNodes = 0;
    return true;
  }else{
    return false;
  }
}

void BstTree::insertColumns(string *values){
  if(this->col != nullptr){
    this->col->clear();
    delete col;
  }
  Column *temp = new Column(values);
  this->col = temp;
  temp = nullptr;
}
