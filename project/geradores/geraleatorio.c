#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAM 200

typedef struct registro {
  int chave;
  long dado1;
  char dado2[5000];

} Registro;

int main() {
  int vetor[TAM];
  srand(42);
  Registro registro;

  FILE* arquivo = fopen("../arquivos/aleatorio.bin", "wb");
  if (!arquivo) {
    printf("Erro ao abrir arquivo binário!");
    exit(1);
  }

  for (int i = 0; i < TAM; i++) {
    vetor[i] = i;
  }

  // Embaralha o vetor
  for (int i = TAM - 1; i >= 0; i--) {
    int posicaoAleatoria = rand() % (i + 1);

    int temp = vetor[i];
    vetor[i] = vetor[posicaoAleatoria];
    vetor[posicaoAleatoria] = temp;
  }

  for (int i = 0; i < TAM; i++) {
    registro.chave = vetor[i];
    registro.dado1 = rand() % LONG_MAX;
    for (int j = 0; j < 4999; j++) {
      registro.dado2[j] = rand() % 93 + 33;
    }
    registro.dado2[4999] = '\0';
    fwrite(&registro, sizeof(Registro), 1, arquivo);
  }

  fseek(arquivo, 0, 0);
  while (fread(&registro, sizeof(Registro), 1, arquivo) == 1) {
    printf("-> %d %ld %s", registro.chave, registro.dado1, registro.dado2);
  }
  fclose(arquivo);
  return 0;
}
