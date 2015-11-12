#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define true 1
#define false 0
#define NAMESIZE 50

typedef struct Smateria {
  char titulo[NAMESIZE]; // Titulo da materia
  char status; // Status da materia
  float notas[4]; // notas[0]= (notas[1] + notas[2])/2
  struct Smateria * proximo; // Direcional para baixo, so aponta para materias
} materia;

typedef struct Saluno {
  char nome[NAMESIZE]; // Nome do aluno
  unsigned int matricula; // Matricula
  //Direcionais da lista
  void * anterior; // Aponta ou para cabeca ou para o aluno
  void * proximo; // Aponta ou para cabeca ou para o aluno
  struct Smateria * turma; // Aponta para materia, nulo
} aluno;

typedef struct Sheader {
  unsigned int quantidade; // Quantidade de alunos
  unsigned int maiorMatricula; // Maior matricula
  unsigned int menorMatricula; // Menor matricula
  struct Saluno *proximo; // Aponta para o proximo aluno
  struct Saluno *anterior; // Aponta para o anterior aluno
} head;

head * cabeca=NULL; // Cabeca da lista
aluno * lista=NULL; // Lista total

int main() {

  void iniciar_head(); // Pronta
  void inserir_aluno(); // Pronta
  void deletar_aluno(aluno * escolhido); // Pronta
  void inserir_materia(aluno * escolhido); // Pronta
  void deletar_materia(aluno * escolhido); // Pronta
  void mostrar_todos(); // Pronta
  struct Saluno * buscar(); // Pronta

  int choice;
  aluno * buscador;

  iniciar_head();

  while(true) {

    printf("\nDiga o que deseja fazer:");
    printf("\n  1 - Inserir aluno");
    if(lista!=NULL) {
      printf("\n  2 - Deletar aluno");
      printf("\n  3 - Inserir materia");
      printf("\n  4 - Deletar materia");
      printf("\n  5 - Mostrar todos");
      printf("\n  6 - Encontrar");
    }
    printf("\n  0 - Sair");
    printf("\n>>");


    scanf("%i", &choice);

    if(choice==1) {
      inserir_aluno();
    }
    else if(choice==2 && lista!=NULL) {
      buscador = buscar();
      deletar_aluno(buscador);
    }
    else if(choice==3 && lista!=NULL) {
      buscador = buscar();
      inserir_materia(buscador);
    }
    else if(choice==4 && lista!=NULL) {
      buscador = buscar();
      deletar_materia(buscador);
    }
    else if(choice==5 && lista!=NULL) {
      mostrar_todos();
    }
    else if(choice==6 && lista!=NULL) {
      buscador = buscar();
    }
    else if(choice==0) {
      break;
    }
    else {
      printf("\n\n     ERRO!\nOpcao invalida ou funcao indisponivel no momento.\n\n");
    }
  }
}

//                   FUNCOES

void iniciar_head() {
    cabeca=malloc(sizeof(head));
    cabeca->quantidade=0;
    cabeca->proximo=NULL;
    cabeca->anterior=NULL;
    cabeca->maiorMatricula=0;
    cabeca->menorMatricula=151048000;
}

void inserir_aluno() {
  aluno * aux, * criador, * seguraLista;
  char name[NAMESIZE];
  unsigned int mat;

  printf("\n\nInserindo aluno:");
  printf("\nDiga o nome do aluno: ");
  scanf(" %[^\n]s%*c", name);
  printf("Diga os tres ultimos numeros da matricula: ");
  scanf("%i", &mat);
  mat = 151047000 + (mat%1000);

  if(lista==NULL) {
    aux=(struct Saluno *) malloc(sizeof(aluno));
    aux->proximo=(struct Sheader *) malloc(sizeof(head));
    aux->proximo=cabeca;
    aux->matricula=mat;
    strcpy(aux->nome, name);
    aux->anterior=(struct Sheader *) malloc(sizeof(head));
    aux->anterior=cabeca;
    aux->turma=malloc(sizeof(materia));
    aux->turma=NULL;
    cabeca->proximo=aux;
    cabeca->anterior=aux;
    cabeca->menorMatricula=mat;
    cabeca->maiorMatricula=mat;
    cabeca->quantidade+=1;
    lista=aux;
  }
  else {
    aux = lista;

    criador = malloc(sizeof(aluno));
    strcpy(criador->nome, name);
    while(aux!=cabeca) {
      if(aux->matricula == mat) {
        printf("Matricula ja existente diga uma nova: ");
        scanf("%i", &mat);
        mat = 151047000 + (mat%1000);
      }
      else {
        aux=aux->proximo;
      }
    }
    criador->matricula = mat;

    if(aux->proximo == cabeca) {
      if(aux->matricula  < criador->matricula) {
        criador->anterior = aux;
        aux->proximo = criador;
        criador->proximo = cabeca;
        cabeca->anterior = criador;
        criador->turma=NULL;
        cabeca->maiorMatricula=mat;
        cabeca->quantidade+=1;
      }
      else {
        criador->proximo = aux;
        aux->anterior = criador;
        criador->anterior = cabeca;
        cabeca->proximo = criador;
        criador->turma=NULL;
        cabeca->menorMatricula=mat;
        cabeca->quantidade+=1;
        lista = criador;
      }
    }

    else {
        aux = cabeca->anterior;
        if(aux->matricula  < criador->matricula) {
          criador->anterior = aux;
          aux->proximo = criador;
          criador->proximo = cabeca;
          cabeca->anterior = criador;
          criador->turma=NULL;
          cabeca->maiorMatricula=mat;
          cabeca->quantidade+=1;
          lista = cabeca->proximo;
        }
        else {
          while(aux->anterior != cabeca && aux->matricula  > criador->matricula) {
            aux = aux->anterior;
          }

          seguraLista = aux;

          if(aux->anterior == cabeca && aux->matricula  > criador->matricula) {
            criador->proximo = seguraLista;
            criador->anterior=cabeca;
            seguraLista->anterior = criador;
            cabeca->proximo=criador;
            criador->turma=NULL;
          }
          else {
            aux = aux->anterior;
            criador->proximo = seguraLista;
            criador->anterior=aux;
            seguraLista->anterior = criador;
            aux->proximo=criador;
            criador->turma=NULL;
          }
          cabeca->quantidade+=1;
          lista = cabeca->proximo;
      }
    }
  }
}

