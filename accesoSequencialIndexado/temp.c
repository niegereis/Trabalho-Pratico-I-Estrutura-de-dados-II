#include "acessoSequencialIndexado.h"
// NAO VERIFICA SE A CHAVE DE ENTRADA E MENOR QUE A CHAVE DO PRIMEIRO REGISTRO

bool pesquisaSequencial(int chave, Registro* registro) {
  FILE* arquivoDeIndex = fopen("crescenteIndex.bin", "r+b");
  if (arquivoDeIndex == NULL) return false;

  FILE* arquivoDeRegitros = fopen("crescente.bin", "r+b");
  if (arquivoDeRegitros == NULL) return false;

  bool fimPaginaIndexPrincipal = false;
  while (!fimPaginaIndexPrincipal) {
    ItemIndice itensIndex[QTD_ITENS_A_SER_LIDOS];
    if (fread(itensIndex, sizeof(ItemIndice), QTD_ITENS_A_SER_LIDOS,
              arquivoDeIndex) == 0)
      fimPaginaIndexPrincipal = true;
  }

  int main() {
    Registro registro;
    if (PesquisaSequencial(16, &registro))
      printf("SUCESSO!\n");
    else
      printf("DEU ERRADO!");
  }