#include "bst.hpp"

BstTree::BstTree(){ // Construtor padrao da arvore
  this->root = nullptr;
  this->col = nullptr;
  this->qntNodes = 0;
}

BstTree::~BstTree(){ // Destrutor padrao da arvore
  this->clear();
}
Column *BstTree::getColumn(){ // Metodo para retornar oas valores da 'coluna' da arvore
  return this->col;
}

int BstTree::getQntNodes(){ // Metodo para retornar a quantidade de nodes na arvore
  return this->qntNodes;
}

ProgramaNetflix *BstTree::getRoot(){ // Retorna o primeiro elemento da arvore
  return this->root;
}

int BstTree::getHeight(ProgramaNetflix *node){ // Metodo para retornar a altura da arvore
  int alturaEsquerda, alturaDireita;
  if(node == nullptr){ // Se o node atual for = nullptr, retorna -1
    return -1;
  }
  alturaEsquerda = getHeight(node->getLeft()); // Caso contrario
  alturaDireita = getHeight(node->getRight()); // Calcula a altura dos filhos
  return alturaEsquerda > alturaDireita ? alturaEsquerda + 1 : alturaDireita  + 1; // Retorna o maior
}

ProgramaNetflix *BstTree::search(string id, int *step){ // Metodo para retornar um no com o valor escolhido pelo usuario (De forma iterativa)
  ProgramaNetflix *aux = this->root; // Pega o a raiz da arvore
  int compare;
  while( aux != nullptr && aux->getId() != id){ // Repete ate encontrar o laco ou percorrer o caminho que 'devia' para encontrar o node e nao encontrar
    (*step)++; // Incrementa o contador de passos
    compare = stringCompare(id, aux->getId()); // Compara qual dos dois IDs eh 'maior' lexicograficamente
    if(compare == -1){ // Valor procurado maior que o do nó atual
      aux = aux->getRight(); // Itera para o filho a direita
    }else if(compare == 1){ // Valor procurado menor que o do nó atual
      aux = aux->getLeft(); // Itera para o filho a esquerda
    }
  }
  return aux; // Retorna o endereco do node caso ache e nullptr se nao encontrar
}


void BstTree::insert(string *values, int *step){ // Metodo para inserir um elemento na arvore (De forma iterativa)
  ProgramaNetflix *aux = this->root; // Pega a raiz da arvore
  ProgramaNetflix *temp;
  int compare;
  if(aux == nullptr){ // Se a arvore estiver vazia
    if(this->col == nullptr){ // Se ainda nao tiver valores nas 'colunas'
      this->col = new Column(); // Cria uma nova coluna com valores padrao
    }
    temp = new ProgramaNetflix(values, nullptr); // Cria o node
    this->root = temp; // Define ele como a raiz da arvore
    (*step)++; // Incrementa um para o contador de steps
  }else{ // Se a arvore nao estiver vazia
    while(1){ // Itera ate finalmente encontrar o ponto (usamos o while(1), pois nesse caso eh certeza que ele ira para quando inserir ou se o valor for repetido)
      compare = stringCompare(values[0], aux->getId()); // Compara se o ID do valor que estamos tentando inserir eh maior/menor que o do node atual que esta sendo checado
      if(compare == -1){ // Significa que o valor que estamos tentando inserir é maior que o que estamos comparando
        if(aux->getRight() != nullptr){ // Se o node tiver um filho a direita
          aux = aux->getRight(); // Itera para o filho a direita
        }else{ // Se nao tiver filho a direita
          temp = new ProgramaNetflix(values, aux); // Cria o node com os valores fornecidos
          aux->setRight(temp); // Define como filho a direita do no que estamos comparando
          break; // Encerra a funcao
        }
      }else if(compare == 1){ // Significa que o valor que estamos tentando inserir é menor que o que estamos comparando
        if(aux->getLeft() != nullptr){ // Se o node tiver um filho a esquerda
          aux = aux->getLeft(); // Itera para o filho a esquerda
        }else{ // Se nao tiver filho a esquerda
          temp = new ProgramaNetflix(values, aux); // Cria o node com os valores fornecidos
          aux->setLeft(temp); // Define como filho a esquerda do no que estamos comparando
          break; // Encerra a funcao
        }
      }else{ // Significa que o valor é o mesmo. Assim, não iremos inserir
        break;
      }
      (*step)++; // Incrementa um para o contador de steps
    }
  } // Limpa variaveis
  aux = nullptr;
  temp = nullptr;
  this->qntNodes++; // Incrementa um na quantidade de nodes
}

bool BstTree::remove(string id, int *step){ // Metodo para remover um elemento da lista (De forma iterativa)
  // Esse metodo foi desenvolvido utilizando a seguinte logica:
  // Se o node tiver dois filhos, encontrar o maior dos menores e trocar os valores. Assim nao precisamos ficar trocando nodes de posicao
  // Se o node tiver apenas um filho, remove o node e coloca seu filho como filho do pai do node que iremos remover
  // Se o node for folha, remove e tira a referencia a ele do pai
  ProgramaNetflix *father, *aux, *newNode;
  aux = search(id, step); // Procura onde esta o node que desejamos remover
  if(aux != nullptr){ // se o node for encontrado
    father = aux->getFather(); // Pega o pai desse node (Eh importante para a forma iterativa)
    if(aux->getLeft() != nullptr && aux->getRight() != nullptr){ // Nó com dois filhos
      newNode = aux->getLeft(); // Pega o filho a esquerda
      while(newNode->getRight() != nullptr){ // Itera ate encontrar o maior dos menores em referencia ao node que esta sendo removido
        newNode = newNode->getRight();
      }
      string *values = newNode->getValues(); // Pega os valores desse node
      newNode->updateValues(aux->getValues()); // Substititui seu valor pelo valor do node que desejamos apagar
      aux->updateValues(values); // Substitui os valores do node que desejamos apagar pelo do newNode
      aux = newNode; // Atualiza o node que devera ser removido
      father = aux->getFather(); // Atualiza o pai do node que sera removido (Importante para a versao iterativa)
      values = nullptr;
      newNode = nullptr;
    }

    if(aux->getLeft() == nullptr || aux->getRight() == nullptr){ // Nó com um filho ou nó folha
      newNode = aux->getLeft() ? aux->getLeft() : aux->getRight(); // Pega o endereço do filho (se tiver)
      if(newNode != nullptr){ // Se o nó tiver um filho
        newNode->setFather(father); // Coloca o filho do node que iremos remover como filho do pai do node que iremos remover
      }
    }

    if(aux != this->root){ // Se o node que desejamos remover nao for o raiz
      if(father->getLeft() == aux){ // Seta o node que ficara no lugar do que iremos remover na posicao certa em relacao ao pai
        father->setLeft(newNode);
      }else{
        father->setRight(newNode);
      }
    }else{ // Se for raiz
      this->root = newNode; // Seta seu filho como o raiz
    }
    delete(aux); // Apaga o node
    aux = nullptr;
    father = nullptr;
    newNode = nullptr;
    this->qntNodes = 0;
    return true;
  }else{
    return false;
  }
}

void BstTree::insertColumns(string *values){ // Metodo para inserir as 'colunas' da arvore
  if(this->col != nullptr){
    this->col->clear();
  }
  Column *temp = new Column(values);
  this->col = temp;
  temp = nullptr;
}

void BstTree::clear(ProgramaNetflix *node){ // Metodo para limpar a arvore

  if(node != nullptr){
    clear(node->getLeft());
    clear(node->getRight());
    delete node;
  }
  
}

void BstTree::clear(){ // Metodo para limpar a arvore
  clear(this->root);
  col->clear();
}
