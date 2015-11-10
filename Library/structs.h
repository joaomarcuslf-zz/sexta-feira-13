#define NAMESIZE 50

typedef struct Smateria {
  char titulo[NAMESIZE];
  float AV[4]; //AV0 = Media
  struct Smateria * proximo;
} materia;

typedef struct Saluno {
  void * anterior;
  char nome[NAMESIZE];
  unsigned int matricula;
  void * proximo;
  struct Smateria * turma;
} aluno;

typedef struct Sheader {
  unsigned int quant;
  struct Saluno *proximo;
  struct Saluno *ultimo;
} head;
