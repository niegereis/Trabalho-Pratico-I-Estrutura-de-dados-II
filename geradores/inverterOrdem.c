#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
char* formatNewName(char filename[], char suffix[], char ext[]);

typedef struct registro {
  int chave;
  long dado1;
  char dado2[5000];
} Registro;

int main() {
  char filename[50];

  printf("Digite o nome do arquivo: ");
  scanf("%s", filename);

  char* binaryNameCopy = formatNewName(filename, "_decrescente", "bin");
  char* txtNameCopy = formatNewName(filename, "_decrescente", "txt");

  strcat(filename, ".bin");
  FILE* fileBinary = fopen(filename, "rb");
  long initialPos = ftell(fileBinary);
  fseek(fileBinary, 0, SEEK_END);
  long finalPos = ftell(fileBinary);

  long qtdItems = ceil((finalPos - initialPos) / (float)sizeof(Registro));
  fseek(fileBinary, -sizeof(Registro) * (qtdItems < 10000 ? qtdItems : 10000),
        SEEK_END);
  FILE* decrecenteBinaryFile = fopen(binaryNameCopy, "wb");
  FILE* decrecenteTxtFile = fopen(txtNameCopy, "w");

  Registro rs[1000];
  while (ftell(fileBinary) >= initialPos) {
    int readed = fread(&rs, sizeof(Registro), 1000, fileBinary);
    if (readed == 0) break;
    printf("red: %d\n", readed);
    int qtd = readed < 1000 ? readed : 1000;

    for (int i = qtd - 1; i >= 0; i--) {
      fwrite(&rs[i], sizeof(Registro), qtd, decrecenteBinaryFile);
      char* tmp = (char*)malloc(sizeof(char) * 20);
      strncpy(tmp, rs[i].dado2, 20);
      fprintf(decrecenteTxtFile, "%d %ld %s\n", rs[i].chave, rs[i].dado1, tmp);
    }
    fseek(fileBinary, -sizeof(Registro) * qtd * 2, SEEK_CUR);
  }
  fclose(fileBinary);
  fclose(decrecenteTxtFile);
  fclose(decrecenteBinaryFile);
}

char* formatNewName(char filename[], char suffix[], char ext[]) {
  char* newName = (char*)malloc(sizeof(char) * 100);
  strcat(newName, filename);
  strcat(newName, suffix);
  strcat(newName, ".");
  strcat(newName, ext);
  return newName;
}
