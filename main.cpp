// Gustavo Teixeira dos Santos 

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cmath>
#include <vector>
#include <locale.h>
#include "avl.hpp"
#include "bst.hpp"
#include "queue.hpp"
#include "utilidades.hpp"
using namespace std;

// ********** STRUCTS ********** //

// Para nossas analises, criamos struct para nos dar suporte no agrupamento de valores/atributos

typedef struct {  // Struct que armazena atributos/valores agrupados sobre o Elenco
  string codigo;
  string nome;
  int qnt;
}Summarize;

typedef struct{ // Struct que armazena o nome e a quantidade de filmes produzidos por pais.
  string nome;
  int qnt;
}Country;

typedef struct{ // Struct que armazena informações sobre os diretores e seus filmes produzidos
  string codigo;
  string nome;
  string filme;
  int qnt;
}Director;

typedef struct{ // Struct para armazenar dados estatisticos sobre os Scores das obras agrupados por decada
  int decade;
  float min;
  float max;
  float standard;
  float media;
  int count;
}t_Decade;

// ********** END STRUCTS ********** //

// ********** FILL FUNCTIONS ********** //


void fillVector(ProgramaNetflix *node, vector<string*> *list){ // Funçao para popular um vector string com as informaçoes contidas nas arvores
  if(node != nullptr){
    fillVector(node->getLeft(), list);
    list->push_back(node->getValues());
    fillVector(node->getRight(), list);
  }
}

void fillByType(ProgramaNetflix *node, vector<ProgramaNetflix*> *showList, vector<ProgramaNetflix*> *movieList){ // Funçao para popular dois vectors contendo as obras que sao movies e que sao shows
  // Sao gerados dois vectors para analise ao inves de popular um inteiro e procurar nesse vetor os dois tipos
  // Dessa forma, ao fim da funcao, temos dois conjuntos de dados segmentados para trabalharmos na analise
  if(node != nullptr){ // Utiliza o persurso pos-order para popular os vectors
    fillByType(node->getLeft(), showList, movieList);
    fillByType(node->getRight(), showList, movieList);
    string type = node->getType();
    float imdbScore = node->getImdbScore();
    if(imdbScore > 0){ // Como nosso programa le todos os dados do arquivo e coloca 0 para os valores nulos, nao consideramos esses valores para as analises, pois usamos medidas estatisticas sensiveis
      if(type == "SHOW"){ // Se for show
        showList->push_back(node); // insere no vector que armazena as informaçoes dos shows
      }else if(type == "MOVIE"){ // Se for Movie
        movieList->push_back(node); // insere no vector que armazena as informaçoes dos movies
      }
    }
  }
}

void fillDecade(ProgramaNetflix *node, vector<t_Decade*> *listDecades, vector<string*> *list){ // Funcao que armazena os valores da arvore em dois vectors
  // O primeiro eh um vector de ponteiro da struct t_Decade, que armazena as informaçoes estatisticas das obras agrupadas por decada
  // O segundo eh um vector que contem os dados da arvore. Utilizamos o mesmo para as analises posteriores
  // Nao incluimos aqui pois essa funcao trabalha de forma recursiva, o que seria um problema incluindo duas etapas diferentes, mesmo que da mesma analise
  // Apos essa funcao, o segundo vector eh usado para calculo do desvio padrao.
  // Utiliza pre-ordem
  if(node != nullptr){


    bool verifier = false;
    t_Decade *temp;
    int tempDecade;
    string *values;
    values = node->getValues();
    if(stoi(values[4]) > 0){ // Se houver ano de lançamento preenchido
      tempDecade = stoi(values[4])/10; // Captura a decada
      verifier = false; // Seta a variavel que controla a inserçao como falsa
      for(int i = 0; i < listDecades->size(); i++){ // Percorre o vector de struct
        if(listDecades->at(i)->decade == tempDecade){ // Se a decada ja estiver preenchida no vector
          listDecades->at(i)->media += stof(values[11]); // Incrementa o valor contido no node atual para calculo da media
          listDecades->at(i)->count++; // Incrementa a quantidade de filmes da decada
          if(stof(values[11]) > 0 && listDecades->at(i)->min > stof(values[11])){ // Atualiza o menor valor caso seja necessario
            listDecades->at(i)->min = stof(values[11]);
          }
          if(listDecades->at(i)->max < stof(values[11])){ // Atualiza o maior valor caso seja necessario
            listDecades->at(i)->max = stof(values[11]);
          }
          verifier = true; // Seta verifier como true, informando que a decada ja existe no vector e que o valor foi atualizado
        }
      }
      if(!verifier){ // Se a decada ainda nao existir no vector, verifier sera false
        temp = new t_Decade[1]; // Cria novo objeto da struct e atribui os valores do programa a ele
        temp->count = 1;
        temp->decade = tempDecade;
        temp->max = stof(values[11]);
        temp->min = temp->max;
        temp->media = temp->min;
        temp->standard = 0;
        listDecades->push_back(temp); // Insere no vector
      }
    }
    list->push_back(values); // Insere as informacoes do node no segundo vector

    fillDecade(node->getLeft(), listDecades, list);
    fillDecade(node->getRight(), listDecades, list);
  }
}

