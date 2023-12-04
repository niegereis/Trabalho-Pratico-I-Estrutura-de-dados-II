#ifndef COMPARTILHADO_H
#define COMPARTILHADO_H

#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

# define M 2

typedef struct registro {
  int chave;
  long int dado1;
  char dado2[5000];
} Registro;

typedef struct analise {
  int comparacaoInsercao, comparacaoPesquisa;
  int transferenciaInsercao, transferenciaPesquisa;
  long long int tempoPesquisa, tempoInsere;
} Analise;

#endif