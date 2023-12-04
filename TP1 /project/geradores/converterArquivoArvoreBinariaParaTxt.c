

#include "converterArquivoArvoreBinariaParaTxt.h"

void converterArquivoArvoreBinariaParaTxt() {
  FILE* arquivoBin = fopen("../arquivos/arvoreBinaria.bin", "rb");
  if (!arquivoBin) {
    printf("Erro ao abrir arquivo binário!");
    exit(1);
  }

  FILE* arquivoTxt = fopen("../arquivos/arvoreBinaria.txt", "w");
  if (!arquivoTxt) {
    printf("Erro ao abrir arquivo texto!");
    exit(1);
  }

  int qtd;
  printf("Digite a quantidade (-1 copia tudo): ");
  scanf("%d", &qtd);
  qtd = qtd == -1 ? INT_MAX : qtd;

  NoExt noAtual;
  int i;
  while (i < qtd && fread(&noAtual, sizeof(NoExt), 1, arquivoBin) > 0) {
    i++;
    fprintf(arquivoTxt, "Esq: %ld - Reg: %d - Dir: %ld\n", noAtual.pEsq,
            noAtual.registro.chave, noAtual.pDir);
  }

  fclose(arquivoBin);
  fclose(arquivoTxt);
}