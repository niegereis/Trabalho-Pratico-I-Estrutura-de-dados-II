#include "acessoSequencialIndexado.h"

ItemIndice criarItemIndicePeloRegistro(Registro r, int pos);
void imprimeItemsArquivoBin(FILE* file);

bool criarPaginaIndicePrincipal() {
  FILE* arquivo = fopen("crescente.bin", "rb");
  if (arquivo == NULL) return false;

  FILE* arquivoPaginaIndexPrincipal = fopen("crescenteIndex.bin", "w+b");
  FILE* arquivoPaginaIndexPrincipalTxt = fopen("crescenteIndex.txt", "w+");
  if (arquivoPaginaIndexPrincipal == NULL) return false;

  Registro registro;
  int posicaoItemAtual = 0;
  while (fread(&registro, sizeof(Registro), 1, arquivo) == 1) {
    ItemIndice item = criarItemIndicePeloRegistro(registro, posicaoItemAtual++);
    fwrite(&item, sizeof(ItemIndice), 1, arquivoPaginaIndexPrincipal);

    fprintf(arquivoPaginaIndexPrincipalTxt, "%d %d\n", item.posicao,
            item.chave);

    fseek(arquivo, (ITENS_PAGINA - 1) * sizeof(Registro), SEEK_CUR);
  }

  imprimeItemsArquivoBin(arquivoPaginaIndexPrincipal);

  fclose(arquivo);
  fclose(arquivoPaginaIndexPrincipal);

  return true;
}

ItemIndice criarItemIndicePeloRegistro(Registro r, int pos) {
  ItemIndice item;
  item.chave = r.chave;
  item.posicao = pos * ITENS_PAGINA;
  return item;
}

void imprimeItemsArquivoBin(FILE* file) {
  long int pos = ftell(file);

  fseek(file, 0, 0);
  ItemIndice item;
  while (fread(&item, sizeof(ItemIndice), 1, file) == 1) {
    printf("%d, %d\n", item.posicao, item.chave);
  }

  fseek(file, pos, SEEK_SET);
}

int main() {
  bool s = criarPaginaIndicePrincipal();
  if (s) {
    printf("SUCESSO");
  } else {
    printf("Error");
  }
  printf("\n");
}