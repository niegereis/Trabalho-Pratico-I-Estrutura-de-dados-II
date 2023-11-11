#ifndef ACCESSO_SEQUENCIAL_INDEXADO_H
#define ACCESSO_SEQUENCIAL_INDEXADO_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define ITENS_PAGINA 3
#define QTD_ITENS_A_SER_LIDOS 3

typedef struct itemIndice {
  int posicao;
  int chave;
} ItemIndice;

typedef struct registro {
  int chave;
  long int dado1;
  char dado2[5000];
} Registro;

bool criarPaginaIndicePrincipal();

#endif  // !ACCESSO_SEQUENCIAL_INDEXADO_H