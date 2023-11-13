#include "arvoreBEstrela.h"

void printNo(No* no, Registro* overflow) {
  for (int i = 0; i < (*no).U.Externo.qtdRegistros; i++) {
    printf("%d ", (*no).U.Externo.registros[i].chave);
  }
  printf("\nOverflow: %p %d\n", &overflow,
         overflow != NULL ? overflow->chave : -1);
}

void testeInsercaoRegistroOrdenada() {
  No* no = criaNo(Externo);
  Registro overflow;

  Registro registro;
  registro.chave = 10;
  insereRegistroOrdenado(no, registro, &overflow);
  printNo(no, &overflow);
  printf("QTD: %d\n\n", no->U.Externo.qtdRegistros);

  registro.chave = 15;
  insereRegistroOrdenado(no, registro, &overflow);
  printNo(no, &overflow);
  printf("QTD: %d\n\n", no->U.Externo.qtdRegistros);

  registro.chave = 2;
  insereRegistroOrdenado(no, registro, &overflow);
  printNo(no, &overflow);
  printf("QTD: %d\n\n", no->U.Externo.qtdRegistros);

  registro.chave = 0;
  insereRegistroOrdenado(no, registro, &overflow);
  printNo(no, &overflow);
  printf("QTD: %d\n\n", no->U.Externo.qtdRegistros);

  registro.chave = -1;
  insereRegistroOrdenado(no, registro, &overflow);
  printNo(no, &overflow);
  printf("QTD: %d\n\n", no->U.Externo.qtdRegistros);
}

void printTipoRaiz(ArvoreBEstrela arvore);

int main() {
  ArvoreBEstrela arvore = arvoreCria();

  Registro r;
  r.chave = 10;
  arvoreInsere(&arvore, r);

  r.chave = 20;
  arvoreInsere(&arvore, r);

  r.chave = 30;
  arvoreInsere(&arvore, r);

  r.chave = 40;
  arvoreInsere(&arvore, r);

  r.chave = 2;
  arvoreInsere(&arvore, r);

  r.chave = 15;
  arvoreInsere(&arvore, r);

  r.chave = 1;
  arvoreInsere(&arvore, r);

  r.chave = 0;
  arvoreInsere(&arvore, r);

  printTipoRaiz(arvore);
  return 0;
}

void printTipoRaiz(ArvoreBEstrela arvore) {
  printf("A arvore é %s", arvore->tipoNo == Interno ? "Interna" : "Externa");
}