void deletar_aluno(aluno * escolhido) {
  aluno * aux, * seguraLista;
  if(escolhido == NULL) {
    printf("\nNao ha nada nesse endereco");
  }
  else {
    printf("\n-=Liberando espaco=-\n\n");

    aux = escolhido->anterior;
    seguraLista = escolhido->proximo;

    if(aux == seguraLista) { // Quer dizer que esse era o unico integrante da lista
      iniciar_head();
      lista = NULL;
      return;
    }

    if(lista == escolhido) {
      lista=lista->proximo;
    }

    aux->proximo=seguraLista;
    seguraLista->anterior=aux;

    escolhido->proximo=NULL;
    escolhido->anterior=NULL;

    free(escolhido);
    escolhido=NULL;

    cabeca->quantidade-=1;

  }
}

void inserir_materia(aluno * escolhido) {
  int choice, iCont;
  float nota;
  char name[NAMESIZE];
  struct Smateria * aux;
	if(escolhido == NULL) {
		printf("\nNao encontrado, deseja inserir?\n1 - Sim\n0 - Nao\nResp: ");
  		scanf("%d", &choice);

  		if(choice==1) {
    		inserir_aluno();
  		}
	}
  else {
    if(escolhido->turma == NULL) {
      escolhido->turma=malloc(sizeof(materia));
    }
    aux=escolhido->turma;

    while(aux->proximo!=NULL) {
      aux = aux->proximo;
    }
    printf("\nDiga o nome da materia: ");
    scanf(" %[^\n]s%*c", name);

    strcpy(aux->titulo, name);
    aux->notas[0]=0;
    for(iCont=1; iCont<3; iCont+=1) {
      printf("\nDiga a sua nota da AV%d: ", iCont);
      scanf("%f", &nota);
      aux->notas[iCont]=nota;
      aux->notas[0]+=nota;
    }

    aux->notas[0]=aux->notas[0]/2;

    if(aux->notas[0]=<6) {
      printf("\nDiga a sua nota da AVF: ");
      scanf("%f", &aux->notas[3]);
      aux->notas[0] = (aux->notas[0] + aux->notas[3])/2;
    }

    if(aux->notas[0]>=6) {
      aux->status = 'A';
    }
    else {
      aux->status = 'R';
    }

    aux->proximo=NULL;
    printf("\nEspaco alocado: %p - Nota: %.2f - Status: %c - Nome: %s", aux, aux->notas[0], aux->status, aux->titulo);
  }
}

void deletar_materia(aluno * escolhido) {
  char name[NAMESIZE];
  struct Smateria * aux, * seguraMateria, * ant;

  if(escolhido->turma==NULL) {
    printf("\nEsse aluno ainda nao possui materias matriculado");
  }
  else {
    printf("\nDiga o nome da materia que deseja ");
    scanf(" %[^\n]s%*c", name);
    while(aux!=NULL && (strcmp(name, aux->titulo) != 0)) {
      ant=aux;
      aux=aux->proximo;
    }

    if(aux!=NULL) {
      if(escolhido->turma == aux) {
        seguraMateria=aux->proximo;
        escolhido->turma = seguraMateria;
        free(aux);
        aux=NULL;
      }
      else {
        seguraMateria=aux->proximo;
        ant->proximo =seguraMateria;
        free(aux);
        aux=NULL;
      }
    }
  }
  return;
}

void mostrar_todos() {
  struct Saluno * auxAluno;
  struct Smateria * auxMateria;
  if(lista!=NULL) {
    printf("\nHEAD");
    printf("\n    Espaco alocado: %p - Quantidade: %i", cabeca, cabeca->quantidade);
    printf("\n  Alunos");
    auxAluno=lista;
    while(auxAluno!=cabeca) {
      printf("\n    Espaco alocado: %p - Matricula: %i - Nome: %s", auxAluno, auxAluno->matricula, auxAluno->nome);
      if(auxAluno->turma!=NULL) {
        auxMateria=auxAluno->turma;
        printf("\n      Materias:");
        while(auxMateria!=NULL) {
          printf("\n        Espaco alocado: %p - Nota: %.2f - Status: %c - Nome: %s", auxMateria, auxMateria->notas[0], auxMateria->status, auxMateria->titulo);
          auxMateria=auxMateria->proximo;
        }
      }
      auxAluno=auxAluno->proximo;
    }
  }
  else {
    printf("\nA Lista esta vazia!");
  }
}

struct Saluno * buscar() {
  int mat, choice;
  char nome[NAMESIZE];
  aluno * aux;

  printf("\n\nBuscando:");
  printf("\nDiga os três ultimos numeros da matricula: ");
  scanf("%d", &mat);

  mat = 151047000 + (mat%1000);
  aux=lista;

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
  return NULL;
}
