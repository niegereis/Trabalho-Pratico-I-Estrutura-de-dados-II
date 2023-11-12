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
  Registro ultimoRegistro = no->U.Externo.registros[qtdRegistros - 1];
  for (int i = 0; i < qtdRegistros; i++) {
    /* code */
  }
}

bool arvoreInsereRecursivo(ArvoreBEstrela* pNo, Registro registro, No* no) {
  if ((*pNo)->tipoNo == Externo) {
    if ((*pNo)->U.Externo.qtdRegistros < 2 * M) {
      insercaoOrdenada(pNo, registro, NULL);
    } else {
      Registro registroComMaiorChave;
      insercaoOrdenada(pNo, registro, &registroComMaiorChave);
      No* pNoMaiores = criaNo(Externo);
      for (int i = M; i < 2 * M; i++) {
        pNoMaiores->U.Externo.registros[i - M] = (*pNo)->U.Externo.registros[i];
        pNoMaiores->U.Externo.qtdRegistros++;
      }
      // TODO: REVISAR
      pNoMaiores->U.Externo.registros[M] = registroComMaiorChave;
      pNoMaiores->U.Externo.qtdRegistros++;

      (*pNo)->U.Externo.qtdRegistros -= pNoMaiores->U.Externo.qtdRegistros - 1;
      no = pNoMaiores;
    }
    return true;
  }
}

bool arvoreInsere(ArvoreBEstrela* pNo, Registro registro) {  // incompleto
  if (pNo == NULL) {
    *pNo = criaNo(Externo);
    (*pNo)->U.Externo.registros[0] = registro;
    (*pNo)->U.Externo.qtdRegistros++;
    return true;
  }

  if ((*pNo)->tipoNo == Externo) {
    No* novoNoCriado;
    arvoreInsereRecursivo(pNo, registro, novoNoCriado);
    int chaveQueVaiSubir = novoNoCriado->U.Externo.registros[0].chave;
    No* novoNoInterno = criaNo(Interno);
    novoNoInterno->U.Interno.chaves[0] = chaveQueVaiSubir;
    novoNoInterno->U.Interno.apontadores[0] = (*pNo);
    novoNoInterno->U.Interno.apontadores[1] = novoNoCriado;
    (*pNo) = novoNoInterno;
  }
  // Se nó for interno
  // Caminhar até o nó externo e voltar atualizando os ponteiros
}

bool arvorePesquisa(ArvoreBEstrela pNo, int chave, Registro* registro) {
  return true;
}

bool arvoreImprime(ArvoreBEstrela pNo) { return true; }