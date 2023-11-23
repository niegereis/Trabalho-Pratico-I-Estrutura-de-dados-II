#include "../lib/arvoreBEstrela.h"

// Função para criar uma nova árvore B*
ArvoreBEstrela arvoreCria() {  // OK
  ArvoreBEstrela arvore = NULL;
  return arvore;
}

// Verifica se o nó é externo
bool ehExterno(NoU* no) { return no->tipoNo == Externo; }

// Verifica se o nó é interno
bool ehInterno(NoU* no) { return no->tipoNo == Interno; }

// Cria um novo nó com o tipo especificado (interno ou externo)
NoU* criaNo(TipoDoNo tipo) {
  NoU* no = (NoU*)malloc(sizeof(NoU));
  no->tipoNo = tipo;

  if (tipo == Interno)

    no->U.Interno.qtdChaves = 0;
  else
    no->U.Externo.qtdRegistros = 0;

  return no;
}

// Insere um registro ordenadamente no nó externo
void insereRegistroOrdenado(NoU* no, Registro registro, Registro* overflow) {
  Registro* registros = no->U.Externo.registros;
  int qtdRegistros = no->U.Externo.qtdRegistros;

  // Se o nó externo estiver vazio, insere o registro
  if (no->U.Externo.qtdRegistros == 0) {
    no->U.Externo.registros[qtdRegistros] = registro;
    no->U.Externo.qtdRegistros++;
    return;
  }

  // Verifica se o vetor de registros está cheio
  bool vetorCheio = no->U.Externo.qtdRegistros == 2 * M;
  if (vetorCheio) {
    // Se o registro inserido for maior que o último, armazena o registro no
    // overflow
    if (registro.chave > registros[qtdRegistros - 1].chave) {
      *overflow = registro;
      return;
    } else {
      // Se não, faz a troca com o último registro e altera o valor de overflow
      Registro tmp = registro;
      registro = registros[qtdRegistros - 1];
      registros[qtdRegistros - 1] = tmp;
      *overflow = registro;
    }
  } else {
    // Se o vetor não estiver cheio, insere o registro
    registros[qtdRegistros] = registro;
    qtdRegistros = (++no->U.Externo.qtdRegistros);
  }

  // Insere o registro ordenadamente no vetor
  Registro tmp = registros[qtdRegistros - 1];
  int i;
  for (i = qtdRegistros - 1; i >= 0; i--) {
    if (tmp.chave < registros[i].chave) {
      registros[i + 1] = registros[i];
    } else if (tmp.chave > registros[i].chave) {
      break;
    }
  }
  registros[++i] = tmp;
}

// Verifica se o nó está cheio (interno ou externo)
bool noCheio(NoU* no) {
  return no->tipoNo == Interno ? no->U.Interno.qtdChaves >= 2 * M
                               : no->U.Externo.qtdRegistros >= 2 * M;
}

// Verifica se um registro já existe no vetor de registros
bool encontraRegistros(Registro* registros, int qtdRegistros, Registro r,
                       Analise* analise) {
  for (int i = 0; i < qtdRegistros; i++) {
    analise->comparacaoInsercao++;
    if (registros[i].chave == r.chave) return true;
  }
  return false;
}

// Insere um registro na folha da árvore B*
bool arvoreInsereNaFolha(NoU* pNo, Registro registro, NoU** noExternoMaiores,
                         Analise* analise) {
  // Verifica se o registro já existe na folha
  if (encontraRegistros(pNo->U.Externo.registros, pNo->U.Externo.qtdRegistros,
                        registro, analise)) {
    return false;
  }

  // Se a folha estiver cheia, faz o split
  if (noCheio(pNo)) {
    Registro overflow;
    // Cria um novo nó externo para armazenar registros maiores
    (*noExternoMaiores) = criaNo(Externo);
    insereRegistroOrdenado(pNo, registro, &overflow);
    Registro* registros = pNo->U.Externo.registros;

    // Copia metade dos registros para o novo nó externo
    for (int i = M; i < 2 * M; i++) {
      (*noExternoMaiores)->U.Externo.registros[i - M] = registros[i];
      (*noExternoMaiores)->U.Externo.qtdRegistros++;
    }

    // Atualiza a quantidade de registros na folha original
    pNo->U.Externo.qtdRegistros -= (*noExternoMaiores)->U.Externo.qtdRegistros;
    (*noExternoMaiores)->U.Externo.registros[pNo->U.Externo.qtdRegistros] =
        overflow;
    (*noExternoMaiores)->U.Externo.qtdRegistros++;

  } else {
    // Se a folha não estiver cheia, insere o registro ordenadamente
    insereRegistroOrdenado(pNo, registro, NULL);
  }
  return true;
}

