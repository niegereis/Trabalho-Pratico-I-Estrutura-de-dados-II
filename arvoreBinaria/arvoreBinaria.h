#ifndef ARVOREBINARIA_H
#define ARVOREBINARIA_H

#include <stdlib.h>
#include <stdbool.h>

#define sizeOfDado2 5000

typedef long Chave;

typedef struct {
    long dado1;
    char dado2[sizeOfDado2];
    Chave chave;
}Item;

typedef struct no {
    Item item;
    struct no* pEsq;
    struct no* pDir;
} No;

typedef No* Arvore ;

void Arvore_Inicia(No**);

bool ArvorePesquisa(No*, Chave, Item*);

bool ArvoreInsere(No**, Item);

void PreOrdem (No *p);

void PosOrdem (No *p);

void Central(No*);

#endif