void fillCountry(ProgramaNetflix *node, vector<Country*> *listCountry){ // Funcao que percorre a arvore e adiciona os valores sobre os filmes agrupados por pais de producao
  if(node != nullptr){
    fillCountry(node->getLeft(), listCountry);
    bool verifier = false;
    int length;
    string *values, *vetCountry;
    Country *temp;
    values = node->getValues(); // Pega os valores do node atual
    if(values[8] != "" && values[8] != "[]"){ // Checa se ha de fato um pais de producao inscrito
      vetCountry = strSplit(clearChar(clearChar(clearChar(values[8], ' '), ']'), '['),',', &length); // Limpa caracteres indesejados e quebra a coluna em um array para analise de cada caso
      for(int i = 0; i < length; i++){ // Laço para percorrer os paises de producao do node atual
        verifier = false; // Variavel booleana que controla a inserçao
        for(int j = 0; j < listCountry->size(); j++){ // Laço para percorrer o vector de struct Country
          if(listCountry->at(j)->nome == vetCountry[i]){ // se o pais ja estiver inserido no vector
            listCountry->at(j)->qnt++; // Incrementa a quantidade
            verifier = true; // Variavel setada como true para indicar que o pais ja existe na struct e foi atualizado
            break;
          }
        }
        if(!verifier){ // Se o pais ainda nao existir na struct, insere
          temp = new Country[1];
          temp->nome = vetCountry[i];
          temp->qnt = 1;
          listCountry->push_back(temp);
        }
      }
      // Limpa variaveis
      temp = nullptr;
      delete[] values;
      delete[] vetCountry;
    }
    fillCountry(node->getRight(), listCountry);
  }
}

void fillBst(BstTree *bst, AvlTree *avl, vector<string> *list){ // Funçao que le um vector e armazena os valores nas duas arvores utilizadas no programa
  string *values;
  int length, step_bst, step_avl;
  step_bst = 0;
  step_avl = 0;
  for(int i = 0; i < list->size(); i++){ // Laço para percorrer o vector contendo as informaçoes lidas no titles.csv
    values = strSplit(list->at(i), ';', &length); // Quebra a string em um array separando-as por ';'
    fillEmpty(values, &length); // Preenche os valores nulos que vieram nas colunas numericas
    bst->insert(values, &step_bst); // Insere na arvore bst
    avl->insert(values, &step_avl); // Insere na arvore avl
  }
  cout << "Passos Bst: " << step_bst << " com " << bst->getQntNodes() << " nos inseridos" << endl << "Passos Avl: " << step_avl << " com " << avl->getQntNodes() << " nos inseridos" << endl; // Exibe informaçoes de passos realizados e quantidade de nodes nas arvores
}



// ********** END FILL FUNCTIONS ********** //

// ********** SORT FUNCTIONS ********** //

template <typename T>
void sortStruct(vector<T*> **sample, int inferior, int superior){ // Funcao template para ordenar structs que possuem o atributo 'qnt'
  // Ordenaçao baseada no algoritmo Mergesort. Pois eh um dos melhores algoritmos para ordenacao e trabalha sobre o conceito de dividir para conquistar
  // Funcao utilizada para ordernar para apresentar a analise
  // Como temos mais de um struct com o atributo qnt q ambos sao ordenados de forma decrescente, criamos uma funcao template para poder se utilizada em ambos os casos
  if(superior - inferior > 0){
    int meio, i, j, k;
    vector<T*> temp;    
    meio = floor((superior+inferior)/2);
    sortStruct(sample, inferior, meio);
    sortStruct(sample, meio+1, superior);
    i = inferior;
    j = meio + 1;
    k = 0;

    while(i <= meio && j <= superior){
      if((*sample)->at(i)->qnt > (*sample)->at(j)->qnt){
        temp.push_back((*sample)->at(i));
        i++;
      }else{
        temp.push_back((*sample)->at(j));
        j++;
      }
      k++;
    }
    while(i <= meio){
      temp.push_back((*sample)->at(i));
      i++;
    }
    while(j <= superior){
      temp.push_back((*sample)->at(j));
      j++;
    }
    for(int x = inferior; x <= superior; x++){
      (*sample)->at(x) = temp.at(x-inferior);
    }
  }
}

void sortType(vector<ProgramaNetflix*> *list, int inferior, int superior){ // Funcao de ordenacao para ordenar o vector de forma crescente a partir do IMDB Scorda
  // Ordenacao tambem baseada no algoritmo MergeSort
  // Funcao necessaria pois para o calculo de Outliers usando o metodo interquartil eh necessario que o vector esteja ordenado de forma crescente
    if(superior - inferior > 0){
    int meio, i, j, k;
    vector<ProgramaNetflix*> temp;    
    meio = floor((superior+inferior)/2);
    sortType(list, inferior, meio);
    sortType(list, meio+1, superior);
    i = inferior;
    j = meio + 1;
    k = 0;

    while(i <= meio && j <= superior){
      if(list->at(i)->getImdbScore() < list->at(j)->getImdbScore()){
        temp.push_back(list->at(i));
        i++;
      }else{
        temp.push_back(list->at(j));
        j++;
      }
      k++;
    }
    while(i <= meio){
      temp.push_back(list->at(i));
      i++;
    }
    while(j <= superior){
      temp.push_back(list->at(j));
      j++;
    }
    for(int x = inferior; x <= superior; x++){
      list->at(x) = temp.at(x-inferior);
    }
  }
}

