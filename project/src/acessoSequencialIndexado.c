#include "../lib/acessoSequencialIndexado.h"

ItemIndice criarItemIndicePeloRegistro(Registro r, int pos);
void imprimeItemsArquivoBin(FILE* file);

// Função para criar uma página de índice principal a partir de um arquivo de
// registros
bool criarPaginaIndicePrincipal(FILE* arquivo, Analise* analise,
                                int quantidade) {
  // Abre o arquivo para a página de índice principal em modo leitura e escrita
  FILE* arquivoPaginaIndexPrincipal =
      fopen("./arquivos/crescenteIndex.bin", "w+b");
  if (arquivoPaginaIndexPrincipal == NULL) return false;

  // Variáveis locais
  Registro registro;
  int posicaoItemAtual = 0;
  int i = 0;
  // Processa o arquivo de registros para criar a página de índice principal
  while (fread(&registro, sizeof(Registro), 1, arquivo) == 1 &&
         i < quantidade) {
    // Atualiza a contagem de transferências
    analise->transferenciaInsercao++;
    // Cria um item de índice a partir do registro atual e escreve no arquivo da
    // página de índice principal
    ItemIndice item = criarItemIndicePeloRegistro(registro, posicaoItemAtual++);
    fwrite(&item, sizeof(ItemIndice), 1, arquivoPaginaIndexPrincipal);
    // Move o cursor do arquivo para o próximo bloco de registros
    fseek(arquivo, (ITENS_PAGINA - 1) * sizeof(Registro), SEEK_CUR);
    i += ITENS_PAGINA;
  }

  // Fecha o arquivo da página de índice principal
  fclose(arquivoPaginaIndexPrincipal);

  return true;
}

// Função para criar um ItemIndice a partir de um Registro e posição
ItemIndice criarItemIndicePeloRegistro(Registro r, int pos) {
  // Cria um novo ItemIndice
  ItemIndice item;
  // Atribui a chave do registro ao ItemIndice
  item.chave = r.chave;
  // Calcula e atribui a posição do registro no arquivo à posição do ItemIndice
  item.posicao = pos * ITENS_PAGINA;
  // Retorna o ItemIndice criado
  return item;
}

// Função para imprimir os itens de um arquivo binário de índice
void imprimeItemsArquivoBin(FILE* file) {
  // Salva a posição atual no arquivo
  long int pos = ftell(file);

  // Move o cursor para o início do arquivo
  fseek(file, 0, 0);
  // Declara uma variável para armazenar cada ItemIndice lido do arquivo
  ItemIndice item;
  // Loop para ler e imprimir cada ItemIndice do arquivo
  while (fread(&item, sizeof(ItemIndice), 1, file) == 1) {
    printf("%d, %d\n", item.posicao, item.chave);
  }
  // Restaura a posição original no arquivo
  fseek(file, pos, SEEK_SET);
}

// Função para buscar um registro na página usando um índice
bool buscaRegistroNaPagina(int chave, Registro* registro, ItemIndice indice,
                           FILE* arquivoDeRegitros, Analise* analise,
                           int quantidade) {
  // Move o cursor para a posição inicial da página no arquivo de registros
  fseek(arquivoDeRegitros, sizeof(Registro) * indice.posicao, SEEK_SET);
  // Declara um array para armazenar os registros lidos do arquivo
  Registro registros[QTD_ITENS_A_SER_LIDOS];
  // Variável para armazenar a quantidade de itens lidos em cada fread
  int qtdItem;
  // Variável para contar os blocos de leitura
  int j = 0;
  // Variável para contar a quantidade total de itens lidos
  int itensLidos = 0;
  analise->transferenciaPesquisa++;
  // Loop para ler blocos de registros do arquivo
  while ((qtdItem = fread(registros, sizeof(Registro), QTD_ITENS_A_SER_LIDOS,
                          arquivoDeRegitros)) > 0 &&
         j * QTD_ITENS_A_SER_LIDOS < ITENS_PAGINA) {
    j++;
    // Loop para verificar cada registro no bloco lido
    for (int i = 0; i < qtdItem && itensLidos < quantidade; i++) {
      // Incrementa o contador de comparações
      analise->comparacaoPesquisa++;
      itensLidos++;
      // Verifica se a chave do registro é igual à chave desejada
      if (chave == registros[i].chave) {
        // Se encontrou, copia o registro e retorna true
        *registro = registros[i];
        return true;
      }
    }
  }
  // Se não encontrou o registro, retorna false
  return false;
}

