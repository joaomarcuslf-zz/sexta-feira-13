#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Library/sistema.h"
#include "Library/high_syntax.h"

head * cabeca=nil;
aluno * externo=nil;

int main() {
  void iniciar_head();
  void inserir_aluno();

  int choice;

  iniciar_head();
  while(true) {

    printf("\nDiga o que deseja fazer:");
    printf("\n  1 - Inserir aluno");
    if(externo!=nil) {
      printf("\n  2 - Inserir materia");
      printf("\n  3 - Inserir nota");
      printf("\n  4 - Mostrar todos");
    }
    printf("\n  0 - Sair");
    printf("\n>>");


    scanf("%i", &choice);

    if(choice==1) {
      inserir_aluno();
    }
    else if(choice==2 and externo!=nil) {

    }
    else if(choice==3 and externo!=nil) {

    }
    else if(choice==4 and externo!=nil) {

    }
    else if(choice==0) {
      break;
    }
    else {
      printf("\n\n     ERROR 001\nOpcao invalida ou funcao indisponivel no momento.\n\n");
    }
  }

  return 0;
}

void iniciar_head() {
  if(cabeca==nil) {
    cabeca=malloc(sizeof(head));
    cabeca->quant=0;
    cabeca->proximo=nil;
    cabeca->ultimo=nil;
  }
}

void inserir_aluno() {
  aluno * aux, * creat;
  char name[NAMESIZE];
  unsigned int mat, choice;

  aux=externo;

  printf("\nDiga o nome do aluno: ");
  scanf(" %[^\n]s%*c", name);
  printf("Diga os tres ultimos numeros da matricula: ");
  scanf("%i", &mat);

  if(externo==nil) {
    aux=malloc(sizeof(aluno));
    aux->proximo=(struct Sheader *) malloc(sizeof(head));
    aux->proximo=cabeca;
    aux->matricula=151047000 + (mat%1000);
    strcpy(aux->nome, name);
    aux->anterior=(struct Sheader *) malloc(sizeof(head));
    aux->anterior=cabeca;
    aux->turma=malloc(sizeof(materia));
    aux->turma=nil;
    cabeca->proximo=aux;
    cabeca->ultimo=aux;
    externo=aux;
  }
  else {
    aux=cabeca->ultimo;
    if(aux->anterior==cabeca) {
      creat=malloc(sizeof(aluno));
      aux->proximo=creat;
      creat->anterior=(struct Sheader *) malloc(sizeof(head));
      creat->anterior=aux;
      creat->proximo=(struct Sheader *) malloc(sizeof(head));
      creat->proximo=cabeca;
      cabeca->ultimo=creat;
      creat->turma=nil;
      creat->matricula=151047000 + (mat%1000);
      strcpy(creat->nome, name);
      aux->proximo=creat;
    }
    else {
      creat=malloc(sizeof(aluno));
      aux->proximo=creat;
      creat->anterior=(struct Saluno *) malloc(sizeof(aluno));
      creat->anterior=aux;
      creat->proximo=(struct Saluno *) malloc(sizeof(aluno));
      creat->proximo=cabeca;
      cabeca->ultimo=creat;
      creat->turma=nil;
      creat->matricula=151047000 + (mat%1000);
      strcpy(creat->nome, name);
      aux->proximo=creat;
    }
    aux=aux->proximo;
  }
  cabeca->quant+=1;
  printf("\nEspaco alocado: %p\nNome: %s\nMatricula: %i\n", aux, aux->nome, aux->matricula);
  printf("\nO aluno foi criado com sucesso deseja iniciar uma materia?\n1 - Sim\n0 - Nao\nResp: ");
  scanf("%d", &choice);

  switch (choice) {
    case 1:
      //iniciar_materia(aux);
    case 0:
      printf("\n");
    default:
      printf("\nObrigado por usar");
  }
}
