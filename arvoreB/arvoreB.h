#ifndef ARVOREB_H
#define ARVORE_H

#include <stdlib.h>
#include <stdbool.h>

#define sizeOfDado2 5000
#define MM 2
#define M 1

typedef long TipoChave;

typedef struct TipoRegistro {
    TipoChave Chave;
    long dado1;
    char dado2[sizeOfDado2];
} TipoRegistro;

typedef struct TipoPagina* TipoApontador;

typedef struct TipoPagina {
    short n;
    TipoRegistro r[MM];
    TipoApontador p[MM + 1]; // vetor de ponteiros que vai apontar para as proximas paginas
} TipoPagina;

void Pesquisa(TipoRegistro*, TipoApontador);

void Imprime(TipoApontador);

void InsereNaPagina (TipoApontador, TipoRegistro, TipoApontador);

void Ins (TipoRegistro, TipoApontador, short*, TipoRegistro*, TipoApontador*);

void Insere(TipoRegistro, TipoApontador*);

#endif