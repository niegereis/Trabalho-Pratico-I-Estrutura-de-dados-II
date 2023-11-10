#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAM 10

typedef struct registro {
  int chave;
  long dado1;
  char dado2[5000];

} Registro;

int main() {
  srand(time(NULL));
  Registro registro;
  FILE* arquivo = fopen("crescendente.bin", "wb+");
  for (int i = 0; i < TAM; i++) {
    registro.chave = i;
    registro.dado1 = rand() % LONG_MAX;
    for (int j = 0; j < 4999; j++) {
      registro.dado2[j] = rand() % 93 + 33;
    }
    registro.dado2[0] = 'a';
    registro.dado2[1] = '\0';
    // registro.dado2[4999] = '\0';
    fwrite(&registro, sizeof(Registro), 1, arquivo);
  }

  printf("AQ\n");
  fseek(arquivo, 0, SEEK_SET);
  while (fread(&registro, sizeof(Registro), 1, arquivo) == 1) {
    printf("-> %d %ld %s\n", registro.chave, registro.dado1, registro.dado2);
  }

  fclose(arquivo);
  return 0;
}