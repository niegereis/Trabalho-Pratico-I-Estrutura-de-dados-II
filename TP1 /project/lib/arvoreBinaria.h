#ifndef ARVOREBINARIA_H
#define ARVOREBINARIA_H

#include <stdio.h>
#include <stdlib.h>

#include "./compartilhado.h"

#define sizeOfDado2 5000

typedef struct {
  Registro registro;
  long pEsq;
  long pDir;
} NoExt;

typedef NoExt* Arvore;

bool ArvoreBinariaPesquisa(FILE*, long, Registro*, Analise*);
void ArvoreBinariaCria(FILE*, FILE*, int, Analise*);
Registro arvoreBinaria(Analise*, int, short*, FILE*, int);

#endif