void sortDecade(vector<t_Decade*> *sample, int inferior, int superior){ // Funcao para ordenar o vector com as structs t_Decade de forma crescente por decada
  // Funcao baseada no algoritmo de ordenacao MergeSort
  // Necessario para exibicao para o usuario
  if(superior - inferior > 0){
    int meio, i, j, k;
    vector<t_Decade*> temp;    
    meio = floor((superior+inferior)/2);
    sortDecade(sample, inferior, meio);
    sortDecade(sample, meio+1, superior);
    i = inferior;
    j = meio + 1;
    k = 0;

    while(i <= meio && j <= superior){
      if(sample->at(i)->decade < sample->at(j)->decade){
        temp.push_back(sample->at(i));
        i++;
      }else{
        temp.push_back(sample->at(j));
        j++;
      }
      k++;
    }
    while(i <= meio){
      temp.push_back(sample->at(i));
      i++;
    }
    while(j <= superior){
      temp.push_back(sample->at(j));
      j++;
    }
    for(int x = inferior; x <= superior; x++){
      sample->at(x) = temp.at(x-inferior);
    }
  }
}

// ********** END SORT FUNCTIONS ********** //


// ********** MERGE FUNCTION ********** //


void mergeCredits(AvlTree *avl, Queue *credits, Queue *finalQueue, vector<Summarize*> *elenco){ // Funcao que cruza a arvore com a base de creditos, gerando uma fila com os dados cruzados e constroi um vector de struct contendo elencos por filme.
  // Nessa funçao utilizamos algumas tecnicas visando a otimizaçao
  // 1 - Decidimos criar uma estrutura de dados Fila, pois em um cruzamento no estilo em que fizemos, uma das bvases eh percorrida por completo e a outra eh usada para encontrar a chave correspondente
  // Com isso, utilizamos uma fila por conta da sua rapida insercao, remoçao e ser rapida para percorre-la no nosso cenario (Uma vez que apos o item ser checado ele pode ser removido).
  // 2 - Analisando que a base de credito possui muitos registros com o id da obra repetido em sequencia, criamos um ponteiro temporario que ira armazenar o valor da ultima checagem
  // Dessa forma, para casos repetidos e em sequencia, nao sera necessario percorrer a arvore novamente procurando o mesmo valor. Poupando tempo.
  // 3 - Ainda visando os dados repetidos em sequencia, ao inserir os valores no vector de struct, percorremos o mesmo de tras para frente, assim em casos repetidos serao feitas bem menos comparaçoes
  ProgramaNetflix *temp = nullptr;
  Summarize *elencoTemp;
  string *valuesTitles, *valuesCredits, *valuesfinal;
  bool verifier = false;
  valuesfinal = new string[19]; // Inicia vetor que armazenada os valores cruzados e sera enviado para insercao na fila
  int step = 0;
  while(credits->getSize() > 0){ // Laço que percorre toda a fila contendo os creditos
    verifier = false;
    valuesCredits = credits->front(); // Pega o primeiro valor da fila
    if(temp == nullptr || temp->getId() != valuesCredits[1]){ // Se o valor atual for diferente do checado anteriormente
      temp = avl->search(valuesCredits[1], &step); // Procura o valor na rvore
      if(temp != nullptr){ // se o valor for encontrado
        valuesTitles = temp->getValues(); // Pega os valores da arvore para insercao na fila mais abaixo
      }
    }
    if(temp != nullptr){ // Se o valor foi encontrado na arvore
      for(int i = 0; i < 15; i++){ // Insere os campos da arvore
        valuesfinal[i] = valuesTitles[i];
      }
      // Como sao so quatro valores e sempre a mesma casa. Foi optado por escrever assim ao inves de abrir um laço for com condicional para evitar o indice 1 (Que eh o indice do id que sera repitido se for inserido)
      valuesfinal[15] = valuesCredits[0]; // Insere os campos da base de creditos
      valuesfinal[16] = valuesCredits[2];
      valuesfinal[17] = valuesCredits[3];
      valuesfinal[18] = valuesCredits[4];
      finalQueue->push(valuesfinal); // Insere na fila com os dados finais

      // Bloco da funcao para armazenar os dados em um vector de Struct para apresentar informaçoes sumarizadas para o usuario
      if(elenco != nullptr){ // Se o valor foi encontrado na arvore
        if(!elenco->empty()){
            for(int i = elenco->size() - 1; i >= 0; i--){ // Percorre a struct de forma inversa
              if(elenco->at(i)->codigo == valuesfinal[0]){ // Se o filme ja estiver sido inserido no vector
                elenco->at(i)->qnt++; // atualiza a quantidade de membror do elenco
                verifier = true;
                break;
              }
            }
          }
          if(!verifier){ // Se o filme ainda nao existir no vecotr, insere.
            elencoTemp = new Summarize[1];
            elencoTemp->codigo = valuesfinal[0];
            elencoTemp->nome = valuesfinal[1];
            elencoTemp->qnt = 1;
            elenco->push_back(elencoTemp);
          }
        }  
      }
        
    credits->pop(); // Apaga o primeiro item da fila de creditos, partindo para a proxima analise
  }
  if(elenco != nullptr){
    sortStruct(&elenco, 0, elenco->size()-1); // Ordena o vector de struct para exibicao ao usuario
  }
}

