#include "bst.hpp"

BstTree::BstTree(){
  this->root = nullptr;
}

void BstTree::print(){
  print(this->root, 0);
}

void BstTree::print(ProgramaNetflix *node, int space){
 	if (node != NULL){	
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

ProgramaNetflix *BstTree::search(string id){
  ProgramaNetflix *aux = this->root;
  int compare;
  while(aux != nullptr){
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
  while(aux != nullptr){
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



void BstTree::insert(string *values){
  ProgramaNetflix *aux = this->root;
  ProgramaNetflix *temp;
  int compare;
  if(aux == nullptr){
    temp = new ProgramaNetflix(values, nullptr);
    this->root = temp;
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
    }
  }
  aux = nullptr;
  temp = nullptr;
}

void BstTree::remove(string id){
  ProgramaNetflix *father, *aux, *newNode;
  aux = search(id, father);
  if(aux != nullptr){
    if(aux->getLeft() == nullptr || aux->getRight() == nullptr){ // Nó com um filho ou menor
      newNode = aux->getLeft() ? aux->getLeft() : aux->getRight(); // Pega o endereço do filho
      if(newNode != nullptr){ // Nó com apenas um filho
        if(aux == this->root){
          newNode->setFather(nullptr);
          this->root = newNode;
        }else{
          newNode->setFather(father); // O nó que ficará no lugar do que será excluido aponta para o pai do nó que será excluído
        }
      }
    }else{ // Nó com dois filhos
      newNode = aux->getLeft(); // Procura pelo maior dos menores
      while(newNode->getRight() != nullptr){
        newNode = newNode->getRight();
      }
        string *values = newNode->getValues(); // Troca os valores do nó
        newNode->updateValues(aux->getValues());
        aux->updateValues(values);
        aux = newNode; // Atualiza o nó que deverá ser apagado
        father = newNode->getFather();
        newNode = nullptr;
    }
    
    if(father->getLeft() == aux){
      father->setLeft(newNode);
    }else{
      father->setRight(newNode);
    }
    delete(aux);
    newNode = nullptr;
    aux = nullptr;
    father = nullptr;
  }else{
    cout << "\n\nValor não encontrado\n\n";
  }
}