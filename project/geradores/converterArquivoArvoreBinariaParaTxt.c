
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../lib/arvoreBinaria.h"

#define TAM 200

void main() {
  FILE* arquivoBin = fopen("../arquivos/arvoreBinaria.bin", "rb");
  FILE* arquivoTxt = fopen("../arquivos/arvoreBinaria.txt", "w");

  NoExt noAtual;
  while (fread(&noAtual, sizeof(NoExt), 1, arquivoBin) > 0) {
    fprintf(arquivoTxt, "Dir: %ld - Reg: %d - Esq: %ld\n", noAtual.pEsq,
            noAtual.registro.chave, noAtual.pDir);
  }

  fclose(arquivoBin);
  fclose(arquivoTxt);
}
