#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
  FILE* arquivo = fopen("crescente.bin", "wb+");
  FILE* arquivoTxt = fopen("_crescente.txt", "w");

  int inseridos = 0, i = 0;
  while (inseridos < TAM) {
    registro.chave = i++;
    while ((rand() % 100) < 60) {
      i++;
    }
    registro.dado1 = rand() % LONG_MAX;
    for (int j = 0; j < 4999; j++) {
      registro.dado2[j] = rand() % 93 + 33;
    }
    registro.dado2[4999] = '\0';

    char* tmp = malloc(sizeof(char) * 20);
    fwrite(&registro, sizeof(Registro), 1, arquivo);
    strncpy(tmp, registro.dado2, 20);

    fprintf(arquivoTxt, "%d %ld %s\n", registro.chave, registro.dado1, tmp);

    inseridos++;
  }

  fseek(arquivo, 0, SEEK_SET);
  while (fread(&registro, sizeof(Registro), 1, arquivo) == 1) {
    char* tmp = malloc(sizeof(char) * 20);
    strncpy(tmp, registro.dado2, 20);
    printf("-> %d %ld %s\n", registro.chave, registro.dado1, tmp);
  }

  fclose(arquivo);
  return 0;
}