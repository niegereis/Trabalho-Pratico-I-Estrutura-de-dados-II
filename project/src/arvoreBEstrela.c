#include "../lib/arvoreBEstrela.h"

ArvoreBEstrela arvoreCria() {  // OK
  ArvoreBEstrela arvore = NULL;
  return arvore;
}

bool ehExterno(NoU* no) { return no->tipoNo == Externo; }
bool ehInterno(NoU* no) { return no->tipoNo == Interno; }

NoU* criaNo(TipoDoNo tipo) {
  NoU* no = (NoU*)malloc(sizeof(NoU));
  no->tipoNo = tipo;

  if (tipo == Interno)

    no->U.Interno.qtdChaves = 0;
  else
    no->U.Externo.qtdRegistros = 0;

  return no;
}

void insereRegistroOrdenado(NoU* no, Registro registro, Registro* overflow) {
  Registro* registros = no->U.Externo.registros;
  int qtdRegistros = no->U.Externo.qtdRegistros;

  if (no->U.Externo.qtdRegistros == 0) {
    no->U.Externo.registros[qtdRegistros] = registro;
    no->U.Externo.qtdRegistros++;
    return;
  }

  bool vetorCheio = no->U.Externo.qtdRegistros == 2 * M;
  if (vetorCheio) {
    if (registro.chave > registros[qtdRegistros - 1].chave) {
      *overflow = registro;
      return;
    } else {
      Registro tmp = registro;
      registro = registros[qtdRegistros - 1];
      registros[qtdRegistros - 1] = tmp;
      *overflow = registro;
    }
  } else {
    registros[qtdRegistros] = registro;
    qtdRegistros = (++no->U.Externo.qtdRegistros);
  }

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

bool noCheio(NoU* no) {
  return no->tipoNo == Interno ? no->U.Interno.qtdChaves >= 2 * M
                               : no->U.Externo.qtdRegistros >= 2 * M;
}

bool encontraRegistros(Registro* registros, int qtdRegistros, Registro r,
                       Analise* analise) {
  for (int i = 0; i < qtdRegistros; i++) {
    analise->comparacaoInsercao++;
    if (registros[i].chave == r.chave) return true;
  }
  return false;
}

bool arvoreInsereNaFolha(NoU* pNo, Registro registro, NoU** noExternoMaiores,
                         Analise* analise) {
  if (encontraRegistros(pNo->U.Externo.registros, pNo->U.Externo.qtdRegistros,
                        registro, analise)) {
    return false;
  }

  if (noCheio(pNo)) {
    Registro overflow;

    (*noExternoMaiores) = criaNo(Externo);
    insereRegistroOrdenado(pNo, registro, &overflow);
    Registro* registros = pNo->U.Externo.registros;

    for (int i = M; i < 2 * M; i++) {
      (*noExternoMaiores)->U.Externo.registros[i - M] = registros[i];
      (*noExternoMaiores)->U.Externo.qtdRegistros++;
    }
    pNo->U.Externo.qtdRegistros -= (*noExternoMaiores)->U.Externo.qtdRegistros;
    (*noExternoMaiores)->U.Externo.registros[pNo->U.Externo.qtdRegistros] =
        overflow;
    (*noExternoMaiores)->U.Externo.qtdRegistros++;

  } else {
    insereRegistroOrdenado(pNo, registro, NULL);
  }
  return true;
}

int obtemChavePrimeiroElemento(NoU* n) {
  return n->tipoNo == Interno ? n->U.Interno.chaves[0]
                              : n->U.Externo.registros[0].chave;
}

int obtemQuantidadeElementosDoNo(NoU* n) {
  return n->tipoNo == Interno ? n->U.Interno.qtdChaves
                              : n->U.Externo.qtdRegistros;
}

int* obterChaves(NoU* no) { return no->U.Interno.chaves; }

NoU** obterApontadores(NoU* no) { return no->U.Interno.apontadores; }

bool arvoreInsereRecursiva(NoU** no, Registro registro, NoU** noMaiores,
                           int* chaveS, Analise* analise) {
  if ((*no)->tipoNo == Externo) {
    return arvoreInsereNaFolha(*no, registro, noMaiores, analise);
  }

  int i, qtdNoAtual = obtemQuantidadeElementosDoNo(*no);
  for (i = 0; i < qtdNoAtual; i++) {
    if (registro.chave < (*no)->U.Interno.chaves[i]) {
      break;
    }
  }
  analise->comparacaoInsercao += i;
  arvoreInsereRecursiva(&(*no)->U.Interno.apontadores[i], registro, noMaiores,
                        chaveS, analise);

  if ((*noMaiores) != NULL) {
    bool temEspaco = (*no)->U.Interno.qtdChaves < 2 * M;
    if (temEspaco) {
      int chaveElemQueSobe = obtemChavePrimeiroElemento(*noMaiores);
      if (ehInterno(*noMaiores)) chaveElemQueSobe = *chaveS;

      int qtdElementosDoNo = obtemQuantidadeElementosDoNo(*no);
      int* chaves = obterChaves(*no);
      NoU** apontadores = obterApontadores(*no);

      int i;
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
      // cria um novo nó interno e splita
      int chaveElemQueSobe = obtemChavePrimeiroElemento(*noMaiores);
      if (ehInterno(*noMaiores)) chaveElemQueSobe = *chaveS;
      NoU* apontadorDoElementoQueSobe = *noMaiores;

      int* chavesNoAtual = (*no)->U.Interno.chaves;
      int qtdElementosDoNo = obtemQuantidadeElementosDoNo(*no);

      int ultimaChaveDoNo = chavesNoAtual[qtdElementosDoNo - 1];
      NoU** apontadores = obterApontadores(*no);

      if (ultimaChaveDoNo > chaveElemQueSobe) {
        // troca chaves
        chavesNoAtual[qtdElementosDoNo - 1] = chaveElemQueSobe;
        chaveElemQueSobe = ultimaChaveDoNo;

        // troca nos
        NoU* tmp = apontadores[qtdElementosDoNo];
        apontadores[qtdElementosDoNo] = apontadorDoElementoQueSobe;
        apontadorDoElementoQueSobe = tmp;
      }
      // chaveElemQueSobe

      int ultimaChave = chavesNoAtual[qtdElementosDoNo - 1];
      NoU* ultimoApontador = apontadores[qtdElementosDoNo];

      int i;
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

      NoU* novoNo = criaNo(Interno);
      novoNo->U.Interno.apontadores[0] = (*no)->U.Interno.apontadores[M + 1];

      *chaveS = (*no)->U.Interno.chaves[M];
      (*no)->U.Interno.qtdChaves--;

      for (int k = M + 1; k < 2 * M; k++) {
        novoNo->U.Interno.chaves[k - (M + 1)] = chavesNoAtual[k];
        novoNo->U.Interno.qtdChaves++;

        novoNo->U.Interno.apontadores[k - M] = apontadores[k + 1];
      }
      (*no)->U.Interno.qtdChaves -= novoNo->U.Interno.qtdChaves;
      novoNo->U.Interno.chaves[novoNo->U.Interno.qtdChaves] = chaveElemQueSobe;
      novoNo->U.Interno.qtdChaves++;
      novoNo->U.Interno.apontadores[novoNo->U.Interno.qtdChaves] =
          apontadorDoElementoQueSobe;

      *noMaiores = novoNo;
    }
  }
  return true;
}

bool arvoreInsere(ArvoreBEstrela* arvore, Registro registro,
                  Analise* analise) {  // incompleto
  if (*arvore == NULL) {
    *arvore = criaNo(Externo);
    (*arvore)->U.Externo.registros[0] = registro;
    (*arvore)->U.Externo.qtdRegistros++;
    return true;
  }

  NoU* novoNoMaiores = NULL;
  int chaveS;
  arvoreInsereRecursiva(arvore, registro, &novoNoMaiores, &chaveS, analise);
  if (novoNoMaiores != NULL) {
    if (ehExterno(novoNoMaiores)) {
      NoU* no = criaNo(Interno);
      int chavePrimeiroElem = obtemChavePrimeiroElemento(novoNoMaiores);

      no->U.Interno.chaves[0] = chavePrimeiroElem;
      no->U.Interno.qtdChaves++;
      no->U.Interno.apontadores[0] = *arvore;
      no->U.Interno.apontadores[1] = novoNoMaiores;
      (*arvore) = no;
    } else {
      NoU* no = criaNo(Interno);
      no->U.Interno.chaves[0] = chaveS;
      no->U.Interno.qtdChaves++;
      no->U.Interno.apontadores[0] = *arvore;
      no->U.Interno.apontadores[1] = novoNoMaiores;
      (*arvore) = no;
    }
  }
  return true;
}

void arvoreImprime(ArvoreBEstrela arvore) {
  if (ehExterno(arvore)) {
    for (int i = 0; i < arvore->U.Externo.qtdRegistros; i++) {
      int chave = arvore->U.Externo.registros[i].chave;
      printf("%d ", chave);
    }
  } else {
    for (int i = 0; i < arvore->U.Interno.qtdChaves + 1; i++) {
      arvoreImprime(arvore->U.Interno.apontadores[i]);
    }
  }
}

bool pesquisaNoExterno(ArvoreBEstrela pNo, int chave, Analise* analise,
                       Registro* retorno) {
  int i = 0;
  int chaveAtual = pNo->U.Externo.registros[i].chave;
  while (i < pNo->U.Externo.qtdRegistros && chave > chaveAtual) {
    chaveAtual = pNo->U.Externo.registros[i].chave;
    i++;
  }
  analise->comparacaoPesquisa += i;

  if (chave == chaveAtual) {
    (*retorno) = pNo->U.Externo.registros[i];
    return true;
  }
  return false;
}

bool pesquisaNoInterno(ArvoreBEstrela pNo, int chave, Analise* analise,
                       Registro* retorno) {
  if (pNo == NULL)
    return false;

  else if (pNo->tipoNo == Externo)
    return pesquisaNoExterno(pNo, chave, analise, retorno);

  int i = 0;
  while (i < pNo->U.Interno.qtdChaves && chave >= pNo->U.Interno.chaves[i]) i++;
  analise->comparacaoPesquisa += i;

  if (chave >= pNo->U.Interno.chaves[i])
    return pesquisaNoInterno(
        pNo->U.Interno.apontadores[pNo->U.Interno.qtdChaves], chave, analise,
        retorno);

  return pesquisaNoInterno(pNo->U.Interno.apontadores[i], chave, analise,
                           retorno);
}

Registro arvoreBEstrela(Analise* analise, int chave, short* achou,
                        FILE* arquivo, int quantidade) {
  Registro registroEncontrado;
  bool valido;
  struct timespec inicio, fim;

  NoU* no = criaNo(Externo);

  clock_gettime(CLOCK_MONOTONIC, &inicio);
  int i = 0;
  while ((fread(&registroEncontrado, sizeof(Registro), 1, arquivo) == 1) &&
         i < quantidade) {
    i++;
    arvoreInsere(&no, registroEncontrado, analise);
  }
  analise->transferenciaInsercao = i;
  clock_gettime(CLOCK_MONOTONIC, &fim);
  analise->tempoInsere = (fim.tv_sec - inicio.tv_sec) * 1e9 + (fim.tv_nsec - inicio.tv_nsec);

  registroEncontrado.chave = chave;
  clock_gettime(CLOCK_MONOTONIC, &inicio);
  if (no->tipoNo == Interno)
    valido = pesquisaNoInterno(no, chave, analise, &registroEncontrado);
  else if (no->tipoNo == Externo)
    valido = pesquisaNoExterno(no, chave, analise, &registroEncontrado);
  clock_gettime(CLOCK_MONOTONIC, &fim);
  analise->tempoPesquisa = (fim.tv_sec - inicio.tv_sec) * 1e9 + (fim.tv_nsec - inicio.tv_nsec);

  if (!valido) return registroEncontrado;

  *achou = 1;
  return registroEncontrado;
}