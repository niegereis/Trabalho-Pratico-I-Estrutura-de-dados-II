#include "../lib/acessoSequencialIndexado.h"

ItemIndice criarItemIndicePeloRegistro(Registro r, int pos);
void imprimeItemsArquivoBin(FILE* file);

bool criarPaginaIndicePrincipal(FILE* arquivo, Analise* analise,
                                int quantidade) {
  FILE* arquivoPaginaIndexPrincipal =
      fopen("./arquivos/crescenteIndex.bin", "w+b");
  FILE* arquivoPaginaIndexPrincipalTxt =
      fopen("./arquivos/crescenteIndex.txt", "w+");
  if (arquivoPaginaIndexPrincipal == NULL) return false;

  Registro registro;
  int posicaoItemAtual = 0;
  int i = 0;
  while (fread(&registro, sizeof(Registro), 1, arquivo) == 1 &&
         i < quantidade) {
    analise->transferenciaInsercao++;
    ItemIndice item = criarItemIndicePeloRegistro(registro, posicaoItemAtual++);
    fwrite(&item, sizeof(ItemIndice), 1, arquivoPaginaIndexPrincipal);

    fprintf(arquivoPaginaIndexPrincipalTxt, "%d %d\n", item.posicao,
            item.chave);

    fseek(arquivo, (ITENS_PAGINA - 1) * sizeof(Registro), SEEK_CUR);
    i += 3;
  }

  // imprimeItemsArquivoBin(arquivoPaginaIndexPrincipal);

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

// NAO VERIFICA SE A CHAVE DE ENTRADA E MENOR QUE A CHAVE DO PRIMEIRO REGISTRO
bool buscaRegistroNaPagina(int chave, Registro* registro, ItemIndice indice,
                           FILE* arquivoDeRegitros) {
  fseek(arquivoDeRegitros, sizeof(Registro) * indice.posicao, SEEK_SET);

  Registro registros[QTD_ITENS_A_SER_LIDOS];
  int qtdItem;
  int j = 0;
  while ((qtdItem = fread(registros, sizeof(Registro), QTD_ITENS_A_SER_LIDOS,
                          arquivoDeRegitros)) > 0 &&
         j < QTD_ITENS_A_SER_LIDOS) {
    j++;
    for (int i = 0; i < qtdItem; i++) {
      if (chave == registros[i].chave) {
        *registro = registros[i];
        return true;
      }
    }
  }
  return false;
}

bool pesquisaSequencial(int chave, Registro* registro, FILE* arquivoDeRegistros,
                        Analise* analise) {
  FILE* arquivoDeIndex = fopen("./arquivos/crescenteIndex.bin", "r+b");
  if (arquivoDeIndex == NULL) return false;

  bool fimDoArquivoIndexPrincipal = false;
  ItemIndice ultimoItemDaPagina;

  while (!fimDoArquivoIndexPrincipal) {
    ItemIndice itensDoArquivoIndex[QTD_ITENS_A_SER_LIDOS];
    int qtdItensLidos = fread(itensDoArquivoIndex, sizeof(ItemIndice),
                              QTD_ITENS_A_SER_LIDOS, arquivoDeIndex);
    analise->transferenciaPesquisa = qtdItensLidos;
    if (qtdItensLidos == 0) {
      return buscaRegistroNaPagina(chave, registro, ultimoItemDaPagina,
                                   arquivoDeRegistros);
      fimDoArquivoIndexPrincipal = true;
    }
    for (int i = 0; i < qtdItensLidos; i++) {
      int chaveAtual = itensDoArquivoIndex[i].chave;

      analise->comparacaoPesquisa++;
      if (chaveAtual == chave) {
        return buscaRegistroNaPagina(chave, registro, itensDoArquivoIndex[i],
                                     arquivoDeRegistros);
      }
      analise->comparacaoPesquisa++;
      if (chaveAtual > chave) {
        bool ehPrimeiroItemDaPagina = (i == 0);
        if (ehPrimeiroItemDaPagina) {
          return buscaRegistroNaPagina(chave, registro, ultimoItemDaPagina,
                                       arquivoDeRegistros);
        }
        return buscaRegistroNaPagina(
            chave, registro, itensDoArquivoIndex[i - 1], arquivoDeRegistros);
      }
    }
    ultimoItemDaPagina = itensDoArquivoIndex[qtdItensLidos - 1];
  }
  return false;
}

Registro acessoSequencialIndexado(Analise* analise, int chave, short* achou,
                                  FILE* arquivo, int quantidade) {
  Registro registroEncontrado;
  bool valido;
  struct timespec inicio, fim;

  clock_gettime(CLOCK_MONOTONIC, &inicio);

  criarPaginaIndicePrincipal(arquivo, analise, quantidade);
  clock_gettime(CLOCK_MONOTONIC, &fim);
  analise->tempoInsere = fim.tv_nsec - inicio.tv_nsec;

  clock_gettime(CLOCK_MONOTONIC, &inicio);
  valido = pesquisaSequencial(chave, &registroEncontrado, arquivo, analise);
  clock_gettime(CLOCK_MONOTONIC, &fim);
  analise->tempoPesquisa = fim.tv_nsec - inicio.tv_nsec;
  if (!valido) return registroEncontrado;

  *achou = 1;
  return registroEncontrado;
}