// ********** END MERGE FUNCTION ********** //

// ********** READ & WRITE FUNCTIONS********** //


void readCredits(Queue *credits, string path){ // Funçao para ler o arquivo de creditos
  ifstream file;                  // Objeto para leitura de arquivo
  vector<string> list;            // Vetor para armazenar linhas do arquivo
  string result, values, *input;   // Variaveis auxiliares
  int length;                     // Variavel para armazenar o comprimento do array
  file.open(path);                // Abre o arquivo especificado pelo caminho 'path'
  
  if(!file.fail()){               // Verifica se a abertura do arquivo foi bem-sucedida
    getline(file, result, '\n');   // Le e descarta a linha de cabeçalho
    int k = 0;
    while(file.peek() != EOF){    // Enquanto nao chegar ao final do arquivo
      values = "";                // Reinicia a variavel 'values' para cada linha do arquivo
      for(int i = 0; i < 4; i++){ // Realiza um loop quatro vezes para obter quatro valores separados por ';'
        getline(file, result, ';');  // Le cada valor separado por ';'
        values += result + ";";      // Concatena o valor à string 'values' seguido por ';'
      }
      getline(file, result, '\n');  // Le o ultimo valor da linha, terminado por '\n'
      values += result;             // Concatena o ultimo valor à string 'values'
      input = strSplit(values, ';', &length);  // Divide a string 'values' em um array de strings usando ';' como separador
      credits->push(input);         // Insere o array de strings na fila 'credits'
      k++;
    }
  }
}

void readArchive(BstTree *bst, AvlTree *avl, string path) { // Funçao para ler o arquivo
  ifstream file; // Declaraçao do objeto ifstream para ler o arquivo
  int count, length; // Variaveis para armazenar o numero de colunas e o comprimento
  char sep; // Caractere separador
  string result, values, *joj; // Strings para armazenar resultados intermediarios
  vector<string> lista; // Vetor para armazenar as linhas do arquivo
  file.open(path); // Abre o arquivo especificado pelo caminho 'path'

  if (!file.fail()) { // Verifica se a abertura do arquivo foi bem-sucedida
    getline(file, result, '\n'); // Le a primeira linha do arquivo e armazena em 'result'

    // Insere as colunas nas arvores bst e avl
    bst->insertColumns(strSplit(result, ';', &length));
    avl->insertColumns(strSplit(result, ';', &length));

    int k = 0;
    while (file.peek() != EOF) { // Enquanto nao atingir o final do arquivo
      values = "";
      for (int i = 0; i < 14; i++) { // Le 14 valores separados por ponto e virgula (;)
        file.get(sep);
        if (sep != ';') {
          getline(file, result, ';');
          values += sep + result + ";";
        } else {
          values += ";";
        }
      }
      getline(file, result, '\n'); // Le o restante da linha ate o caractere de nova linha (\n)
      values += result;
      lista.push_back(values); // Adiciona a linha ao vetor 'lista'
      k++;
    }
  }

  fillBst(bst, avl, &lista); // Preenche as arvores bst e avl com os valores do vetor 'lista'
  lista.clear(); // Limpa o vetor 'lista' apos o preenchimento
}

void writeArchive(AvlTree *avl, string path){ // Funçao para gravar os dados da arvore em um arquivo
  ofstream fout(path); // Abre o arquivo para escrita
  vector<string*> list; // Declara um vetor de ponteiros para strings
  string *values = avl->getColumn()->getValues(); // Obtem os valores da coluna da arvore AVL
  fillVector(avl->getRoot(), &list); // Preenche o vetor 'list' com os valores da arvore AVL
  for(int i = 0; i < 14; i++){ // Loop para escrever os valores das colunas separados por ';'
    fout << values[i] << ";"; // Escreve o valor da coluna seguido por ';'
  }
  fout << values[14] << "\n"; // Escreve o ultimo valor da coluna e quebra de linha
  
  for(int i = 0; i < list.size(); i++){ // Loop para percorrer os elementos do vetor 'list'
    for(int j = 0; j < 14; j++){ // Loop para escrever os valores dos elementos separados por ';'
      fout << list.at(i)[j] << ";"; // Escreve o valor do elemento seguido por ';'
    }
    fout << list.at(i)[14] << "\n"; // Escreve o ultimo valor do elemento e quebra de linha
  }

  delete[] values;
  values = nullptr; // Define o ponteiro 'values' como nulo
}

