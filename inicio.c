#include <stdio.h>
#include "Library/sistema.h"

int main() {

  int choice;
  aluno * buscador;

  iniciar_head();
  while(true) {

    printf("\nDiga o que deseja fazer:");
    printf("\n  1 - Inserir aluno");
    if(externo!=nil) {
      printf("\n  2 - Inserir materia");
      printf("\n  3 - Mostrar todos");
      printf("\n  4 - Encontrar");
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
      mostrar_todos();
    }
    else if(choice==4 and externo!=nil) {
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
