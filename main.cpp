/*
 *Trabalho de PAA de Arvore binario
 *Membros: Rafael Augusto Barros Ladeira de Oliveira
 *         João Pedro Moura de Assis Filho.
 *Link do Compilador: https://replit.com/join/sintvetsbt-joao211
 *Link Github: https://github.com/Jopei/AvBinariaOtima
 */
#include <bits/stdc++.h>
#include <iostream>
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
using namespace std;
// Area de Declarações
struct dict {
  struct dict *left, *right;
  char word[15], wordtr[20];
  int val = 0;
} *Root = NULL;
typedef struct dict dictionary;
// typedef struct dict dictionaryOtm;

struct Trunk
{
    Trunk *prev;
    string str;
 
    Trunk(Trunk *prev, string str)
    {
        this->prev = prev;
        this->str = str;
    }
};

int check(char[], char[]);
void insert(dictionary *);
void Search();
void view(dictionary *);
void insertionsort();
vector<dict *> v;
//----------------------------------------------------------//
/*Funções realizadas para arvore de busca binaria*/

// Função responsavel por chegar as palavras adcionadas no dicionario
int check(char a[], char b[]) {
  int i, j, c;
  for (i = 0, j = 0; a[i] != '\0' && b[j] != '\0'; i++, j++) {
    if (a[i] > b[j]) {
      c = 1;
      break;
    } else if (b[j] > a[i]) {
      c = -1;
      break;
    } else
      c = 0;
  }
  if (c == 1)
    return 1;
  else if (c == -1)
    return -1;
  else
    return 0;
}
// Metodo responsavel pela busca binaria usando a palavra em inglês como chave 
void search() {
  int flag = 0;
  dictionary *ptr;
  ptr = Root;
  char w[15];
  printf("\nDigite a palavra para obter a tradução\n");
  scanf("%s", w);
  while (ptr != NULL && flag == 0) {
    if (check(w, ptr->word) > 0)
      ptr = ptr->right;
    else if (check(w, ptr->word) < 0)
      ptr = ptr->left;
    else if (check(w, ptr->word) == 0) {
      flag = 1;
      ptr->val = ptr->val + 1;
      printf("\nTradução");
      printf("\n%s\n", ptr->wordtr);
    }
  }
  if (flag == 0)
    printf("\nPalavra não inserida\n");
}
// Metodo responsavel pela busca binaria usando a palavra em portugues como chave de procura
void search2() {
  int flag = 0;
  dictionary *ptr;
  ptr = Root;
  char w[15], wordtr[20];
  printf("\nDigite a tradução para obter a palavra\n");
  scanf("%s", w);
  while (ptr != NULL && flag == 0) {
    if (check(w, ptr->wordtr) > 0)
      ptr = ptr->right;
    else if (check(w, ptr->wordtr) < 0)
      ptr = ptr->left;
    else if (check(w, ptr->wordtr) == 0) {
      flag = 1;
      ptr->val = ptr->val + 1;
      printf("\nPalavra original");
      printf("\n%s\n", ptr->word);
    }
  }
  if (flag == 0)
    printf("\nPalavra não inserida\n");
}
// Metodo resposavel por inserir as structs no dicionario por meio de no.
void insert(dictionary *temp) {
  int flag = 0;
  dictionary *ptr, *par;
  ptr = Root;

  if (Root == NULL)
    Root = temp;
  else {
    while (ptr != NULL) {
      if (check(temp->word, ptr->word) > 0) {
        par = ptr;
        ptr = ptr->right;
      }

      else if (check(temp->word, ptr->word) < 0) {
        par = ptr;
        ptr = ptr->left;
      } else if (check(temp->word, ptr->word) == 0) {
        flag = 1;
        printf("\nPalavra já Adcionada!!\n");
        break;
      }
    }
    if (flag == 0 && ptr == NULL) {

      if (check(par->word, temp->word) == 1)
        par->left = temp;
      else if (check(par->word, temp->word) == -1)
        par->right = temp;
    }
  }
}
/*void insert2(dictionaryOtm *temp){
  int flag = 0;
  dictionaryOtm *ptr, *par;
  ptr = Root;

  if (Root == 0)
    Root = temp;
  else {
    while (ptr != NULL) {
      if (check(temp->word, ptr->word) > 0) {
        par = ptr;
        ptr = ptr->right;
      }

      else if (check(temp->word, ptr->word) < 0) {
        par = ptr;
        ptr = ptr->left;
      } else if (check(temp->word, ptr->word) == 0) {
        flag = 1;
        printf("\nPalavra já Adcionada!\n");
        break;
      }
    }
    if (flag == 0 && ptr == NULL) {

      if (check(par->word, temp->word) == 1)
        par->left = temp;
      else if (check(par->word, temp->word) == -1)
        par->right = temp;
    }
  }
}*/
// Metodo resposavel por visualizar os elementos presentes dentro da arvore
void view(dictionary *ptr) {
  if (Root == NULL) {
    printf("\nArvore Vazia\n");
  } else if (ptr != NULL) {

    view(ptr->left);
    printf("\n--------------------------------------------");
    printf("\nPalavra em inglês:%s\n", ptr->word);
    printf("\nTradução:%s\n", ptr->wordtr);
    printf("\nTaxa de procura:%i\n", ptr->val);
    printf("\n--------------------------------------------");
    view(ptr->right);
  }
}
// Helper function to print branches of the binary tree
void showTrunks(Trunk *p)
{
    if (p == nullptr) {
        return;
    }
 
    showTrunks(p->prev);
    cout << p->str;
}
 