void writeMerged(Queue *lista, string path, string *columns) { // Funçao para gravas os dados cruzados entre titles e credits em um arquivo
  ofstream fout(path); // Cria um objeto de fluxo de saida para o arquivo especificado por 'path'
  string *values; // Declara um ponteiro para uma string chamado 'values'
  
  // Gravando colunas
  for(int i = 0; i < 15; i++){ // Loop para gravar as colunas
    fout << columns[i] << ";"; // Escreve o valor de 'columns[i]' seguido por um ponto e virgula no arquivo
  }
  fout << "actor_id;name;character;role" << endl; // Escreve a string "actor_id;name;character;role" no arquivo

  while(lista->getSize() > 0){ // Loop enquanto a fila nao estiver vazia
    values = lista->front(); // Obtem o primeiro conjunto de valores da fila e atribui a 'values'
    for(int i = 0; i < 18; i++){ // Loop para iterar sobre os valores em 'values'
      fout << values[i] << ";"; // Escreve o valor de 'values[i]' seguido por um ponto e virgula no arquivo
    }
    fout << values[18] << endl; // Escreve o ultimo valor de 'values' no arquivo, seguido por uma nova linha
    lista->pop(); // Remove o primeiro elemento da fila
  }
}

// ********** END READ & WRITE FUNCTIONS ********** //

// ********** ANALYTICAL FUNCTIONS ********** //

void getOutlierByType(AvlTree *avl, int option) { // Funcao para pegar Outliers em cada um dos tipos de programa netflix
  // Option 1 eh para encontrar programas com a nota acima do comum e 0 para abaixo

  vector<ProgramaNetflix*> showList, movieList; // Vetores para armazenar programas de TV e filmes
  vector<ProgramaNetflix*> OutlierList; // Vetor para armazenar os programas "outliers"
  int index;
  float media, imdbScore, iqr, q1, q3;
  fillByType(avl->getRoot(), &showList, &movieList); // Preenche os vetores showList e movieList com os programas de TV e filmes

  // TIPO SHOW // 

  sortType(&showList, 0, showList.size()-1); // Ordena o vetor showList com base no IMDB Score
  q3 = showList.at(floor(showList.size() * 0.75))->getImdbScore(); // Calcula o terceiro quartil do IMDB Score
  q1 = showList.at(floor(showList.size() * 0.25))->getImdbScore(); // Calcula o primeiro quartil do IMDB Score
  iqr = q3 - q1; // Calcula a amplitude interquartil (IQR)
  cout << "\n\nTipo: SHOW";
  for(int i = 0; i < showList.size(); i++) {
    // Verifica se o programa e um "outlier" com base na opçao e no IMDB Score
    if((option == 1 && showList.at(i)->getImdbScore() > (q3 + 1.5*iqr)) || (option == 0 && showList.at(i)->getImdbScore() < (q1 - 1.5*iqr))) {
      cout << "\n\tID: " << showList.at(i)->getId() << " Titulo: " << showList.at(i)->getTitle() << " IMDB Score: " << showList.at(i)->getImdbScore();
    }
  }

  // TIPO MOVIE //

  sortType(&movieList, 0, movieList.size()-1); // Ordena o vetor movieList com base no IMDB Score
  q3 = movieList.at(floor(movieList.size() * 0.75))->getImdbScore(); // Calcula o terceiro quartil do IMDB Score
  q1 = movieList.at(floor(movieList.size() * 0.25))->getImdbScore(); // Calcula o primeiro quartil do IMDB Score
  iqr = q3 - q1; // Calcula a amplitude interquartil (IQR)
  cout << "\n\nTipo: MOVIE";
  for(int i = 0; i < movieList.size(); i++) {
    // Verifica se o programa e um "outlier" com base na opçao e no IMDB Score
    if((option == 1 && movieList.at(i)->getImdbScore() > (q3 + 1.5*iqr)) || (option == 0 && movieList.at(i)->getImdbScore() < (q1 - 1.5*iqr))) {
      cout << "\n\tID: " << movieList.at(i)->getId() << " Titulo: " << movieList.at(i)->getTitle() << " IMDB Score: " << movieList.at(i)->getImdbScore();
    }
  }

  showList.clear(); // Limpa o vetor showList
  movieList.clear(); // Limpa o vetor movieList
}


