#ifndef ARVORE_B_ESTRELA
#define ARVORE_B_ESTRELA

#include "compartilhado.h"

#define M 1

typedef enum { Interno, Externo } TipoDoNo;

typedef struct noU* ArvoreBEstrela;

typedef struct noU {
  TipoDoNo tipoNo;
  union {
    struct {
      int qtdChaves;
      int chaves[2 * M];
      struct noU* apontadores[2 * M + 1];
    } Interno;
    struct {
      int qtdRegistros;
      Registro registros[2 * M];
    } Externo;
  } U;
} NoU;

ArvoreBEstrela arvoreCria();
bool arvoreInsere(ArvoreBEstrela*, Registro, Analise*);
bool arvorePesquisa(ArvoreBEstrela, int, Registro*);
NoU* criaNo(TipoDoNo tipo);
void insereRegistroOrdenado(NoU*, Registro, Registro*);
void arvoreImprime(ArvoreBEstrela);
Registro arvoreBEstrela(Analise*, int, short*, FILE*, int);
bool pesquisaNoInterno(ArvoreBEstrela, int, Analise*, Registro*);
Registro arvoreBEstrela(Analise*, int, short*, FILE*, int);

#endif  // ARVORE_B_ESTRELA
