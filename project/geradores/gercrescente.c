#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct registro {
  int chave;
  long dado1;
  char dado2[5000];

} Registro;

int main(int argc, char** argv) {
  srand(time(NULL));
  Registro registro;
  FILE* arquivo = fopen("../arquivos/crescente.bin", "wb");
  if (!arquivo) {
    printf("Erro ao abrir arquivo binário!");
    exit(1);
  }

  if (argc != 2) {
    printf("execute ./exe <qtd-items>");
    exit(1);
  }

  int tam = atoi(argv[1]);

  for (int i = 0; i < tam; i++) {
    registro.chave = i;
    registro.dado1 = rand() % LONG_MAX;
    for (int j = 0; j < 4999; j++) {
      registro.dado2[j] = rand() % 93 + 33;
    }
    registro.dado2[4999] = '\0';
    fwrite(&registro, sizeof(Registro), 1, arquivo);
  }
  fclose(arquivo);
  return 0;
}