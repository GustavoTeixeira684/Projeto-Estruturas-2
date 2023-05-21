#include "avl.hpp"

AvlTree::AvlTree(){ // Construtor padrao da arvore
  this->root = nullptr;
  this->col = nullptr;
  this->qntNodes = 0;
}

AvlTree::~AvlTree(){ // Destrutor padrao da arvore
  this->clear();
}

int AvlTree::getQntNodes(){ // Metodo para retornar a quantidade de nodes na arvore
  return this->qntNodes;
}

Column *AvlTree::getColumn(){ // Metodo para retornar oas valores da 'coluna' da arvore
  return this->col;
}

ProgramaNetflix *AvlTree::getRoot(){ // Retorna o primeiro elemento da arvore
  return this->root;
}

ProgramaNetflix *AvlTree::search(string id, int *step){ // Metodo para retornar um no com o valor escolhido pelo usuario (De forma iterativa)
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

int AvlTree::getHeight(ProgramaNetflix *node){ // Metodo para retornar a altura da arvore
  int alturaEsquerda, alturaDireita;
  if(node == nullptr){ // Se o node atual for = nullptr, retorna -1
    return -1;
  }
  alturaEsquerda = getHeight(node->getLeft()); // Caso contrario
  alturaDireita = getHeight(node->getRight()); // Calcula a altura dos filhos
  return alturaEsquerda > alturaDireita ? alturaEsquerda + 1 : alturaDireita  + 1; // Retorna o maior
}

int AvlTree::getBalance(ProgramaNetflix *node){ // Metodo que retorna o Fator de Balanceamento de uma subarvore
  return getHeight(node->getRight()) - getHeight(node->getLeft());

}

void AvlTree::leftRotate(ProgramaNetflix *node){ // Metodo para rotacionar para a esquerda
   // Como estamos utilizando a versao recursiva para otimizacao
   // Tambem estamos utilizando o ponteiro father para permitir fazer a chacegem do balanceamento (Que eh o que mais demora em uma arvore AVL) de forma otimizadao
   // Com isso, o custo eh funcoes de rotacao com mais linhas de codigo para gerenciar os ponteiros father
   // Porem, enquanto o metodo que checa o balanceamento da arvore passa itera diversas vezes percorrendo a arvore, os metodos de rotacao sao acionados poucas (ou nenhuma) vezes por insercao/remocao
   // Com isso, colocando na balança, decidimos que compensa para a otimizacao

  ProgramaNetflix *temp = node->getRight() ? node->getRight()->getLeft() : nullptr; // Se o node tem filho a direita, pegar o filho a esquerda do filho a direita. (Eh o node que sera perdido na rotacao. Mais a frente ele sera reinserido na arvore) 
  node->getRight()->setLeft(node); // Seta o node como filho a esquerda do filho a direita do node
  node->getRight()->setFather(node->getFather()); // Seta o pai da nova raiz da subarvore como o pai do node referencia da funcao (O node que estamos rotacionando). Se o node for a raiz ele recebera como pai nullptr
  if(node->getFather() != nullptr){ // Se o node tiver pai 
    node->getFather()->getRight() == node ? node->getFather()->setRight(node->getRight()) : node->getFather()->setLeft(node->getRight()); // Atualiza a referencia do novo node raiz da subarvore em referencia ao pai
  }else{ // Se nao tiver
    this->root = node->getRight(); // seta a nova raiz da subarvore como raiz a arvore por inteiro
  }
  node->setFather(node->getRight()); // Atualiza o pai do antigo node raiz da subarvore
  node->setRight(temp); // Pega o node/subarvore que estava na antiga posicao do node atual e coloca como filho a direita dele
  // Essa estrategia evita que facamos insercoes nos nodes perdidos durante a rotacao. Eh uma tecnica utilizada e testada, nao causa problemas na arvore e a mantem ordenada
  if(temp != nullptr){
    temp->setFather(node); // Atualiza o pai do node/subarvore que foi reinserido na arvore
  }
  temp = nullptr;
}

void AvlTree::rightRotate(ProgramaNetflix *node){ // Metodo para rotacionar para a direita
   // Como estamos utilizando a versao recursiva para otimizacao
   // Tambem estamos utilizando o ponteiro father para permitir fazer a checagem do balanceamento (Que eh o que mais demora em uma arvore AVL) de forma otimizada
   // Com isso, os custos sao funcoes de rotacao com mais linhas de codigo para gerenciar os ponteiros father
   // Porem, enquanto o metodo que checa o balanceamento da arvore passa itera diversas vezes percorrendo a arvore, os metodos de rotacao sao acionados poucas (ou nenhuma) vezes por insercao/remocao
   // Com isso, colocando na balança, decidimos que compensa para a otimizacao

  ProgramaNetflix *temp = node->getLeft() ? node->getLeft()->getRight() : nullptr; // Se o node tem filho a esquerda, pegar o filho a direita do filho a esquerda. (Eh o node que sera perdido na rotacao. Mais a frente ele sera reinserido na arvore) 
  node->getLeft()->setRight(node); // Seta o node como filho a direita do filho a esquerda do node
  node->getLeft()->setFather(node->getFather()); // Seta o pai da nova raiz da subarvore como o pai do node referencia da funcao (O node que estamos rotacionando). Se o node for a raiz ele recebera como pai nullptr
  if(node->getFather() != nullptr){ // Se o node tiver pai 
    node->getFather()->getRight() == node ? node->getFather()->setRight(node->getLeft()) : node->getFather()->setLeft(node->getLeft()); // Atualiza a referencia do novo node raiz da subarvore em referencia ao pai
  }else{ // Se nao tiver
    this->root = node->getLeft(); // seta a nova raiz da subarvore como raiz a arvore por inteiro
  }
  node->setFather(node->getLeft()); // Atualiza o pai do antigo node raiz da subarvore
  node->setLeft(temp); // Pega o node/subarvore que estava na antiga posicao do node atual e coloca como filho a esquerda dele
  // Essa estrategia evita que facamos insercoes nos nodes perdidos durante a rotacao. Eh uma tecnica utilizada e testada, nao causa problemas na arvore e a mantem ordenada
  if(temp!= nullptr){
    temp->setFather(node); // Atualiza o pai do node/subarvore que foi reinserido na arvore
  }
  temp = nullptr;
}

void AvlTree::balanceTree(ProgramaNetflix *node){ // Metodo para percorrer a arvore e a re-balancear
  // Trabalha de modo iterativo
  // Começa no node que foi inserido/removido e sobe ate a raiz de forma iterativa, checando o balanceamento
  // Forma iterativa e otimizada
  int nodeBalance;
  while(node != nullptr){ // Laço para percorrer a arvore (Pai do raiz eh nullptr).
    nodeBalance = getBalance(node); // Poga o FB da subarvore
    if(nodeBalance > 1){ // Se for > 1
      nodeBalance = getBalance(node->getRight()); // Pega o FB do filho da direita
      if(nodeBalance > 0){ // Se for maior que 0
        // Rotação simples à esquerda
        leftRotate(node); // Rotacao a esquerda na raiz da sub-arvore
      }else{ // Se for menor ou igual a 0
        // Rotação dupla à esquerda
        rightRotate(node->getRight()); // Rotacao a direita no filho a direita
        leftRotate(node); // Rotacao a esquerda na raiz da sub-arvore
      }
    }else if(nodeBalance < -1){
      nodeBalance = getBalance(node->getLeft());
      if(nodeBalance < 0){
        // Rotação simples à direita
        rightRotate(node);
      }else{
        // Rotação dupla à direita
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
        insert = false;
        break;
      }
      (*step)++; // Incrementa um para o contador de steps
    }
  }
  if(insert){ // Se foi possivel inserir o valor na arvore
    balanceTree(temp); // Chama o metodo para balancear a mesma
  }
  this->qntNodes++;
  aux = nullptr;
  temp = nullptr;
}

bool AvlTree::remove(string id, int *step){ // Metodo para remover um elemento da lista (De forma iterativa)
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
    if(newNode != nullptr){ // Se nao apagou um folha
      balanceTree(newNode); // Chama o metodo para balancear a arvore a partir do node
    }else{
      balanceTree(father); // Chama o metodo para balancear a arvore a partir do seu pai
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

void AvlTree::insertColumns(string *values){ // Metodo para inserir as 'colunas' da arvore
  if(this->col != nullptr){
    this->col->clear();
  }
  Column *temp = new Column(values);
  this->col = temp;
  temp = nullptr;
}

void AvlTree::clear(ProgramaNetflix *node){ // Metodo para limpar a arvore

  if(node != nullptr){
    clear(node->getLeft());
    clear(node->getRight());
    delete node;
  }
  
}

void AvlTree::clear(){ // Metodo para limpar a arvore
  clear(this->root);
  delete col;
}