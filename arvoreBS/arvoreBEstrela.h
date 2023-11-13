#ifndef ARVORE_B_ESTRELA
#define ARVORE_B_ESTRELA

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define M 1

typedef struct registro {
  int chave;
  long int dado1;
  char dado2[5000];
} Registro;

typedef enum { Interno, Externo } TipoDoNo;

typedef struct no* ArvoreBEstrela;

typedef struct no {
  TipoDoNo tipoNo;
  union {
    struct {
      int qtdChaves;
      int chaves[2 * M];
      struct no* apontadores[2 * M + 1];
    } Interno;
    struct {
      int qtdRegistros;
      Registro registros[2 * M];
    } Externo;
  } U;
} No;

ArvoreBEstrela arvoreCria();
bool arvoreInsere(ArvoreBEstrela* pNo, Registro registro);
bool arvorePesquisa(ArvoreBEstrela pNo, int chave, Registro* registro);
No* criaNo(TipoDoNo tipo);
void insereRegistroOrdenado(No* no, Registro registro, Registro* overflow);
void arvoreImprime(ArvoreBEstrela arvore);

#endif  // ARVORE_B_ESTRELA
