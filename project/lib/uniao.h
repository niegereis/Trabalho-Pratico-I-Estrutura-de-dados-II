#ifndef UNIAO_H
#define UNIAO_H

#include <string.h>

#include "acessoSequencialIndexado.h"
#include "arvoreB.h"
#include "arvoreBEstrela.h"
#include "arvoreBinaria.h"
#include "compartilhado.h"

void pesquisaMetodo(int, int, int, int, bool, Analise*, bool);
void imprimirArquivoBinario(FILE*, int);
void imprimeRegistro(Registro);
void imprimeAnalise(Analise);

#endif
