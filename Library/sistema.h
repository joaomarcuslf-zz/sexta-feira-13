#include <stdlib.h>
#include <string.h>
#include "high_syntax.h"
#include "structs.h"


void iniciar_head();
void inserir_aluno();
void inserir_materia(aluno * escolhido);
void mostrar_todos();
struct Saluno * buscar();


head * cabeca=nil;
aluno * externo=nil;


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
      inserir_materia(aux);
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
	int choice, iCont;
  float nota;
  char name[NAMESIZE];
  struct Smateria * aux;
	if(escolhido == nil) {
		printf("\nNao encontrado, deseja inserir?\n1 - Sim\n0 - Nao\nResp: ");
  		scanf("%d", &choice);

  		if(choice==1) {
    		inserir_aluno();
  		}
	}
  else {
    if(escolhido->turma == nil) {
      escolhido->turma=malloc(sizeof(materia));
    }
    aux=escolhido->turma;

    while(aux->proximo!=nil) {
      aux = aux->proximo;
    }
    printf("\nDiga o nome da materia: ");
    scanf(" %[^\n]s%*c", name);

    strcpy(aux->titulo, name);
    aux->AV[0]=0;
    for(iCont=1; iCont<4; iCont+=1) {
      printf("\nDiga a sua %i nota: ", iCont);
      scanf("%f", &nota);
      aux->AV[iCont]=nota;
      aux->AV[0]+=nota;
    }
    aux->AV[0]=aux->AV[0]/3;
    aux->proximo=nil;
    printf("\nEspaco alocado: %p - Nota: %.2f - Nome: %s", aux, aux->AV[0], aux->titulo);
  }
}

void mostrar_todos() {
  struct Saluno * auxAluno;
  struct Smateria * auxMateria;
  printf("\nHEAD");
  printf("\n    Espaco alocado: %p - Quantidade: %i", cabeca, cabeca->quant);
  printf("\n  Alunos");
  auxAluno=externo;
  while(auxAluno!=cabeca) {
    printf("\n      Espaco alocado: %p - Matricula: %i - Nome: %s", auxAluno, auxAluno->matricula, auxAluno->nome);
    if(auxAluno->turma!=nil) {
      auxMateria=auxAluno->turma;
      printf("\n        Materias:");
      while(auxMateria!=nil) {
        printf("\n          Espaco alocado: %p - Nota: %.2f - Nome: %s", auxMateria, auxMateria->AV[0], auxMateria->titulo);
        auxMateria=auxMateria->proximo;
      }
    }
    auxAluno=auxAluno->proximo;
  }

}
