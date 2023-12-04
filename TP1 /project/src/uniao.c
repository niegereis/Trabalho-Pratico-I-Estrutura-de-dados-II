#include "../lib/uniao.h"

void analiseInicia(Analise* analise) {
  analise->comparacaoInsercao = 0;
  analise->comparacaoPesquisa = 0;
  analise->transferenciaInsercao = 0;
  analise->transferenciaPesquisa = 0;
  analise->tempoInsere = 0;
  analise->tempoPesquisa = 0;
}

void imprimeRegistro(Registro reg) {
  char tmp[20];
  strncpy(tmp, reg.dado2, 19);
  printf("Registro:\n\tChave: %d\n\tDado 1: %ld\n\tDado 2: %s\n", reg.chave,
         reg.dado1, tmp);
}

void imprimeAnalise(Analise an) {
  printf(
      "\nInserção:\n\tComparações: %d\n\tTransferências: %d\n\tTempo(em "
      "nano segundos): %lld",
      an.comparacaoInsercao, an.transferenciaInsercao, an.tempoInsere);
  printf(
      "\nPesquisa:\n\tComparações: %d\n\tTransferências: %d\n\tTempo(em "
      "nano segundos): %lld\n",
      an.comparacaoPesquisa, an.transferenciaPesquisa, an.tempoPesquisa);
}

bool pesquisaMetodo(int metodo, int situacao, int chave, int quantidade,
                    bool exibirRegistros, Analise* analise,
                    bool imprimirRelatorio) {
  analiseInicia(analise);
  Registro encontrado;
  short achou = 0;
  FILE* arquivo;

  if (metodo >= 2) {
    switch (situacao) {
      case 1:
        arquivo = fopen("./arquivos/crescente.bin", "r+b");
        break;

      case 2:
        arquivo = fopen("./arquivos/decrescente.bin", "r+b");
        break;

      case 3:
        arquivo = fopen("./arquivos/aleatorio.bin", "r+b");
        break;

      default:
        printf("Invalido\n");
        return false;
    }
  } else {
    arquivo = fopen("./arquivos/crescente.bin", "r+b");
  }

  if (arquivo == NULL) {
    perror("Não foi possível abrir o arquivo.\n");
    return false;
  }

  if (exibirRegistros) {
    printf("=============== Arquivo ==================\n");
    printf("==========================================\n");
    imprimirArquivoBinario(arquivo, quantidade);
    printf("==========================================\n");
  }

  switch (metodo) {
    case 1:  // sequencial
      encontrado =
          acessoSequencialIndexado(analise, chave, &achou, arquivo, quantidade);
      break;

    case 2:  // arvore binaria
      encontrado = arvoreBinaria(analise, chave, &achou, arquivo, quantidade);
      break;

    case 3:  // arvore b
      encontrado = arvoreB(analise, chave, &achou, arquivo, quantidade);
      break;

    case 4:  // arvore b*
      encontrado = arvoreBEstrela(analise, chave, &achou, arquivo, quantidade);
      break;

    default:
      printf("Invalido\n");
      return false;
  }

  fclose(arquivo);

  if (imprimirRelatorio) {
    if (achou == 1) {
      printf("\nRegistro encontrado!\n");
      imprimeRegistro(encontrado);
      imprimeAnalise(*analise);

    } else {
      printf("\nO registro não foi encontrado!\n\n");
      imprimeAnalise(*analise);
    }
  }
  if (achou)
    return true;
  else
    return false;
}

void imprimirArquivoBinario(FILE* file, int quantidade) {
  Registro r;
  int i = 0;
  while (fread(&r, sizeof(Registro), 1, file) > 0 && i < quantidade) {
    i++;
    char tmp[20];
    strncpy(tmp, r.dado2, 19);

    printf("    %d %0ld %s\n", r.chave, r.dado1, tmp);
  }
  fseek(file, 0, 0);
}