// Obtém a chave do primeiro elemento do nó
int obtemChavePrimeiroElemento(NoU* n) {
  return n->tipoNo == Interno ? n->U.Interno.chaves[0]
                              : n->U.Externo.registros[0].chave;
}

// Obtém a quantidade de elementos no nó
int obtemQuantidadeElementosDoNo(NoU* n) {
  return n->tipoNo == Interno ? n->U.Interno.qtdChaves
                              : n->U.Externo.qtdRegistros;
}

// Obtém as chaves de um nó interno
int* obterChaves(NoU* no) { return no->U.Interno.chaves; }

// Obtém os apontadores de um nó interno
NoU** obterApontadores(NoU* no) { return no->U.Interno.apontadores; }

// Função recursiva para inserção na árvore B*
bool arvoreInsereRecursiva(NoU** no, Registro registro, NoU** noMaiores,
                           int* chaveS, Analise* analise) {
  // Se o nó é externo, insere na folha
  if ((*no)->tipoNo == Externo) {
    return arvoreInsereNaFolha(*no, registro, noMaiores, analise);
  }

  // Encontra a posição adequada para a inserção no nó interno
  int i, qtdNoAtual = obtemQuantidadeElementosDoNo(*no);
  for (i = 0; i < qtdNoAtual; i++) {
    if (registro.chave < (*no)->U.Interno.chaves[i]) {
      break;
    }
  }

  // Atualiza o contador de comparações
  analise->comparacaoInsercao += i;

  // Chama recursivamente a função para o próximo nó interno
  arvoreInsereRecursiva(&(*no)->U.Interno.apontadores[i], registro, noMaiores,
                        chaveS, analise);

  // Se houver um nó maior resultante da inserção, realiza o split
  if ((*noMaiores) != NULL) {
    // Verifica se há espaço no nó interno para a chave do nó maior
    bool temEspaco = (*no)->U.Interno.qtdChaves < 2 * M;
    if (temEspaco) {
      // Obtém a chave que sobe do nó maior
      int chaveElemQueSobe = obtemChavePrimeiroElemento(*noMaiores);
      if (ehInterno(*noMaiores)) chaveElemQueSobe = *chaveS;

      int qtdElementosDoNo = obtemQuantidadeElementosDoNo(*no);
      int* chaves = obterChaves(*no);
      NoU** apontadores = obterApontadores(*no);

      int i;
      // Insere ordenadamente a chave que sobe e atualiza os apontadores
      for (i = qtdElementosDoNo - 1; i >= 0; i--) {
        if (chaveElemQueSobe < chaves[i]) {
          chaves[i + 1] = chaves[i];
          apontadores[i + 2] = apontadores[i + 1];
        } else if (chaveElemQueSobe > chaves[i]) {
          break;
        }
      }
      chaves[i + 1] = chaveElemQueSobe;
      (*no)->U.Interno.qtdChaves++;
      apontadores[i + 2] = *noMaiores;
      *noMaiores = NULL;
    } else {
      // Cria um novo nó interno e realiza o split
      int chaveElemQueSobe = obtemChavePrimeiroElemento(*noMaiores);
      if (ehInterno(*noMaiores)) chaveElemQueSobe = *chaveS;
      NoU* apontadorDoElementoQueSobe = *noMaiores;

      int* chavesNoAtual = (*no)->U.Interno.chaves;
      int qtdElementosDoNo = obtemQuantidadeElementosDoNo(*no);

      int ultimaChaveDoNo = chavesNoAtual[qtdElementosDoNo - 1];
      NoU** apontadores = obterApontadores(*no);

      if (ultimaChaveDoNo > chaveElemQueSobe) {
        // Troca as chaves
        chavesNoAtual[qtdElementosDoNo - 1] = chaveElemQueSobe;
        chaveElemQueSobe = ultimaChaveDoNo;

        // Troca os nós
        NoU* tmp = apontadores[qtdElementosDoNo];
        apontadores[qtdElementosDoNo] = apontadorDoElementoQueSobe;
        apontadorDoElementoQueSobe = tmp;
      }
      // chaveElemQueSobe
      int ultimaChave = chavesNoAtual[qtdElementosDoNo - 1];
      NoU* ultimoApontador = apontadores[qtdElementosDoNo];

      int i;
      // Insere ordenadamente a chave que sobe e atualiza os apontadores
      for (i = qtdElementosDoNo - 1; i >= 0; i--) {
        if (ultimaChave < chavesNoAtual[i]) {
          chavesNoAtual[i + 1] = chavesNoAtual[i];
          apontadores[i + 2] = apontadores[i + 1];
        } else if (ultimaChave > chavesNoAtual[i]) {
          break;
        }
      }
      apontadores[i + 2] = ultimoApontador;
      chavesNoAtual[i + 1] = ultimaChave;

      // Cria um novo nó interno e realiza o split
      NoU* novoNo = criaNo(Interno);
      novoNo->U.Interno.apontadores[0] = (*no)->U.Interno.apontadores[M + 1];

      // Atualiza a chave que será promovida para o nível acima
      *chaveS = (*no)->U.Interno.chaves[M];
      // Decrementa a quantidade de chaves no nó original após a promoção
      (*no)->U.Interno.qtdChaves--;

      // Move as chaves e apontadores do nó original para o novo nó
      for (int k = M + 1; k < 2 * M; k++) {
        novoNo->U.Interno.chaves[k - (M + 1)] = chavesNoAtual[k];
        novoNo->U.Interno.qtdChaves++;
        novoNo->U.Interno.apontadores[k - M] = apontadores[k + 1];
      }

      // Atualiza a quantidade de chaves no nó original após a transferência
      (*no)->U.Interno.qtdChaves -= novoNo->U.Interno.qtdChaves;

      // Insere a chave promovida no novo nó
      novoNo->U.Interno.chaves[novoNo->U.Interno.qtdChaves] = chaveElemQueSobe;
      novoNo->U.Interno.qtdChaves++;

      // Atualiza o apontador correspondente à chave promovida no novo nó
      novoNo->U.Interno.apontadores[novoNo->U.Interno.qtdChaves] =
          apontadorDoElementoQueSobe;
      // Atualiza o ponteiro para o nó maior resultante da promoção
      *noMaiores = novoNo;
    }
  }
  return true;
}

