#include "avl.hpp"

AvlTree::AvlTree(){
  this->root = nullptr;
  this->col = nullptr;
  this->qntNodes = 0;
}

void AvlTree::print(){
  print(this->root, 0);
  cout << endl;
}

int AvlTree::getQntNodes(){
  return this->qntNodes;
}

Column *AvlTree::getColumn(){
  return this->col;
}

void AvlTree::print(ProgramaNetflix *node, int space){
 	if (node != nullptr){	
    print(node->getRight(), space + 5);
    for (int k = 0; k < space; ++k){
	 	  cout << " ";
    }
    int temp = 0;
    cout << node->getId() << "[" << getBalance(node) << "]\n";
    print(node->getLeft(), space+5);
  }
}

ProgramaNetflix *AvlTree::getRoot(){
  return this->root;
}

ProgramaNetflix *AvlTree::search(string id, int *step){
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

// ProgramaNetflix *AvlTree::search(string id, ProgramaNetflix *father){
//   ProgramaNetflix *aux = this->root;
//   int compare;
//   while( aux != nullptr && aux->getId() != id){
//     father = aux;
//     compare = stringCompare(id, aux->getId());
//     if(compare == -1){ // Valor procurado maior que o do nó atual
//       aux = aux->getRight();
//     }else if(compare == 1){ // Valor procurado menor que o do nó atual
//       aux = aux->getLeft();
//     }
//   }
//   return aux;
// }

int AvlTree::getHeight(ProgramaNetflix *node){
  int alturaEsquerda, alturaDireita;
  if(node == nullptr){
    return -1;
  }
  alturaEsquerda = getHeight(node->getLeft());
  alturaDireita = getHeight(node->getRight());
  return alturaEsquerda > alturaDireita ? alturaEsquerda + 1 : alturaDireita + 1;
}

int AvlTree::getBalance(ProgramaNetflix *node){
  return getHeight(node->getRight()) - getHeight(node->getLeft());

}

void AvlTree::leftRotate(ProgramaNetflix *node){
  ProgramaNetflix *temp = node->getRight() ? node->getRight()->getLeft() : nullptr;
  node->getRight()->setLeft(node);
  node->getRight()->setFather(node->getFather());
  if(node->getFather() != nullptr){
    node->getFather()->getRight() == node ? node->getFather()->setRight(node->getRight()) : node->getFather()->setLeft(node->getRight());
  }else{
    this->root = node->getRight();
  }
  node->setFather(node->getRight());
  node->setRight(temp);
  if(temp != nullptr){
    temp->setFather(node);
  }
  temp = nullptr;
}

void AvlTree::rightRotate(ProgramaNetflix *node){
  ProgramaNetflix *temp = node->getLeft() ? node->getLeft()->getRight() : nullptr;
  node->getLeft()->setRight(node);
  node->getLeft()->setFather(node->getFather());
  if(node->getFather() != nullptr){
    node->getFather()->getRight() == node ? node->getFather()->setRight(node->getLeft()) : node->getFather()->setLeft(node->getLeft());
  }else{
    this->root = node->getLeft();
  }
  node->setFather(node->getLeft());
  node->setLeft(temp);
  if(temp!= nullptr){
    temp->setFather(node);
  }
  temp = nullptr;
}

void AvlTree::balanceTree(ProgramaNetflix *node){
  int nodeBalance;
  while(node != nullptr){
    nodeBalance = getBalance(node);
    if(nodeBalance > 1){
      nodeBalance = getBalance(node->getRight());
      if(nodeBalance > 0){
        // Rotação simples à esquerda
        // cout << "Rotação simples à esquerda" << endl;
        leftRotate(node);
      }else{
        // Rotação dupla à esquerda
        // cout << "Rotação dupla à esquerda\n";
        rightRotate(node->getRight());
        leftRotate(node);
      }
    }else if(nodeBalance < -1){
      nodeBalance = getBalance(node->getLeft());
      if(nodeBalance < 0){
        // Rotação simples à direita
        // cout << "Rotação simples à direita" << endl;
        rightRotate(node);
      }else{
        // Rotação dupla à direita
        // cout << "Rotação dupla à direita\n";
        leftRotate(node->getLeft());
        rightRotate(node);
      }
    }
    node = node->getFather();
  }
}

void AvlTree::insert(string *values, int *step){
  ProgramaNetflix *aux = this->root;
  ProgramaNetflix *temp;
  bool insert = true;
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
        insert = false;
        break;
      }
      (*step)++;
    }
  }
  if(insert){
    balanceTree(temp);
  }
  this->qntNodes++;
  aux = nullptr;
  temp = nullptr;
}

bool AvlTree::remove(string id, int *step){
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
    if(newNode != nullptr){
      balanceTree(newNode);
    }else{
      balanceTree(father);
    }
    aux = nullptr;
    father = nullptr;
    newNode = nullptr;
    this->qntNodes--;
    return true;
  }else{
    return false;
  }
}

void AvlTree::insertColumns(string *values){
  if(this->col != nullptr){
    this->col->clear();
    delete col;
  }
  Column *temp = new Column(values);
  this->col = temp;
  temp = nullptr;
}

