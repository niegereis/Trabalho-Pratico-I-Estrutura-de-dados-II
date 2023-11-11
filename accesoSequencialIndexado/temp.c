#include "acessoSequencialIndexado.h"
// NAO VERIFICA SE A CHAVE DE ENTRADA E MENOR QUE A CHAVE DO PRIMEIRO REGISTRO
bool buscaRegistroNaPagina(int chave, Registro* registro, ItemIndice indice) {
  FILE* arquivoDeRegitros = fopen("crescente.bin", "r+b");
  if (arquivoDeRegitros == NULL) return false;

  fseek(arquivoDeRegitros, sizeof(Registro) * indice.posicao, SEEK_SET);
  Registro registros[QTD_ITENS_A_SER_LIDOS];
  int qtdItem;
  while ((qtdItem = fread(registros, sizeof(Registro), QTD_ITENS_A_SER_LIDOS,
                          arquivoDeRegitros)) > 0) {
    for (int i = 0; i < qtdItem; i++) {
      if (chave == registros[i].chave) {
        *registro = registros[i];
        return true;
      }
    }
  }
  return false;
}

bool pesquisaSequencial(int chave, Registro* registro) {
  FILE* arquivoDeIndex = fopen("crescenteIndex.bin", "r+b");
  if (arquivoDeIndex == NULL) return false;

  bool fimDoArquivoIndexPrincipal = false;
  ItemIndice ultimoItemDaPagina;

  while (!fimDoArquivoIndexPrincipal) {
    ItemIndice itensDoArquivoIndex[QTD_ITENS_A_SER_LIDOS];
    int qtdItensLidos = fread(itensDoArquivoIndex, sizeof(ItemIndice),
                              QTD_ITENS_A_SER_LIDOS, arquivoDeIndex);

    if (qtdItensLidos == 0) fimDoArquivoIndexPrincipal = true;
    for (int i = 0; i < qtdItensLidos; i++) {
      int chaveAtual = itensDoArquivoIndex[i].chave;
      if (chaveAtual == chave)
        return buscaRegistroNaPagina(chave, registro, itensDoArquivoIndex[i]);
      if (chaveAtual > chave) {
        bool ehPrimeiroItemDaPagina = (i == 0);
        if (ehPrimeiroItemDaPagina) {
          return buscaRegistroNaPagina(chave, registro, ultimoItemDaPagina);
        }
        return buscaRegistroNaPagina(chave, registro,
                                     itensDoArquivoIndex[i - 1]);
      }
    }
    ultimoItemDaPagina = itensDoArquivoIndex[qtdItensLidos - 1];
  }
}

void imprime(int chave) {
  Registro registro;
  if (pesquisaSequencial(chave, &registro))
    printf("SUCESSO! %ld\n", registro.dado1);
  else
    printf("DEU ERRADO!\n");
}

int main() {
  imprime(0);
  imprime(7);
  imprime(8);
  imprime(9);
  imprime(14);
  imprime(16);
  imprime(17);
  imprime(19);
  imprime(23);
  imprime(10);
}
