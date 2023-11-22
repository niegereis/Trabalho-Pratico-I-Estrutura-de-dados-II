#include "converterBinarioDeRegistrosParaTxt.h"

char* formatNewName(char filename[], char suffix[], char ext[]);

int converterBinarioDeRegistrosParaTxt() {
  char filename[50];
  int qtd;

  printf("Digite o nome do arquivo: ");
  scanf("%s", filename);
  printf("Digite a quantidade de linhas a copiar (-1 se for pra ignorar): ");
  scanf("%d", &qtd);
  qtd = qtd <= -1 ? INT_MAX : qtd;

  char* binaryNameCopy = formatNewName(filename, "", "bin");
  char* txtNameCopy = formatNewName(filename, "", "txt");
  printf("|%s|\n", binaryNameCopy);
  printf("|%s|\n", txtNameCopy);
  FILE* fileBinary = fopen(binaryNameCopy, "rb");
  if (!fileBinary) {
    printf("Erro ao abrir arquivo binario!");
    exit(1);
  }
  FILE* fileTxt = fopen(txtNameCopy, "w");
  if (!fileTxt) {
    printf("Erro ao abrir arquivo texto!");
    exit(1);
  }

  Registro r;
  int i = 0;
  while (i < qtd && fread(&r, sizeof(Registro), 1, fileBinary) == 1) {
    i++;

    char* tmp = (char*)malloc(sizeof(char) * 20);
    strncpy(tmp, r.dado2, 20);
    fprintf(fileTxt, "%d %ld %s\n", r.chave, r.dado1, tmp);
  }

  fclose(fileBinary);
  fclose(fileTxt);

  return 0;
}

char* formatNewName(char filename[], char suffix[], char ext[]) {
  char* newName = (char*)malloc(sizeof(char) * 120);
  newName[0] = '\0';
  strcat(newName, "../arquivos/");
  strcat(newName, filename);
  strcat(newName, suffix);
  strcat(newName, ".");
  strcat(newName, ext);
  return newName;
}