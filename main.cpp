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

typedef struct {
  string codigo;
  string nome;
  int qnt;
}Summarize;

typedef struct{
  string nome;
  int qnt;
}Country;

typedef struct{
  string codigo;
  string nome;
  string filme;
  int qnt;
}Director;

typedef struct{
  int decade;
  float min;
  float max;
  float standard;
  float media;
  int count;
}t_Decade;

// ********** END STRUCTS ********** //

// ********** FILL FUNCTIONS ********** //

template <typename T>
void fillVector(ProgramaNetflix *node, vector<T*> *list){
  if(node != nullptr){
    fillVector(node->getLeft(), list);
    list->push_back(node->getValues());
    fillVector(node->getRight(), list);
  }
}

void fillByType(ProgramaNetflix *node, vector<ProgramaNetflix*> *showList, vector<ProgramaNetflix*> *movieList){
  if(node != nullptr){
    fillByType(node->getLeft(), showList, movieList);
    string type = node->getType();
    float imdbScore = node->getImdbScore();
    if(type == "SHOW" && imdbScore > 0){
      showList->push_back(node);
    }else if(type == "MOVIE" && imdbScore > 0){
      movieList->push_back(node);
    }
    fillByType(node->getRight(), showList, movieList);
  }
}


void fillBst(BstTree *bst, AvlTree *avl, vector<string> *list){
  string *values;
  int length, step_bst, step_avl;
  step_bst = 0;
  step_avl = 0;
  for(int i = 0; i < list->size(); i++){
    values = strSplit(list->at(i), ';', &length);
    fillEmpty(values, &length);
    bst->insert(values, &step_bst);
    avl->insert(values, &step_avl);
  }
  cout << "Passos Bst: " << step_bst << " com " << bst->getQntNodes() << " nós inseridos" << endl << "Passos Avl: " << step_avl << " com " << avl->getQntNodes() << " nós inseridos" << endl;
}

void fillDecade(ProgramaNetflix *node, vector<t_Decade*> *listDecades, vector<string*> *list){
  if(node != nullptr){
    fillDecade(node->getLeft(), listDecades, list);

    bool verifier = false;
    t_Decade *temp;
    int tempDecade;
    string *values;
    values = node->getValues();
    if(stoi(values[4]) > 0){
      tempDecade = stoi(values[4])/10;
      verifier = false;
      for(int i = 0; i < listDecades->size(); i++){
        if(listDecades->at(i)->decade == tempDecade){
          listDecades->at(i)->media += stof(values[11]);
          listDecades->at(i)->count++;
          if(stof(values[11]) > 0 && listDecades->at(i)->min > stof(values[11])){
            listDecades->at(i)->min = stof(values[11]);
          }
          if(listDecades->at(i)->max < stof(values[11])){
            listDecades->at(i)->max = stof(values[11]);
          }
          verifier = true;
        }
      }
      if(!verifier){
        temp = new t_Decade[1];
        temp->count = 1;
        temp->decade = tempDecade;
        temp->max = stof(values[11]);
        temp->min = temp->max;
        temp->media = temp->min;
        temp->standard = 0;
        listDecades->push_back(temp);
      }
    }
    list->push_back(values);

    fillDecade(node->getRight(), listDecades, list);
  }
}

void fillCountry(ProgramaNetflix *node, vector<Country*> *listCountry){
  if(node != nullptr){
    fillCountry(node->getLeft(), listCountry);
    bool verifier = false;
    int length;
    string *values, *vetCountry;
    Country *temp;
    values = node->getValues();
    if(values[8] != "" && values[8] != "[]"){
      vetCountry = strSplit(clearChar(clearChar(clearChar(values[8], ' '), ']'), '['),',', &length);
      for(int i = 0; i < length; i++){
        verifier = false;
        for(int j = 0; j < listCountry->size(); j++){
          if(listCountry->at(j)->nome == vetCountry[i]){
            listCountry->at(j)->qnt++;
            verifier = true;
            break;
          }
        }
        if(!verifier){
          temp = new Country[1];
          temp->nome = vetCountry[i];
          temp->qnt = 1;
          listCountry->push_back(temp);
        }
      }
      temp = nullptr;
      delete[] values;
      delete[] vetCountry;
    }
    fillCountry(node->getRight(), listCountry);
  }
}

// ********** END FILL FUNCTIONS ********** //

// ********** SORT FUNCTIONS ********** //