// Função para pesquisa sequencial usando um arquivo de índice
bool pesquisaSequencial(int chave, Registro* registro, FILE* arquivoDeRegistros,
                        Analise* analise, int quantidade) {
  // Abre o arquivo de índice
  FILE* arquivoDeIndex = fopen("./arquivos/crescenteIndex.bin", "r+b");
  // Verifica se o arquivo de índice foi aberto com sucesso
  if (arquivoDeIndex == NULL) return false;
  // Variável para indicar o fim do arquivo de índice principal
  bool fimDoArquivoIndexPrincipal = false;
  // Variável para armazenar o último item da página
  ItemIndice ultimoItemDaPagina;
  // Array para armazenar os itens do arquivo de índice lidos
  ItemIndice itensDoArquivoIndex[QTD_ITENS_A_SER_LIDOS];

  // Lê uma parte do arquivo de índice contendo os índices de pesquisa
  int qtdItensLidos = fread(itensDoArquivoIndex, sizeof(ItemIndice),
                            QTD_ITENS_A_SER_LIDOS, arquivoDeIndex);

  // Incrementa o contador de transferências de pesquisa
  analise->transferenciaPesquisa++;
  // Incrementa o contador de comparações
  analise->comparacaoPesquisa++;

  // Verifica se a chave procurada é menor do que a menor chave no arquivo
  if (chave < itensDoArquivoIndex[0].chave) return false;

  // Loop principal
  while (!fimDoArquivoIndexPrincipal) {
    // Verifica se não há mais itens no arquivo de índice
    if (qtdItensLidos == 0) {
      // Realiza a busca na página usando o último item da página
      return buscaRegistroNaPagina(chave, registro, ultimoItemDaPagina,
                                   arquivoDeRegistros, analise, quantidade);
      fimDoArquivoIndexPrincipal =
          true;  // Indica o fim do arquivo de índice principal
    }

    // Loop para verificar cada item lido do arquivo de índice
    for (int i = 0; i < qtdItensLidos; i++) {
      int chaveAtual = itensDoArquivoIndex[i].chave;
      // Incrementa o contador de comparações
      analise->comparacaoPesquisa++;
      // Verifica se a chave atual é igual à chave desejada
      if (chaveAtual == chave) {
        // Realiza a busca na página usando o item encontrado
        return buscaRegistroNaPagina(chave, registro, itensDoArquivoIndex[i],
                                     arquivoDeRegistros, analise, quantidade);
      }
      // Incrementa o contador de comparações
      analise->comparacaoPesquisa++;
      // Verifica se a chave atual é maior do que a chave desejada
      if (chaveAtual > chave) {
        bool ehPrimeiroItemDaPagina = (i == 0);
        // Verifica se é o primeiro item da página
        if (ehPrimeiroItemDaPagina) {
          // Realiza a busca na página usando o último item da página
          return buscaRegistroNaPagina(chave, registro, ultimoItemDaPagina,
                                       arquivoDeRegistros, analise, quantidade);
        }
        // Realiza a busca na página usando o item anterior
        return buscaRegistroNaPagina(chave, registro,
                                     itensDoArquivoIndex[i - 1],
                                     arquivoDeRegistros, analise, quantidade);
      }
    }

    // Atualiza o último item da página com o último item lido
    ultimoItemDaPagina = itensDoArquivoIndex[qtdItensLidos - 1];
    // Lê mais itens do arquivo de índice
    qtdItensLidos = fread(itensDoArquivoIndex, sizeof(ItemIndice),
                          QTD_ITENS_A_SER_LIDOS, arquivoDeIndex);
    // Incrementa o contador de transferências de pesquisa
    analise->transferenciaPesquisa++;
  }
  return false;
}

// Função para acessar sequencialmente um arquivo indexado
Registro acessoSequencialIndexado(Analise* analise, int chave, short* achou,
                                  FILE* arquivo, int quantidade) {
  Registro registroEncontrado;
  bool valido;
  struct timespec inicio, fim;

  // Mede o tempo de início
  clock_gettime(CLOCK_MONOTONIC, &inicio);
  // Cria a página de índice principal
  criarPaginaIndicePrincipal(arquivo, analise, quantidade);
  // Mede o tempo de fim
  clock_gettime(CLOCK_MONOTONIC, &fim);
  // Calcula o tempo de inserção
  analise->tempoInsere =
      (fim.tv_sec - inicio.tv_sec) * 1e9 + (fim.tv_nsec - inicio.tv_nsec);
  // Mede o tempo de início
  clock_gettime(CLOCK_MONOTONIC, &inicio);
  // Realiza a pesquisa sequencial
  valido = pesquisaSequencial(chave, &registroEncontrado, arquivo, analise,
                              quantidade);
  // Mede o tempo de fim
  clock_gettime(CLOCK_MONOTONIC, &fim);
  // Calcula o tempo de pesquisa
  analise->tempoPesquisa =
      (fim.tv_sec - inicio.tv_sec) * 1e9 + (fim.tv_nsec - inicio.tv_nsec);
  // Verifica se a pesquisa não foi bem-sucedida
  if (!valido) return registroEncontrado;
  // Define que o registro foi encontrado
  *achou = 1;
  // Retorna o registro encontrado
  return registroEncontrado;
}