// Função principal para inserção na árvore B*
bool arvoreInsere(ArvoreBEstrela* arvore, Registro registro, Analise* analise) {
  // Caso base: árvore vazia
  if (*arvore == NULL) {
    // Cria um nó externo e insere o registro
    *arvore = criaNo(Externo);
    (*arvore)->U.Externo.registros[0] = registro;
    (*arvore)->U.Externo.qtdRegistros++;
    return true;
  }
  // Ponteiro para o nó maior resultante da inserção recursiva
  NoU* novoNoMaiores = NULL;
  // Variável para armazenar a chave que sobe durante o processo de split
  int chaveS;
  // Chama a função de inserção recursiva
  arvoreInsereRecursiva(arvore, registro, &novoNoMaiores, &chaveS, analise);
  // Se há um nó maior resultante da inserção
  if (novoNoMaiores != NULL) {
    // Verifica se o nó maior é externo
    if (ehExterno(novoNoMaiores)) {
      // Cria um novo nó interno para a promoção do nó externo
      NoU* no = criaNo(Interno);
      // Obtém a chave do primeiro elemento do nó externo promovido
      int chavePrimeiroElem = obtemChavePrimeiroElemento(novoNoMaiores);
      // Atualiza o novo nó interno com a chave promovida e os apontadores
      no->U.Interno.chaves[0] = chavePrimeiroElem;
      no->U.Interno.qtdChaves++;
      no->U.Interno.apontadores[0] = *arvore;
      no->U.Interno.apontadores[1] = novoNoMaiores;
      (*arvore) = no;
    } else {
      // Cria um novo nó interno para a promoção de um nó interno
      NoU* no = criaNo(Interno);
      // Atualiza o novo nó interno com a chave promovida e os apontadores
      no->U.Interno.chaves[0] = chaveS;
      no->U.Interno.qtdChaves++;
      no->U.Interno.apontadores[0] = *arvore;
      no->U.Interno.apontadores[1] = novoNoMaiores;
      (*arvore) = no;
    }
  }
  return true;
}