void getDirectorMovie(AvlTree *avl, vector<Director*> *director) { // Funçao para encontrar e agrupar os filmes por diretor
  // Da forma como construimos, ele armazena na lista de diretores os dados do diretor e controi uma string com todos os filmes que o diretor participou

  bool verifier = false; // Variavel para verificar se o diretor ja existe na lista
  string *values; // Ponteiro para armazenar os valores da fila
  Director *temp; // Ponteiro temporario para um diretor
  Queue *credits = new Queue(5); // Criaçao de uma fila chamada "credits" com capacidade 5
  Queue *finalCredits = new Queue(19); // Criaçao de uma fila chamada "finalCredits" com capacidade 19
  readCredits(credits, "dados/credits.csv"); // Leitura dos creditos de um arquivo e armazenamento na fila "credits"
  mergeCredits(avl, credits, finalCredits, nullptr); // Mescla os creditos da fila "credits" com a arvore AVL
  delete credits; // Libera a memoria ocupada pela fila "credits"

  while(finalCredits->getSize() > 0) { // Enquanto a fila "finalCredits" nao estiver vazia
    verifier = false; // Reinicializa a variavel "verifier" como falsa
    values = finalCredits->front(); // Obtem o primeiro elemento da fila "finalCredits" e armazena em "values"

    if(values[18] == "DIRECTOR") { // Verifica se o valor na posiçao 18 de "values" e "DIRECTOR"
      if(director->size() > 0) { // Verifica se o vetor de diretores nao esta vazio
        for(int i = 0; i < director->size(); i++) { // Percorre o vetor de diretores
          if(director->at(i)->codigo == values[15]) { // Verifica se o codigo do diretor atual e igual ao valor na posiçao 15 de "values"
            director->at(i)->qnt++; // Incrementa a quantidade de filmes do diretor atual
            director->at(i)->filme += "\n\t" + values[1]; // Adiciona o nome do filme atual à lista de filmes do diretor
            verifier = true; // Define a variavel "verifier" como verdadeira para indicar que o diretor foi encontrado
            break; // Sai do loop
          }
        }
      }

      if(!verifier) { // Se o diretor nao foi encontrado na lista
        temp = new Director[1]; // Aloca memoria para um novo objeto Diretor
        temp->codigo = values[15]; // Define o codigo do diretor
        temp->nome = values[16]; // Define o nome do diretor
        temp->filme = values[1]; // Define o primeiro filme do diretor
        temp->qnt = 1; // Define a quantidade de filmes como 1
        director->push_back(temp); // Adiciona o diretor ao vetor de diretores
      }
    }
    finalCredits->pop(); // Remove o primeiro elemento da fila "finalCredits"
  }

  sortStruct(&director, 0, director->size()-1); // Ordena o vetor de diretores com base no codigo
}

void getDataByDecade(AvlTree *avl) { // Funçao que pega dados estatisticos agrupados por decada
  float tempStandard; // Variavel temporaria para calculo do desvio padrao
  vector<string*> *list = new vector<string*>(); // Vetor dinamico para armazenar os dados
  vector<t_Decade*> *listDecades = new vector<t_Decade*>(); // Vetor dinamico para armazenar as decadas calculadas
  fillDecade(avl->getRoot(), listDecades, list); // Preenche os vetores com as decadas e os dados correspondentes

  // Itera sobre as decadas calculadas
  for(int i = 0; i < listDecades->size(); i++) {
    tempStandard = 0;

    // Calcula a media da decada atual
    listDecades->at(i)->media /= listDecades->at(i)->count;

    // Itera sobre os dados
    for(int j = 0; j < list->size(); j++) {
      // Verifica se o dado pertence à decada atual
      if(stoi(list->at(j)[4])/10 == listDecades->at(i)->decade) {
        // Calcula o valor do desvio padrao
        tempStandard += pow(stof(list->at(j)[11]) - listDecades->at(i)->media, 2);
      }
    }

    // Calcula o desvio padrao da decada atual
    listDecades->at(i)->standard = sqrt(tempStandard / listDecades->at(i)->count);
  }

  // Ordena as decadas em ordem crescente
  sortDecade(listDecades, 0, listDecades->size()-1);

  // Itera sobre as decadas para exibir os resultados
  for(int i = 0; i < listDecades->size(); i++) {
    if(listDecades->at(i)->media > 0) {
      std::cout << std::fixed << std::setprecision(2);
      cout << "\n\nDecada: " << listDecades->at(i)->decade << "0\n\tMedia: " << listDecades->at(i)->media << "\n\tMenor Valor: " << listDecades->at(i)->min;
      cout << "\n\tMaior Valor: " << listDecades->at(i)->max << "\n\tDesvio Padrao: " << listDecades->at(i)->standard; 
    }
  }

  // Limpa os vetores e libera a memoria alocada dinamicamente
  listDecades->clear();
  list->clear();
  delete listDecades;
  delete list;
}


void getTitlePerCountry(AvlTree *avl){
  // Cria um novo vetor dinâmico para armazenar os paises
  vector<Country*> *listCountry = new vector<Country*>();

  // Preenche o vetor com os paises presentes na arvore AVL agrupados
  fillCountry(avl->getRoot(), listCountry);

  // Ordena o vetor de paises agrupados de forma decrescente para exibiçao
  sortStruct(&listCountry, 0, listCountry->size()-1);

  // Itera sobre cada pais no vetor e imprime o nome e a quantidade correspondente
  for(int i = 0; i < listCountry->size(); i++){
    cout << "Nome: " << listCountry->at(i)->nome << " Quantidade: " << listCountry->at(i)->qnt << endl;
  }

  // Limpa o vetor e libera a memoria alocada
  listCountry->clear();
  delete listCountry;
}

