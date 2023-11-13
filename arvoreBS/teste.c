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

void insere(ArvoreBEstrela* a, int reg) {
  Registro r;
  r.chave = reg;
  arvoreInsere(a, r);
}

int main() {
  ArvoreBEstrela arvore = arvoreCria();
  casoTeste(&arvore);
  // insere(&arvore, 15);
  // insere(&arvore, -7);
  // insere(&arvore, 40);
  // insere(&arvore, 2);
  // insere(&arvore, 10);
  // insere(&arvore, 30);
  // insere(&arvore, -2);
  // insere(&arvore, 45);
  // insere(&arvore, 50);
  // insere(&arvore, -7);
  // insere(&arvore, 55);
  // insere(&arvore, 60);
  // insere(&arvore, 70);
  // insere(&arvore, -2);
  // insere(&arvore, 70);
  // insere(&arvore, -1);
  // insere(&arvore, -10);
  // insere(&arvore, -20);
  // insere(&arvore, -40);
  // insere(&arvore, 45);
  // insere(&arvore, 50);
  // insere(&arvore, -20);
  // insere(&arvore, -70);
  // insere(&arvore, -1);

  arvoreImprime(arvore);

  return 0;
}

void printTipoRaiz(ArvoreBEstrela arvore) {
  printf("A arvore é %s", arvore->tipoNo == Interno ? "Interna" : "Externa");
}

void casoTeste(ArvoreBEstrela* arvore) {
  Registro r;
  r.chave = 10;
  arvoreInsere(arvore, r);

  r.chave = 20;
  arvoreInsere(arvore, r);

  r.chave = 30;
  arvoreInsere(arvore, r);

  r.chave = 40;
  arvoreInsere(arvore, r);

  r.chave = 2;
  arvoreInsere(arvore, r);

  r.chave = 15;
  arvoreInsere(arvore, r);

  r.chave = 1;
  arvoreInsere(arvore, r);

  r.chave = 0;
  arvoreInsere(arvore, r);

  r.chave = 8;
  arvoreInsere(arvore, r);

  r.chave = 100;
  arvoreInsere(arvore, r);

  r.chave = -4;
  arvoreInsere(arvore, r);

  r.chave = -1;
  arvoreInsere(arvore, r);

  r.chave = -20;
  arvoreInsere(arvore, r);

  r.chave = -40;
  arvoreInsere(arvore, r);

  r.chave = 10;
  arvoreInsere(arvore, r);

  r.chave = 20;
  arvoreInsere(arvore, r);

  r.chave = 30;
  arvoreInsere(arvore, r);

  r.chave = 40;
  arvoreInsere(arvore, r);

  r.chave = 2;
  arvoreInsere(arvore, r);

  r.chave = 15;
  arvoreInsere(arvore, r);

  r.chave = 1;
  arvoreInsere(arvore, r);

  r.chave = 0;
  arvoreInsere(arvore, r);

  r.chave = 8;
  arvoreInsere(arvore, r);

  r.chave = 100;
  arvoreInsere(arvore, r);

  r.chave = -4;
  arvoreInsere(arvore, r);

  r.chave = -1;
  arvoreInsere(arvore, r);

  r.chave = -20;
  arvoreInsere(arvore, r);

  r.chave = -40;
  arvoreInsere(arvore, r);
}