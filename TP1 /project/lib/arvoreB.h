#ifndef ARVOREB_H
#define ARVORE_H

#include "compartilhado.h"

typedef struct TipoPagina* TipoApontador;

typedef struct TipoPagina {
  short n;
  Registro r[2 * M];
  TipoApontador p[2 * M + 1];  // vetor de ponteiros que vai apontar para as
                               // proximas paginas
} TipoPagina;

bool Pesquisa(Registro*, TipoApontador, Analise*);

void Imprime(TipoApontador);

void InsereNaPagina(TipoApontador, Registro, TipoApontador, Analise*);

void Ins(Registro, TipoApontador, short*, Registro*, TipoApontador*, Analise*);

void Insere(Registro, TipoApontador*, Analise*);

void InicializaArvoreB(TipoApontador*);

void LiberaPagina(TipoApontador);

void LiberaArvore(TipoApontador*);

Registro arvoreB(Analise*, int, short*, FILE*, int);

#endif