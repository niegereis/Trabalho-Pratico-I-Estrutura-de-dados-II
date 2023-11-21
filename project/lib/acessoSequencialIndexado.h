#ifndef ACCESSO_SEQUENCIAL_INDEXADO_H
#define ACCESSO_SEQUENCIAL_INDEXADO_H

#include "compartilhado.h"

#define ITENS_PAGINA 6
#define QTD_ITENS_A_SER_LIDOS 2

typedef struct itemIndice {
  int posicao;
  int chave;
} ItemIndice;

bool criarPaginaIndicePrincipal(FILE* arquivo, Analise* analise,
                                int quantidade);
Registro acessoSequencialIndexado(Analise* analise, int chave, short* achou,
                                  FILE* arquivo, int quantidade);

#endif  // !ACCESSO_SEQUENCIAL_INDEXADO_H