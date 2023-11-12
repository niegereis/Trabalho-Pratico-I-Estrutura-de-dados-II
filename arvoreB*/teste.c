#include "arvoreBEstrela.h"

void printNo(No* no, Registro* overflow) {
  for (int i = 0; i < (*no).U.Externo.qtdRegistros; i++) {
    printf("%d ", (*no).U.Externo.registros[i].chave);
  }
  printf("\nOverflow: %p %d\n", &overflow,
         overflow != NULL ? overflow->chave : -5);
}

void testeInsercaoRegistroOrdenada() {
  No* no = criaNo(Externo);
  Registro overflow;

  Registro registro;
  registro.chave = 10;
  insercaoOrdenada(no, registro, &overflow);
  printNo(no, &overflow);

  registro.chave = 15;
  insercaoOrdenada(no, registro, &overflow);
  printNo(no, &overflow);

  registro.chave = 2;
  insercaoOrdenada(no, registro, &overflow);
  printNo(no, &overflow);

  registro.chave = 0;
  insercaoOrdenada(no, registro, &overflow);
  printNo(no, &overflow);

  registro.chave = -1;
  insercaoOrdenada(no, registro, &overflow);
  printNo(no, &overflow);

  return 0;
}

int main() {
  No* no = criaNo(Interno);
  No* filho1 = criaNo(Externo);
}