// ********** END ANALYTICAL FUNCTIONS ********** //

int main() {
  setlocale(LC_ALL, "Portuguese");
  const string PATH = "dados/titles.csv";
  ProgramaNetflix *temp;vector<Director*> *director = new vector<Director*>();
  BstTree *bst = new BstTree(); // Objeto do tipo Arvore BST
  AvlTree *avl = new AvlTree(); // Objeto do tipo Arvore AVL
  Queue *credits, *finalQueue; // Filas utilizadas para lidar com a base de creditos e a base cruzada
  vector<Summarize*> elenco; // Vector que armazena o elenco
  credits = new Queue(5); // Inicia a Fila Credits com 5 colunas
  finalQueue = new Queue(19); // Inicia a Fila finalQueue com 19 colunas
  int option = -1, step_bst, step_avl; // Variavel que armazena a opcao do usuario
  string input, archivePath, id, *values = nullptr; // Variavel que contem o caminho do arquivo para ler

  cout << "Bem vindo ao programa de Analise/Ciencia de dados com Arvores BST e AVL\n\n";
  cout << "Desenvolvedores:\n\tGustavo Teixeira dos Santos  TIA 32197020\n\tCleverson Pereira da Silva  TIA 32198531\n\tVictor Junqueira  TIA 42123712\n\tFelipe Nakandakari  TIA 42104701\n\tPedro Catarino  TIA 42105951\n\n";
  
  while(option != 8){ // Itera ate o usuario digitar 8 = encerrar programa
    cout << "\n\nO que deseja:\n\t1 - Ler dados de arquivo\n\t2 - Opcoes de Analise\n\t3 - Inserir Programa\n\t4 - Buscar Programa\n\t5 - Remover Programa\n\t6 - Exibir a Altura das arvores\n\t7 - Salvar dados em arquivo\n\t8 - Encerrar Programa\nEscolha: ";
    cin >> option;
    switch(option){
      case 1: // Ler dados de arquivo
        getchar();
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
        if(avl->getRoot() != nullptr){
          cout << "Qual analise dejesa:\n\t1 - 20 filmes com os maiores elencos\n\t2 - Titulos com o IMDB Score acima ou abaixo do comum\n\t3 - Filmes por Diretor (para diretores com mais de um filme) ";
          cout << "\n\t4 - Dados estatisticos sobre as decadas\n\t5 - Quantidade de filmes por pais\nEscolha: ";
          cin >> option;
          switch(option){
            case 1: // Opçao para exibir os 20 filmes com os maiores elencos
              readCredits(credits, "dados/credits.csv"); // Le os creditos
              mergeCredits(avl, credits, finalQueue, &elenco); // Cruza os dados com a arvore
              cout << "\nRelacao de elenco por titulo em ordem crescente:\n\n";
              cout << "Id titulo | Nome titulo | Quantidade pessoas no Elenco\n";
              for(int i = 0; i < 20; i++){ // Exibe os 20 maiores para o usuario
                cout << "\t" << elenco.at(i)->codigo << "|" << elenco.at(i)->nome << "|" << elenco.at(i)->qnt << endl;
              }

              // Pergunta se o usuario deseja que seja gerada uma base com os dados cruzados
              cout << "\n\nUma base consolidada foi gerada a partir do cruzamento de titulos e creditos. Deseja salvar? (1 para sim e 0 para nao): ";
              cin >> option;
              if(option == 1){ // Caso o usuario queira, grava o arquivo
                getchar();
                cout << "Digite o caminho para onde deseja salvar o arquivo: ";
                getline(cin, input);
                writeMerged(finalQueue, input, avl->getColumn()->getValues());
              }
              elenco.clear();

            break;
            case 2: // Titulos com o IMDB Scorde acima ou abaixo do comum
              cout << "Digite 1 para acima do comum e 0 para abaixo do comum: ";
              cin >> option;
              getOutlierByType(avl, option); // Chama funçao que exibe os outliers por tipo de show
            break;
            case 3: // Filmes por Diretor
              getDirectorMovie(avl, director); // Chama funçao que retorna os filmes que os diretores fizeram
              cout << "Codigo | Nome | Quantidade\n";
              for(int i = 0; i < director->size(); i++){
                if(director->at(i)->qnt > 1){ // Exibe a lista
                  cout << director->at(i)->codigo << " | " << director->at(i)->nome << " | " << director->at(i)->qnt << endl;
                }
              }
              getchar();
              // Permite com que o usuario digite o codigo de algum diretor para visualizar todos os filmes que ele fez
              while(input != "n"){
                cout << "\nDigite o codigo de um diretor para ver os filmes que ele produziu (ou digite n para pular): ";
                getline(cin, input);
                for(int i = 0; i < director->size(); i++){
                  if(director->at(i)->codigo == input){
                    cout << "\nFilmes do diretor " << director->at(i)->nome << ": \n\t";
                    cout << director->at(i)->filme << endl;
                     break;
                  }
                }
              }
            break;
            case 4: // Dados estatisticos por decada
              getDataByDecade(avl); // Chama funcao que exibe os dados estatisticos por decada
            break;
            case 5: // Quantidade de filmes por pais
              getTitlePerCountry(avl); // Chama funcao que exibe a quantidade de filmes por pais em ordem decrescente
            break;
          }
        }else{
          cout << "\nPor favor, insira algum valor na arvore primeiro!\n";
        }
      break;
      case 3: // Inserir Programa
        values = new string[15]; // Pega os valores para inserir
        getchar();
        cout << "Digite o ID: ";
        getline(cin, values[0]);
        cout << "Digite o Titulo: ";
        getline(cin, values[1]);
        cout << "Digite o Tipo: ";
        getline(cin, values[2]);
        cout << "Digite a Descricao: ";
        getline(cin, values[3]);
        cout << "Digite o Ano de Lancamento: ";
        getline(cin, values[4]);
        cout << "Digite a Certificacao de Idade: ";
        getline(cin, values[5]);
        cout << "Digite o Tempo de Duracao: ";
        getline(cin, values[6]);
        cout << "Digite os Generos: ";
        getline(cin, values[7]);
        cout << "Digite os Paises de Producao: ";
        getline(cin, values[8]);
        cout << "Digite a quantidade de Temporadas: ";
        getline(cin, values[9]);
        cout << "Digite o ID no IMDB: ";
        getline(cin, values[10]);
        cout << "Digite o Score no IMDB: ";
        getline(cin, values[11]);
        cout << "Digite a Quantidade de Votos no IMDB: ";
        getline(cin, values[12]);
        cout << "Digite a Popularidade no TMDB: ";
        getline(cin, values[13]);
        cout << "Digite a Pontuacao no TMDB: ";
        getline(cin, values[14]);
        step_bst = 0;
        step_avl = 0;
        avl->insert(values, &step_avl); // Insere os valores na avl
        bst->insert(values, &step_bst); // Insere os valores na bst
        cout << "Titulo inserido!\n\tQuantidade de passos BST: " << step_bst << "\n\tQuantidade de passos AVL: " << step_avl << endl; // Exibe quantidade de passos realizados para a inserçao
        delete[] values;
        values = nullptr;
      break;
      case 4: // Buscar Programa
        getchar();
        cout << "Digite o codigo do programa que voce deseja pesquisar: ";
        getline(cin, id);
        step_bst = 0;
        step_avl = 0;
        temp = avl->search(id, &step_avl); // Ja que as duas arvores estao sincronizadas, so eh necessario um dos dois valores para exibir os resultadosdo Programa na tela
        if(bst->search(id, &step_bst) != nullptr){ // Se o valor existir nas arvores, exibe os dados do programa
          temp->printValue();
        }else{
          cout << "\n\nValor nao encontrado!\n";
        }
        cout << "\nQuantidade de passos da checagem:\n\tAVL: " << step_avl << "\n\tBST: " << step_bst << endl;
        temp = nullptr;
      break;
      case 5: // Remover Programa
        getchar();
        cout << "\nDigite o id do item que deseja remover: ";
        getline(cin, id);
        step_bst = 0;
        step_avl = 0;
        if(bst->remove(id, &step_bst) && avl->remove(id, &step_avl)){ // Se o programa foi encontrado e removido, exibe mensagem de sucesso e a quantidade de passos necessarios
          cout << "\nExcluido com sucesso!";
          cout << "\nQuantidade de passos da para remocao:\n\tAVL: " << step_avl << "\n\tBST: " << step_bst << endl;
        }else{ // Caso contrario
          cout << "\nValor nao encontrado!" << endl; // Exibe mensagem informando que nao foi possivel
        }
      break;
      case 6: // Exibir altura das Arvores
        cout << "\nA altura da Arvore AVL eh: " << avl->getHeight(avl->getRoot()) << endl;
        cout << "A altura da Arvore BST eh: " << bst->getHeight(bst->getRoot()) << endl;
      break;
      case 7: // Salvar dados em arquivo
        getchar();
        cout << "Digite 1 se deseja salvar em um arquivo bkp padronizado (dados/titles_output.csv) ou digite o caminho para o novo arquivo: ";
        getline(cin, archivePath);
        if(archivePath == "1"){
          writeArchive(avl, "dados/titles_output.csv");
        }else{
          writeArchive(avl, archivePath);
        }
      break;
      case 8: // Encerrar Programa
        delete avl; // Limpar arvore AVL
        delete bst; // Limpar arvore BST
        delete finalQueue; // Limpar Fila
        delete credits; // Limpar Fila
        delete values; // Limpar vetor de valores
        values = nullptr;
        cout << "\nOBRIGADO POR UTILIZAR O PROGRAMA DE ANALISE/CIENCIA DE DADOS\n\n";
      break;
      default: // Caso o usuario selecione outros valores
        cout << "\n\nPor favor, Digite um valor valido!!\n\n";
      break;
    }
  }

}