// Função para imprimir a árvore B*
void arvoreImprime(ArvoreBEstrela arvore) {
  // Verifica se o nó é externo
  if (ehExterno(arvore)) {
    // Imprime as chaves do nó externo
    for (int i = 0; i < arvore->U.Externo.qtdRegistros; i++) {
      int chave = arvore->U.Externo.registros[i].chave;
      printf("%d ", chave);
    }
  } else {
    // Caso o nó seja interno, imprime suas chaves e chama recursivamente para
    // os apontadores
    for (int i = 0; i < arvore->U.Interno.qtdChaves + 1; i++) {
      arvoreImprime(arvore->U.Interno.apontadores[i]);
    }
  }
}

// Função para realizar a pesquisa em um nó externo da árvore B*
bool pesquisaNoExterno(ArvoreBEstrela pNo, int chave, Analise* analise,
                       Registro* retorno) {
  // Inicializa o índice e a chave atual com o primeiro elemento do nó externo
  int i = 0;
  int chaveAtual = pNo->U.Externo.registros[i].chave;

  // Percorre o nó externo até encontrar a chave ou atingir o final do nó
  while (i < pNo->U.Externo.qtdRegistros && chave > chaveAtual) {
    chaveAtual = pNo->U.Externo.registros[i].chave;
    i++;
  }
  // Atualiza o contador de comparações da pesquisa
  analise->comparacaoPesquisa += i;

  // Verifica se a chave foi encontrada e, se sim, atualiza o registro de
  // retorno
  if (chave == chaveAtual) {
    (*retorno) = pNo->U.Externo.registros[i];
    return true;
  }
  return false;
}

// Função para realizar a pesquisa em um nó interno da árvore B*
bool pesquisaNoInterno(ArvoreBEstrela pNo, int chave, Analise* analise,
                       Registro* retorno) {
  // Verifica se o nó é nulo
  if (pNo == NULL) return false;

  // Se o nó for externo, realiza a pesquisa no nó externo correspondente
  else if (pNo->tipoNo == Externo)
    return pesquisaNoExterno(pNo, chave, analise, retorno);

  // Se o nó for interno, continua a pesquisa nos apontadores internos
  int i = 0;
  while (i < pNo->U.Interno.qtdChaves && chave >= pNo->U.Interno.chaves[i]) i++;
  // Atualiza o contador de comparações da pesquisa
  analise->comparacaoPesquisa += i;
  // Verifica se a chave é maior ou igual à última chave do nó interno
  if (chave >= pNo->U.Interno.chaves[i])
    return pesquisaNoInterno(
        pNo->U.Interno.apontadores[pNo->U.Interno.qtdChaves], chave, analise,
        retorno);
  // Continua a pesquisa nos apontadores internos
  return pesquisaNoInterno(pNo->U.Interno.apontadores[i], chave, analise,
                           retorno);
}

// Função para buscar uma chave na árvore B*
Registro arvoreBEstrela(Analise* analise, int chave, short* achou,
                        FILE* arquivo, int quantidade) {
  // Variáveis locais
  Registro registroEncontrado;
  bool valido;
  struct timespec inicio, fim;

  // Cria um nó externo para inserção
  NoU* no = criaNo(Externo);

  // Inicia o processo de inserção na árvore B*
  clock_gettime(CLOCK_MONOTONIC, &inicio);
  int i = 0;
  while ((fread(&registroEncontrado, sizeof(Registro), 1, arquivo) == 1) &&
         i < quantidade) {
    i++;
    arvoreInsere(&no, registroEncontrado, analise);
  }
  analise->transferenciaInsercao = i;
  clock_gettime(CLOCK_MONOTONIC, &fim);
  analise->tempoInsere =
      (fim.tv_sec - inicio.tv_sec) * 1e9 + (fim.tv_nsec - inicio.tv_nsec);

  // Configura a chave desejada
  registroEncontrado.chave = chave;
  // Inicia o processo de pesquisa na árvore B*
  clock_gettime(CLOCK_MONOTONIC, &inicio);
  if (no->tipoNo == Interno)
    valido = pesquisaNoInterno(no, chave, analise, &registroEncontrado);
  else if (no->tipoNo == Externo)
    valido = pesquisaNoExterno(no, chave, analise, &registroEncontrado);
  clock_gettime(CLOCK_MONOTONIC, &fim);
  analise->tempoPesquisa =
      (fim.tv_sec - inicio.tv_sec) * 1e9 + (fim.tv_nsec - inicio.tv_nsec);

  // Se a chave não for válida, retorna o último registro encontrado
  if (!valido) return registroEncontrado;

  // Atualiza a flag de achou e retorna o registro encontrado
  *achou = 1;
  return registroEncontrado;
}