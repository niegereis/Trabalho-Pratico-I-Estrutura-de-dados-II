#ifndef ARVOREB_H
#define ARVORE_H
#include "../metodos.h"


#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <time.h>

#define sizeOfDado2 5000
#define MM 2
#define M 1

typedef long Chave;

typedef struct TipoRegistro {
    Chave Chave;
    long dado1;
    char dado2[sizeOfDado2];
} TipoRegistro;

typedef struct TipoPagina* TipoApontador;

typedef struct TipoPagina {
    short n;
    TipoRegistro r[MM];
    TipoApontador p[MM + 1]; // vetor de ponteiros que vai apontar para as proximas paginas
} TipoPagina;

void Pesquisa(TipoRegistro*, TipoApontador, Analise*);

void Imprime(TipoApontador);

void InsereNaPagina (TipoApontador, TipoRegistro, TipoApontador, Analise*);

void Ins (TipoRegistro, TipoApontador, short*, TipoRegistro*, TipoApontador*, Analise*);

void Insere(TipoRegistro, TipoApontador*, Analise*);

//void leArquivo(FILE*, int, int, TipoApontador*, Analise*);

void arvoreB(Analise*, FILE*, TipoRegistro *, int , int, TipoApontador);

void InicializaArvoreB (TipoApontador);

void LiberaPagina(TipoApontador);

void LiberaArvore(TipoApontador*);

#endif
