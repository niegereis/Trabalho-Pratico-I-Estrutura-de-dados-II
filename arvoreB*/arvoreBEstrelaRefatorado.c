#include "arvoreBEstrela.h"

ArvoreBEstrela arvoreCria() {  // OK
  ArvoreBEstrela arvore = malloc(sizeof(ArvoreBEstrela));
  arvore = NULL;
  return arvore;
}

No* criaNo(TipoDoNo tipo) {
  No* no = (No*)malloc(sizeof(No));
  no->tipoNo = tipo;

  if (tipo == Interno)

    no->U.Interno.qtdChaves = 0;
  else
    no->U.Externo.qtdRegistros = 0;

  return no;
}

No* ArvorePercorre(ArvoreBEstrela pNo, int chave, int* nivel) {
  if (pNo->tipoNo == Externo) return pNo;

  for (int i = 0; i < pNo->U.Interno.qtdChaves + 1; i++) {
    if (i == pNo->U.Interno.qtdChaves + 1 || pNo->U.Interno.chaves[i] > chave)
      // pq do nivel?
      return ArvorePercorre(pNo->U.Interno.apontadores[i], chave, nivel++);
  }
}

void insercaoOrdenada(No* no, Registro registro, Registro* overflow) {
  int qtdRegistros = no->U.Externo.qtdRegistros;
  bool vetorCheio = qtdRegistros == 2 * M;
  Registro* registros = no->U.Externo.registros;

  if (vetorCheio) {
    bool registroMaiorQueUltimaChave =
        registro.chave > registros[qtdRegistros - 1].chave;
    if (registroMaiorQueUltimaChave) {
      (*overflow) = registro;
      return;
    }
  }

  if (qtdRegistros == 0) {
    registros[0] = registro;
    no->U.Externo.qtdRegistros++;
    return;
  }

  if (qtdRegistros == 1) {
    bool registroMaiorQueUltimaChave =
        registro.chave > registros[qtdRegistros - 1].chave;
    if (registroMaiorQueUltimaChave)
      registros[1] = registro;
    else {
      registros[1] = registros[0];
      registros[0] = registro;
    }
    no->U.Externo.qtdRegistros++;
    return;
  }

  Registro ultimoRegistro = registros[qtdRegistros - 1];
  int i;
  for (i = qtdRegistros - 2; i >= 0; i--) {
    if (registro.chave < registros[i].chave) {
      registros[i + 1] = registros[i];
    }
  }
  registros[i + 1] = registro;

  if (vetorCheio)
    (*overflow) = ultimoRegistro;
  else {
    registros[no->U.Externo.qtdRegistros] = ultimoRegistro;
    no->U.Externo.qtdRegistros++;
  }
}

bool arvoreInsereNaFolha(ArvoreBEstrela* pNo, Registro registro, No* no) {
  if ((*pNo)->tipoNo == Externo) {
    if ((*pNo)->U.Externo.qtdRegistros < 2 * M) {
      insercaoOrdenada(*pNo, registro, NULL);
    } else {
      Registro registroComMaiorChave;
      insercaoOrdenada(*pNo, registro, &registroComMaiorChave);
      No* pNoMaiores = criaNo(Externo);
      for (int i = M; i < 2 * M; i++) {
        pNoMaiores->U.Externo.registros[i - M] = (*pNo)->U.Externo.registros[i];
        pNoMaiores->U.Externo.qtdRegistros++;
      }

      pNoMaiores->U.Externo.registros[M] = registroComMaiorChave;
      pNoMaiores->U.Externo.qtdRegistros++;

      (*pNo)->U.Externo.qtdRegistros -= pNoMaiores->U.Externo.qtdRegistros - 1;
      no = pNoMaiores;
    }
    return true;
  }
}

bool arvoreInsere(ArvoreBEstrela* arvore, Registro registro,
                  No* noCriado) {  // incompleto
  if (arvore == NULL) {
    *arvore = criaNo(Externo);
    (*arvore)->U.Externo.registros[0] = registro;
    (*arvore)->U.Externo.qtdRegistros++;
    return true;
  }

  if ((*arvore)->tipoNo == Externo) {
    No* novoNoCriado;
    arvoreInsereNaFolha(arvore, registro, novoNoCriado);
    if (novoNoCriado != NULL) {
      int chaveQueVaiSubir = novoNoCriado->U.Externo.registros[0].chave;
      No* novoNoInterno = criaNo(Interno);
      novoNoInterno->U.Interno.chaves[0] = chaveQueVaiSubir;
      novoNoInterno->U.Interno.apontadores[0] = (*arvore);
      novoNoInterno->U.Interno.apontadores[1] = novoNoCriado;
      (*arvore) = novoNoInterno;
    }
  }
  // Se nó for interno
  // Caminhar até o nó externo e voltar atualizando os ponteiros
  else {
    int indice;
    for (indice = 0; indice < (*arvore)->U.Interno.qtdChaves; indice++) {
      if (registro.chave < (*arvore)->U.Interno.chaves[indice]) {
        break;
      }
    }
    arvoreInsere(&(*arvore)->U.Interno.apontadores[indice], registro);
  }
}

bool arvorePesquisa(ArvoreBEstrela pNo, int chave, Registro* registro) {
  return true;
}

bool arvoreImprime(ArvoreBEstrela pNo) { return true; }