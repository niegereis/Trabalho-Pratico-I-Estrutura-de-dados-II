#include "arvoreBEstrela.h"

ArvoreBEstrela arvoreCria() {  // OK
  ArvoreBEstrela arvore = NULL;
  return arvore;
}

bool ehExterno(No* no) { return no->tipoNo == Externo; }
bool ehInterno(No* no) { return no->tipoNo == Interno; }

No* criaNo(TipoDoNo tipo) {
  No* no = (No*)malloc(sizeof(No));
  no->tipoNo = tipo;

  if (tipo == Interno)

    no->U.Interno.qtdChaves = 0;
  else
    no->U.Externo.qtdRegistros = 0;

  return no;
}

void insereRegistroOrdenado(No* no, Registro registro, Registro* overflow) {
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

bool noCheio(No* no) {
  return no->tipoNo == Interno ? no->U.Interno.qtdChaves >= 2 * M
                               : no->U.Externo.qtdRegistros >= 2 * M;
}

bool arvoreInsereNaFolha(No* pNo, Registro registro, No** noExternoMaiores) {
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
}

int obtemChavePrimeiroElemento(No* n) {
  return n->tipoNo == Interno ? n->U.Interno.chaves[0]
                              : n->U.Externo.registros[0].chave;
}

int obtemQuantidadeElementosDoNo(No* n) {
  return n->tipoNo == Interno ? n->U.Interno.qtdChaves
                              : n->U.Externo.qtdRegistros;
}

int* obterChaves(No* no) { return no->U.Interno.chaves; }

No** obterApontadores(No* no) { return no->U.Interno.apontadores; }

bool arvoreInsereRecursiva(No** no, Registro registro, No** noMaiores,
                           int* chaveS) {
  if ((*no)->tipoNo == Externo) {
    return arvoreInsereNaFolha(*no, registro, noMaiores);
  }

  int i, qtdNoAtual = obtemQuantidadeElementosDoNo(*no);
  for (i = 0; i < qtdNoAtual; i++) {
    if (registro.chave < (*no)->U.Interno.chaves[i]) {
      break;
    }
  }
  arvoreInsereRecursiva(&(*no)->U.Interno.apontadores[i], registro, noMaiores,
                        chaveS);

  if ((*noMaiores) != NULL) {
    bool temEspaco = (*no)->U.Interno.qtdChaves < 2 * M;
    if (temEspaco) {
      int chaveElemQueSobe = obtemChavePrimeiroElemento(*noMaiores);
      int qtdElementosDoNo = obtemQuantidadeElementosDoNo(*no);
      int* chaves = obterChaves(*no);
      No** apontadores = obterApontadores(*no);

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
      No* apontadorDoElementoQueSobe = *noMaiores;

      int* chavesNoAtual = (*no)->U.Interno.chaves;
      int qtdElementosDoNo = obtemQuantidadeElementosDoNo(*no);

      int ultimaChaveDoNo = chavesNoAtual[qtdElementosDoNo - 1];
      No** apontadores = obterApontadores(*no);

      if (ultimaChaveDoNo > chaveElemQueSobe) {
        // troca chaves
        chavesNoAtual[qtdElementosDoNo - 1] = chaveElemQueSobe;
        chaveElemQueSobe = ultimaChaveDoNo;

        // troca nos
        No* tmp = apontadores[qtdElementosDoNo];
        apontadores[qtdElementosDoNo] = apontadorDoElementoQueSobe;
        apontadorDoElementoQueSobe = tmp;
      }
      // chaveElemQueSobe

      int ultimaChave = chavesNoAtual[qtdElementosDoNo - 1];
      No* ultimoApontador = apontadores[qtdElementosDoNo];

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

      No* novoNo = criaNo(Interno);
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
}

bool arvoreInsere(ArvoreBEstrela* arvore, Registro registro) {  // incompleto
  if (*arvore == NULL) {
    *arvore = criaNo(Externo);
    (*arvore)->U.Externo.registros[0] = registro;
    (*arvore)->U.Externo.qtdRegistros++;
    return true;
  }

  No* novoNoMaiores = NULL;
  int chaveS;
  arvoreInsereRecursiva(arvore, registro, &novoNoMaiores, &chaveS);
  if (novoNoMaiores != NULL) {
    if (ehExterno(novoNoMaiores)) {
      No* no = criaNo(Interno);
      int chavePrimeiroElem = obtemChavePrimeiroElemento(novoNoMaiores);

      no->U.Interno.chaves[0] = chavePrimeiroElem;
      no->U.Interno.qtdChaves++;
      no->U.Interno.apontadores[0] = *arvore;
      no->U.Interno.apontadores[1] = novoNoMaiores;
      (*arvore) = no;
    } else {
      No* no = criaNo(Interno);
      no->U.Interno.chaves[0] = chaveS;
      no->U.Interno.qtdChaves++;
      no->U.Interno.apontadores[0] = *arvore;
      no->U.Interno.apontadores[1] = novoNoMaiores;
      (*arvore) = no;
    }
  }
}
