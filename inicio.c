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
  void inserir_materia(aluno * escolhido);
  struct Saluno * buscar();

  int choice;
  aluno * buscador;

  iniciar_head();
  while(true) {

    printf("\nDiga o que deseja fazer:");
    printf("\n  1 - Inserir aluno");
    if(externo!=nil) {
      printf("\n  2 - Inserir materia");
      printf("\n  3 - Inserir nota");
      printf("\n  4 - Mostrar todos");
      printf("\n  5 - Encontrar");
    }
    printf("\n  0 - Sair");
    printf("\n>>");


    scanf("%i", &choice);

    if(choice==1) {
      inserir_aluno();
    }
    else if(choice==2 and externo!=nil) {
      buscador = buscar();
      inserir_materia(buscador);
    }
    else if(choice==3 and externo!=nil) {
      buscador = buscar();
      inserir_materia(buscador);
    }
    else if(choice==4 and externo!=nil) {

    }
    else if(choice==5 and externo!=nil) {
      buscador = buscar();
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
  mat = 151047000 + (mat%1000);

  if(externo==nil) {
    aux=(struct Saluno *) malloc(sizeof(aluno));
    aux->proximo=(struct Sheader *) malloc(sizeof(head));
    aux->proximo=cabeca;
    aux->matricula=mat;
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
    aux=cabeca->proximo;

    while(aux!=cabeca) {
      if(mat == aux->matricula) {
        printf("Matricula ja existente diga uma nova: ");
        scanf("%i", &mat);
        mat = 151047000 + (mat%1000);
      }
      else {
        aux=aux->proximo;
      }
    }

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
      creat->matricula=mat;
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
      creat->matricula=mat;
      strcpy(creat->nome, name);
      aux->proximo=creat;
    }
    aux=aux->proximo;
  }
  cabeca->quant+=1;

  aux=cabeca->proximo;
  while(aux->proximo!=cabeca) {
    printf("\nEspaco alocado: %p - Matricula: %i - Nome: %s", aux, aux->matricula, aux->nome);
    aux=aux->proximo;
  }
  aux=cabeca->ultimo;

  printf("\n\nEspaco alocado: %p\nNome: %s\nMatricula: %i\n", aux, aux->nome, aux->matricula);
  printf("\nO aluno foi criado com sucesso deseja iniciar uma materia?\n1 - Sim\n0 - Nao\nResp: ");
  scanf("%d", &choice);

  switch (choice) {
    case 1:
      inserir_aluno(aux);
    case 0:
      printf("\n");
    default:
      printf("\nObrigado por usar");
  }
}

struct Saluno * buscar() {
  int mat, choice;
  char nome[NAMESIZE];
  aluno * aux;

  printf("\nDiga os três ultimos numeros da matricula: ");
  scanf("%d", &mat);

  mat = 151047000 + (mat%1000);
  aux=externo;

  while(aux!=cabeca) {
    if(mat==aux->matricula) {
      printf("\nEncontrado em:\n   Espaco alocado: %p - Matricula: %i - Nome: %s\n", aux, aux->matricula, aux->nome);
      return aux;
    }
    aux=aux->proximo;
  }

  printf("\nNao encontrado, deseja inserir?\n1 - Sim\n0 - Nao\nResp: ");
  scanf("%d", &choice);

  if(choice==1) {
    inserir_aluno();
  }
  return nil;
}

void inserir_materia(aluno * escolhido) {

}
