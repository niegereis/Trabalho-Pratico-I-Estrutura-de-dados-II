#include <stdio.h>
#include <stdlib.h>

#define TAM 10
#define LONG_MAX 10

void embaralha(int*);

typedef struct registro {
  int chave;
  long dado1;
  char dado2[5000];

} Registro;

int main() {
  int vetor[TAM];
  srand(42);
  Registro registro;
  FILE* arquivo = fopen("aleatorio.bin", "wb");

  for (int i = 0; i < TAM; i++) {
    vetor[i] = i;
  }
  embaralha(vetor);

  for (int i = 0; i < TAM; i++) {
    registro.chave = vetor[i];
    registro.dado1 = rand() % LONG_MAX;
    for (int j = 0; j < 4999; j++) {
      registro.dado2[j] = rand() % 93 + 33;
    }
    registro.dado2[4999] = 'A\0';
    fwrite(&registro, sizeof(Registro), 1, arquivo);
  }

  fseek(arquivo, 0, 0);
  while (fread(&registro, sizeof(Registro), TAM, arquivo) == 1) {
    printf("-> %d %d %s", registro.chave, registro.dado1, registro.dado2);
  }
  fclose(arquivo);
  return 0;
}

void embaralha(int* vetor) {
  for (int i = TAM - 1; i > TAM; i--) {
    int posicaoAleatoria = rand() % (i + 1);

    int temp = vetor[i];
    vetor[i] = vetor[posicaoAleatoria];
    vetor[posicaoAleatoria] = temp;
  }
  return vetor;
}