template <typename T>
void sortStruct(vector<T*> **sample, int inferior, int superior){
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

void sortType(vector<ProgramaNetflix*> *list, int inferior, int superior){
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

void sortDecade(vector<t_Decade*> *sample, int inferior, int superior){
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

void getOutlyerByType(AvlTree *avl, int option){
  vector<ProgramaNetflix*> showList, movieList;
  vector<ProgramaNetflix*> outlyerList;
  int index;
  float media, imdbScore, iqr, q1, q3;
  fillByType(avl->getRoot(), &showList, &movieList);

  // TIPO SHOW // 
  sortType(&showList, 0, showList.size()-1);
  q3 = showList.at(floor(showList.size() * 0.75))->getImdbScore();
  q1 = showList.at(floor(showList.size() * 0.25))->getImdbScore();
  iqr = q3 - q1;
  cout << "\n\nTipo: SHOW";
  for(int i = 0; i < showList.size(); i++){
    if((option == 1 && showList.at(i)->getImdbScore() > (q3 + 1.5*iqr)) || (option == 0 && showList.at(i)->getImdbScore() < (q1 - 1.5*iqr))){
      cout << "\n\tID: " << showList.at(i)->getId() << " Titulo: " << showList.at(i)->getTitle() << " IMDB Score: " << showList.at(i)->getImdbScore();
    }
  }

  // TIPO MOVIE //
  sortType(&movieList, 0, movieList.size()-1);
  q3 = movieList.at(floor(movieList.size() * 0.75))->getImdbScore();
  q1 = movieList.at(floor(movieList.size() * 0.25))->getImdbScore();
  iqr = q3 - q1;
  cout << "\n\nTipo: MOVIE";
  for(int i = 0; i < movieList.size(); i++){
    if((option == 1 && movieList.at(i)->getImdbScore() > (q3 + 1.5*iqr)) || (option == 0 && movieList.at(i)->getImdbScore() < (q1 - 1.5*iqr))){
      cout << "\n\tID: " << movieList.at(i)->getId() << " Titulo: " << movieList.at(i)->getTitle() << " IMDB Score: " << movieList.at(i)->getImdbScore();
    }
  }

  showList.clear();
  movieList.clear();

}

// ********** MERGE FUNCTION ********** //


void mergeCredits(AvlTree *avl, Queue *credits, Queue *finalQueue, vector<Summarize*> *elenco){
  ProgramaNetflix *temp = nullptr;
  Summarize *elencoTemp;
  string *valuesTitles, *valuesCredits, *valuesfinal;
  bool verifier = false;
  valuesfinal = new string[19];
  int step = 0;
  while(credits->getSize() > 0){
    verifier = false;
    valuesCredits = credits->front();
    if(temp == nullptr || temp->getId() != valuesCredits[1]){
      temp = avl->search(valuesCredits[1], &step);
      if(temp != nullptr){
        valuesTitles = temp->getValues();
      }
    }
    if(temp != nullptr){
      for(int i = 0; i < 15; i++){
        valuesfinal[i] = valuesTitles[i];
      }
      // Como são só quatro valores e sempre a mesma casa. Foi optado por escrever assim ao invés de abrir um laço for com condicional para evitar o indice 1 (Que eh o indice do id que sera repitido se for inserido)
      valuesfinal[15] = valuesCredits[0];
      valuesfinal[16] = valuesCredits[2];
      valuesfinal[17] = valuesCredits[3];
      valuesfinal[18] = valuesCredits[4];
      finalQueue->push(valuesfinal);
      if(elenco != nullptr){
        if(!elenco->empty()){
            for(int i = elenco->size() - 1; i >= 0; i--){
              if(elenco->at(i)->codigo == valuesfinal[0]){
                elenco->at(i)->qnt++;
                verifier = true;
                break;
              }
            }
          }
          if(!verifier){
            elencoTemp = new Summarize[1];
            elencoTemp->codigo = valuesfinal[0];
            elencoTemp->nome = valuesfinal[1];
            elencoTemp->qnt = 1;
            elenco->push_back(elencoTemp);
          }
        }  
      }
        
    credits->pop();
  }
  if(elenco != nullptr){
    sortStruct(&elenco, 0, elenco->size()-1);
  }
}

// ********** END MERGE FUNCTION ********** //

// ********** READ & WRITE FUNCTIONS********** //


void readCredits(Queue *credits, string path){
  ifstream file;
  vector<string> list;
  string result, values, *input;
  int length;
  file.open(path);
  if(!file.fail()){
    getline(file, result, '\n'); // Pulando o cabeçalho
    int k = 0;
    while(file.peek() != EOF){
      values = "";
      for(int i = 0; i < 4; i++){
        getline(file, result, ';');
        values += result + ";";

      }
      getline(file, result, '\n');
      values += result;
      input = strSplit(values, ';', &length);
      credits->push(input);
      k++;
    }
  }
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
    bst->insertColumns(strSplit(result, ';', &length));
    avl->insertColumns(strSplit(result, ';', &length));
    int k = 0;
    while(file.peek() != EOF){
      values = "";
      for(int i = 0; i < 14; i++){
        file.get(sep);
        if(sep != ';'){
          getline(file, result, ';');
          values += sep + result + ";";
        }else{
          values += ";";
        }
      }
      getline(file, result, '\n');
      values += result;
      lista.push_back(values);
      k++;
    }
  }
  fillBst(bst, avl, &lista);
  lista.clear();
}

void writeArchive(AvlTree *avl, string path){
  ofstream fout(path);
  vector<string*> list;
  string *values = avl->getColumn()->getValues();
  fillVector(avl->getRoot(), &list);
  for(int i = 0; i < 14; i++){
    fout << values[i] << ";";
  }
  fout << values[14] << "\n";
  
  for(int i = 0; i < list.size(); i++){
    for(int j = 0; j < 14; j++){
      fout << list.at(i)[j] << ";";
    }
    fout << list.at(i)[14] << "\n";
  }

  // delete values;
  values = nullptr;
  
}

void writeMerged(Queue *lista, string path, string *columns){
  ofstream fout(path);
  string *values;
  // Gravando colunas
  for(int i = 0; i < 15; i++){
    fout << columns[i] << ";";
  }
  fout << "actor_id;name;character;role"<<endl;

  while(lista->getSize() > 0){
    values = lista->front();
    for(int i = 0; i < 18; i++){
      fout << values[i] << ";";
    }
    fout << values[18] << endl;
    lista->pop();
  }
}

// ********** END READ & WRITE FUNCTIONS ********** //

// ********** ANALYTICAL FUNCTIONS ********** //

void getDirectorMovie(AvlTree *avl, vector<Director*> *director){
  bool verifier = false;
  string *values;
  // vector<Director*> *director = new vector<Director*>();
  Director *temp;
  Queue *credits = new Queue(5);
  Queue *finalCredits = new Queue(19);
  readCredits(credits, "dados/credits.csv");
  mergeCredits(avl, credits, finalCredits, nullptr);
  delete credits;
  while(finalCredits->getSize() > 0){
    verifier = false;
    values = finalCredits->front();
    if(values[18] == "DIRECTOR"){
      if(director->size() > 0){
        for(int i = 0; i < director->size(); i++){
          if(director->at(i)->codigo == values[15]){
            director->at(i)->qnt++;
            director->at(i)->filme += "\n\t" + values[1];
            verifier = true;
            break;
          }
        }
      }
      
      if(!verifier){
        temp = new Director[1];
        temp->codigo = values[15];
        temp->nome = values[16];
        temp->filme = values[1];
        temp->qnt = 1;
        director->push_back(temp);
      }
    }
    finalCredits->pop();
  }
  sortStruct(&director, 0, director->size()-1);
}

void getDataByDecade(AvlTree *avl){
  float tempStandard;
  vector<string*> *list = new vector<string*>();
  vector<t_Decade*> *listDecades = new vector<t_Decade*>();
  fillDecade(avl->getRoot(), listDecades, list);
  for(int i = 0; i < listDecades->size(); i++){
    tempStandard = 0;
    listDecades->at(i)->media /= listDecades->at(i)->count;
    for(int j = 0; j < list->size(); j++){
      if(stoi(list->at(j)[4])/10 == listDecades->at(i)->decade){
        tempStandard += pow(stof(list->at(j)[11]) - listDecades->at(i)->media, 2);
      }
    }
    listDecades->at(i)->standard = sqrt(tempStandard / listDecades->at(i)->count);
  }
  sortDecade(listDecades, 0, listDecades->size()-1);
  for(int i = 0; i < listDecades->size(); i++){
    if(listDecades->at(i)->media > 0){
        std::cout << std::fixed << std::setprecision(2);
        cout << "\n\nDecada: " << listDecades->at(i)->decade << "0\n\tMedia: " << listDecades->at(i)->media << "\n\tMenor Valor: " << listDecades->at(i)->min;
        cout << "\n\tMaior Valor: " << listDecades->at(i)->max << "\n\tDesvio Padrao: " << listDecades->at(i)->standard; 
      }
  }

  listDecades->clear();
  list->clear();
  delete listDecades;
  delete list;

}


void getTitlePerCountry(AvlTree *avl){
  vector<Country*> *listCountry = new vector<Country*>();
  fillCountry(avl->getRoot(), listCountry);
  sortStruct(&listCountry, 0, listCountry->size()-1);

  for(int i = 0; i < listCountry->size(); i++){
    cout << "Nome: " << listCountry->at(i)->nome << " Quantidade: " << listCountry->at(i)->qnt << endl;
  }
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
  Queue *credits, *finalQueue;
  vector<Summarize*> elenco;
  credits = new Queue(5);
  finalQueue = new Queue(19);
  int option = -1, step_bst, step_avl; // Variavel que armazena a opcao do usuario
  string input, archivePath, id, *values = nullptr; // Variavel que contem o caminho do arquivo para ler

  cout << "Bem vindo ao programa de Analise/Ciencia de dados com Arvores BST e AVL\n\n";
  cout << "Desenvolvedores:\n\tGustavo Teixeira dos Santos  TIA 32197020\n\tCleverson Pereira da Silva  TIA 32198531\n\tVictor Junqueira  TIA 42123712\n\tFelipe Nakandakari  TIA 42104701\n\tPedro Catarino  TIA 42105951\n\n";
  
  while(option != 8){
    cout << "\n\nO que deseja:\n\t1 - Ler dados de arquivo\n\t2 - Opcoes de Analise\n\t3 - Inserir Programa\n\t4 - Buscar Programa\n\t5 - Remover Programa\n\t6 - Exibir a Altura das Árvores\n\t7 - Salvar dados em arquivo\n\t8 - Encerrar Programa\nEscolha: ";
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
          cout << "Qual analise dejesa:\n\t1 - 20 filmes com os maiores elencos\n\t2 - Titulos com o IMDB Score acima do comum\n\t3 - Filmes por Diretor (para diretores com mais de um filme) ";
          cout << "\n\t4 - Dados estatísticos sobre as decadas\n\t5 - Quantidade de filmes por pais\nEscolha: ";
          cin >> option;
          switch(option){
            case 1:
              readCredits(credits, "dados/credits.csv");
              mergeCredits(avl, credits, finalQueue, &elenco);
              cout << "\nRelacao de elenco por titulo em ordem crescente:\n\n";
              cout << "Id titulo | Nome titulo | Quantidade pessoas no Elenco\n";
              for(int i = 0; i < 20; i++){
                cout << "\t" << elenco.at(i)->codigo << "|" << elenco.at(i)->nome << "|" << elenco.at(i)->qnt << endl;
              }

              cout << "\n\nUma base consolidada foi gerada a partir do cruzamento de titulos e creditos. Deseja salvar? (1 para sim e 0 para nao): ";
              cin >> option;
              if(option == 1){
                getchar();
                cout << "Digite o caminho para onde deseja salvar o arquivo: ";
                getline(cin, input);
                writeMerged(finalQueue, input, avl->getColumn()->getValues());
              }
              elenco.clear();

            break;
            case 2:
              cout << "Digite 1 para acima do comum e 0 para abaixo do comum: ";
              cin >> option;
              getOutlyerByType(avl, option);
            break;
            case 3:
              getDirectorMovie(avl, director);
              cout << "Codigo | Nome | Quantidade\n";
              for(int i = 0; i < director->size(); i++){
                if(director->at(i)->qnt > 1){
                  cout << director->at(i)->codigo << " | " << director->at(i)->nome << " | " << director->at(i)->qnt << endl;
                }
              }
              getchar();
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
            case 4:
              getDataByDecade(avl);
            break;
            case 5:
              getTitlePerCountry(avl);
            break;
          }
        }else{
          cout << "\nPor favor, insira algum valor na arvore primeiro!\n";
        }
      break;
      case 3: // Inserir Programa
        values = new string[15];
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
        avl->insert(values, &step_avl);
        bst->insert(values, &step_bst);
        cout << "Titulo inserido!\n\tQuantidade de passos BST: " << step_bst << "\n\tQuantidade de passos AVL: " << step_avl << endl;
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
        if(bst->search(id, &step_bst) != nullptr){
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
        if(bst->remove(id, &step_bst) && avl->remove(id, &step_avl)){
          cout << "\nExcluido com sucesso!";
          cout << "\nQuantidade de passos da para remocao:\n\tAVL: " << step_avl << "\n\tBST: " << step_bst << endl;
        }else{
          cout << "\nValor nao encontrado!" << endl;
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
      break;
      default: // Caso o usuário selecione outros valores
        cout << "\n\nPor favor, Digite um valor valido!!\n\n";
      break;
    }
  }

}
