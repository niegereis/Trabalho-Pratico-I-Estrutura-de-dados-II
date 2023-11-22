
#include <stdio.h>

#include "converterArquivoArvoreBinariaParaTxt.c"
#include "converterArquivoIndexBinariaParaTxt.c"
#include "converterBinarioDeRegistrosParaTxt.c"

int main() {
  printf("Digite a opção\n");
  printf("1 - Converter arquivo arvore binaria para txt\n");
  printf("2 - Converter arquivo index para txt\n");
  printf("3 - Converter arquivo de registros para txt\n");
  printf("Digite a opção: ");
  int option;
  scanf("%d", &option);

  if (option == 1) {
    converterArquivoArvoreBinariaParaTxt();
  } else if (option == 2) {
    converterArquivoIndexParaBinario();
  } else {
    converterBinarioDeRegistrosParaTxt();
  }
}