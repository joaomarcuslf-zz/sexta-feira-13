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
  unsigned int mat;

  aux=externo;

  printf("\nDiga o nome do aluno: ");
  scanf(" %[^\n]s%*c", name);
  printf("Diga os tres ultimos numeros da matricula: ");
  scanf("%i", &mat);

  if(externo==nil) {
    externo=malloc(sizeof(aluno));
    externo->proximo=(struct Sheader *) malloc(sizeof(head));
    externo->proximo=cabeca;
    externo->matricula=151047000 + (mat%1000);
    strcpy(externo->nome, name);
    externo->anterior=(struct Sheader *) malloc(sizeof(head));
    externo->anterior=cabeca;
    externo->turma=malloc(sizeof(materia));
    externo->turma=nil;
    cabeca->proximo=externo;
    cabeca->ultimo=externo;
  }
  else {
    creat=malloc(sizeof(aluno));
    aux->proximo=creat;
    creat->anterior=aux;
    cabeca->ultimo=creat;
  }

  cabeca->quant+=1;
  printf("\nEspaco alocado: %p\nNome: %s\nMatricula: %i\n", externo, externo->nome, externo->matricula);
  printf("\nO aluno foi criado com sucesso deseja iniciar uma materia?\n1 - Sim\n2 - Nao\nResp: ");
  scanf("%i", &mat);

  switch (mat) {
    case 1:
      //iniciar_materia(aux);
    case 0:
      printf("\n");
    default:
      printf("\nObrigado por usar");
  }
}
