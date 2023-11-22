
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../lib/acessoSequencialIndexado.h"

void converterArquivoIndexParaBinario() {
  FILE* arquivoBin = fopen("../arquivos/crescenteIndex.bin", "rb");
  if (!arquivoBin) {
    printf("Erro ao abrir arquivo binário!");
    exit(1);
  }
  FILE* arquivoTxt = fopen("../arquivos/crescenteIndex.txt", "w");
  if (!arquivoTxt) {
    printf("Erro ao abrir arquivo texto!");
    exit(1);
  }

  int qtd;
  printf("Digite a quantidade (-1 copia tudo): ");
  scanf("%d", &qtd);
  qtd = qtd == -1 ? INT_MAX : qtd;

  ItemIndice itemIndice;
  int i;
  while (i < qtd && fread(&itemIndice, sizeof(ItemIndice), 1, arquivoBin) > 0) {
    i++;
    fprintf(arquivoTxt, "POS: %d - CHAVE: %d\n", itemIndice.posicao,
            itemIndice.chave);
  }

  fclose(arquivoBin);
  fclose(arquivoTxt);
}
