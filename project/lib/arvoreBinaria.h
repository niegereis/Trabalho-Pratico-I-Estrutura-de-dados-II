#ifndef ARVOREBINARIA_H
#define ARVOREBINARIA_H

#include "compartilhado.h"

typedef struct no {
    Registro item;
    struct no* pEsq;
    struct no* pDir;
} No;

typedef No* Arvore ;

Arvore Arvore_Inicia();

bool ArvorePesquisa(No*, int, Registro*, Analise*);

bool ArvoreInsere(No**, Registro, Analise*);

// void PreOrdem (No *p);

// void PosOrdem (No *p);

// void Central(No*);

bool leArquivoBin(FILE*, int, Arvore, Analise*); 

Registro arvoreBinaria(Analise*, int, short*, FILE*, int);


#endif