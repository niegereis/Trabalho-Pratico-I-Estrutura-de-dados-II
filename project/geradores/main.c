
#include <dirent.h>
#include <stdio.h>
#include <sys/stat.h>

#include "converterArquivoArvoreBinariaParaTxt.h"
#include "converterArquivoIndexBinariaParaTxt.h"
#include "converterBinarioDeRegistrosParaTxt.h"
#include "geraleatorio.h"
#include "gercrescente.h"
#include "gerdecrescente.h"

int main() {
  DIR* path = opendir("../arquivos");
  if (!path) {
    mkdir("../arquivos", 0700);
  } else {
    closedir(path);
  }

  printf("Digite a opção\n");
  printf("1 - Converter arquivo arvore binaria para txt\n");
  printf("2 - Converter arquivo index para txt\n");
  printf("3 - Converter arquivo de registros para txt\n");
  printf("4 - Gerar arquivo crescente\n");
  printf("5 - Gerar arquivo decrescente\n");
  printf("6 - Gerar arquivo aleatorio\n");
  printf("Digite a opção: ");
  int option;
  scanf("%d", &option);

  if (option == 1) {
    converterArquivoArvoreBinariaParaTxt();
  } else if (option == 2) {
    converterArquivoIndexParaBinario();
  } else if (option == 3) {
    converterBinarioDeRegistrosParaTxt();
  }

  if (option >= 4) {
    printf("Tamanho: ");
    int tam;
    scanf("%d", &tam);
    if (option == 4) {
      gercrescente(tam);
    } else if (option == 5) {
      gerdecrescente(tam);
    } else if (option == 6) {
      geraleatorio(tam);
    }
  }
}