void printTree(const dict *root, Trunk *prev, bool isLeft)
{
    if (root == nullptr) {
        return;
    }
 
    string prev_str = "    ";
    Trunk *trunk = new Trunk(prev, prev_str);
 
    printTree(root->right, trunk, true);
 
    if (!prev) {
        trunk->str = "———";
    }
    else if (isLeft)
    {
        trunk->str = ".———";
        prev_str = "   |";
    }
    else {
        trunk->str = "`———";
        prev->str = prev_str;
    }
 
    showTrunks(trunk);
    cout << " " << root->word << "(" << root->val << ")" << endl;
 
    if (prev) {
        prev->str = prev_str;
    }
    trunk->str = "   |";
 
    printTree(root->left, trunk, false);
}
//Metodo responsavel por exibir os niveis da arvore 
void printBT(const std::string &prefix, const dict *node, bool isLeft) {
  if (node != nullptr) {
    std::cout << prefix;
    std::cout << (isLeft ? "|--" : "L--");
    // print the value of the node
    std::cout << node->word << "("<<node->val<<")" << std::endl;
    // enter the next tree level - left and right branch
    printBT(prefix + (isLeft ? "|   " : "    "), node->right, true);
    printBT(prefix + (isLeft ? "|   " : "    "), node->left, false);
  }
}
void printBT(const dict *node) { printBT("", node, false); }
//----------------------------------------------------------//

dict *newDict(int data) {
  dict *tmp = new dict();
  tmp->val = data;
  tmp->left = tmp->right = NULL;
  return tmp;
}
void traverse(dict *node) {
  if (node == nullptr)
    return;
  traverse(node->left);
  dict *tmp = new dict();
  tmp = node;
  v.push_back(tmp);
  traverse(node->right);
}
void vectorPrint() {
  insertionsort();
  printf("\n----------------------\n");
  for (int i = v.size(); i > 0; i--) {
    printf("Palavra:%s\nFrequencia de Procura:%i", v[i - 1]->word, v[i - 1]->val);
    printf("\n----------------------\n");
  }
}
void insertionsort() {
  int i = 0, j = 0;
  dict *aux;
  for (i = 1; i < v.size(); i++) {
    aux = v[i];
    for (j = i; (j > 0) && (aux->val < v[j - 1]->val); j--) {
      v[j] = v[j - 1];
    }
    v[j] = aux;
  }
}

//----------------------------------------------------------//
int main(int argc, char const *argv[]) {
  setlocale(LC_ALL, "Portuguese");
  int ch, level = 1;
  dictionary *temp;
  while (ch != 6) {
    printf("\n-----------Menu-----------\n"
           "\n1-Inserir uma palavra em inglês e sua tradução"
           " na arvore"
           "\n2-Procure uma tradução para o português"
           "\n3-Procure uma tradução para o inglês"
           "\n4-Visualizar elementos da arvore"
           "\n5-Visualizar árvore"
           "\n6-Sair"
           "\n-------------------------\n");
    scanf("%d", &ch);
    switch (ch) {
    case 1:
      temp = (dictionary *)malloc(sizeof(dictionary));
      temp->left = NULL;
      temp->right = NULL;
      printf("\nInsira a palavra:\n");
      scanf("\n%s", temp->word);
      printf("\nInsira a tradução:\n");
      scanf("%s", temp->wordtr);
      insert(temp);
      traverse(temp);
      for (auto &x : v)
        cout << x->val << " ";
      break;
    case 2:
      search();
      break;
    case 3:
      search2();
      break;
    case 4:
      view(Root);
      break;
    case 5:
      printf("\n-----------Normal Binary Tree visualization-----------\n");
      printBT(Root);
      printf("\n-----------Binary Tree visualization Per Frequency-----------\n");
      printTree(Root, nullptr, false);
      break;
    case 6:
      printf("\n\nObrigado por usar o nosso programa!\nAutores: Rafael "
             "Oliveira e João Pedro \n\nTodos os direitos reservados 2022\n");
      insertionsort();
      exit(0);
    }
  }

  return 0;
}