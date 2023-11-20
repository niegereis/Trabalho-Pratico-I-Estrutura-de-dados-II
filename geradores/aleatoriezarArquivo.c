#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM 2000000
#define TROCAS 2000000

char* copyFile(char filename[], char suffix[], char ext[]);
char* formatNewName(char filename[], char suffix[], char ext[]);
void trocaAleatoria(FILE* file);

typedef struct registro {
  int chave;
  long dado1;
  char dado2[5000];
} Registro;

int main() {
  char filename[50];
  printf("Digite o nome do arquivo: ");
  scanf("%s", filename);

  char* binaryNameCopy = copyFile(filename, "_copy", "bin");
  char* txtNameCopy = formatNewName(filename, "_copy", "txt");

  FILE* fileBinary = fopen(binaryNameCopy, "r+b");

  for (int i = 0; i < TROCAS; i++) {
    trocaAleatoria(fileBinary);
  }
  fseek(fileBinary, 0, 0);

  FILE* fileTxt = fopen(txtNameCopy, "w+");
  Registro r;

  while (fread(&r, sizeof(Registro), 1, fileBinary) > 0) {
    char* tmp = (char*)malloc(sizeof(char) * 20);
    strncpy(tmp, r.dado2, 20);
    fprintf(fileTxt, "%d %ld %s\n", r.chave, r.dado1, tmp);
  }
  fclose(fileBinary);
  fclose(fileTxt);
}

char* formatNewName(char filename[], char suffix[], char ext[]) {
  char* newName = (char*)malloc(sizeof(char) * 100);
  strcat(newName, filename);
  strcat(newName, suffix);
  strcat(newName, ".");
  strcat(newName, ext);
  return newName;
}

char* copyFile(char filename[], char suffix[], char ext[]) {
  char command[100] = "cp ";
  strcat(command, filename);
  strcat(command, ".");
  strcat(command, ext);
  strcat(command, " ");

  char* newName = formatNewName(filename, suffix, ext);
  strcat(command, newName);
  system(command);
  printf("|%s|\n", command);
  return newName;
}

long lerPosicao(FILE* file, Registro* reg, long pos) {
  fseek(file, pos * sizeof(Registro), SEEK_SET);
  long position = ftell(file);
  fread(reg, sizeof(Registro), 1, file);
  return position;
}

void escreverPosicao(FILE* file, Registro* r, long pos) {
  fseek(file, pos, SEEK_SET);
  fwrite(r, sizeof(Registro), 1, file);
}

void trocaAleatoria(FILE* file) {
  Registro r1, r2;
  long p1 = lerPosicao(file, &r1, rand() % (TAM - 1));
  long p2 = lerPosicao(file, &r2, rand() % (TAM - 1));
  escreverPosicao(file, &r1, p2);
  escreverPosicao(file, &r2, p1);
}