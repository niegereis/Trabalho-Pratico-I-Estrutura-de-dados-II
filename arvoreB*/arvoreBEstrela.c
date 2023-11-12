#include "arvoreBEstrela.h"

No* ArvorePercorre(ArvoreBEstrela, int, int*);
bool insereRegistro(No*, Registro);

ArvoreBEstrela arvoreCria() {  // OK
  ArvoreBEstrela arvore = malloc(sizeof(ArvoreBEstrela));
  arvore = NULL;
  return arvore;
}

bool arvoreInsere(ArvoreBEstrela* pNo, Registro registro) {  // incompleto
  if (pNo == NULL) {
    *pNo = criaNo(Externo);
    (*pNo)->U.Externo.registros[0] = registro;
    (*pNo)->U.Externo.qtdRegistros++;
    return true;
  }

  else {
    int nivel = 0;  // guarda o nível do noInsercao
    No* noInsercao = ArvorePercorre(pNo, registro.chave, &nivel);
    bool
  }

  return true;
}

No* criaNo(TipoDoNo tipo) {
  No* no = (No*)malloc(sizeof(No));
  no->tipoNo = tipo;

  if (tipo == Interno)
    no->U.Interno.qtdChaves = 0;

  else  // se tipo for igual a Externo
    no->U.Externo.qtdRegistros = 0;

  return no;
}

// retorna o nó externo em que o registro procurado provavelmente está
No* ArvorePercorre(ArvoreBEstrela pNo, int chave, int* nivel) {  // OK
  if (pNo->tipoNo == Externo) return pNo;
  *nivel++;

  for (int i = 0; i < pNo->U.Interno.qtdChaves; i++) {
    if (pNo->U.Interno.chaves[i] > chave)
      return ArvorePercorre(pNo->U.Interno.apontadores[i], chave, nivel++);
    else
      return ArvorePercorre(
          pNo->U.Interno.apontadores[pNo->U.Interno.qtdChaves],
          chave);  // se a chave for maior do que qualquer uma do nó, ela vai
                   // para o ultimo ponteiro do vetor
  }
}

bool insereRegistro(No* pNo, Registro registro) {  // incompleto
  for (int i = 0; i < pNo->U.Externo.qtdRegistros; i++) {
    if (pNo->U.Externo.registros[i].chave < registro.chave) }
}

bool arvorePesquisa(ArvoreBEstrela pNo, int chave, Registro* registro) {  // OK
  if (pNo = NULL) return false;
  int nivel;
  No* noPesquisado = ArvorePercorre(pNo, chave, &nivel);
  for (int i = 0; i < noPesquisado->U.Externo.qtdRegistros; i++) {
    if (noPesquisado->U.Externo.registros[i].chave == chave) {
      registro = &noPesquisado->U.Externo.registros[i];
      return true;
    }
  }
  return false;
}
