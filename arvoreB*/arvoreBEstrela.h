#ifndef ARVORE_B_ESTRELA
#define ARVORE_B_ESTRELA

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define MM 4

typedef struct registro {
  int chave;
  long int dado1;
  char dado2[5000];
} Registro;

typedef enum { Interno, Externo } TipoDoNo;

typedef struct no* ArvoreBEstrela;

typedef struct no {
  TipoDoNo Pt;
  union {
    struct {
      int qtdChaves;
      int chaves[MM];
      ArvoreBEstrela apontadores[MM + 1];
    } Interno;
    struct {
      int qtdRegistros;
      Registro registros[MM];
    } Externo;
  } U;
} No;

ArvoreBEstrela arvoreCria();
bool arvoreInsere(ArvoreBEstrela* arvore, Registro registro);
bool arvorePesquisa(ArvoreBEstrela* arvore, int chave, Registro* registro);
bool arvoreImprime(ArvoreBEstrela* arvore);

#endif  // ARVORE_B_ESTRELA