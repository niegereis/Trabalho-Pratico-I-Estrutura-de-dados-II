#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <fstream>
#include <iostream>

#define TAM 5

void copyFile(char filename[], char suffix[], char ext[]);

typedef struct registro {
  int chave;
  long dado1;
  char dado2[5000];
} Registro;

using namespace std;

int main() {
  char filename[50];
  cout << ("Digite o nome do arquivo: ");
  scanf("%s", filename);

  strcat(filename, ".bin");
  FILE* file = fopen(filename, "rb");

  Registro reg;
  printf("Dados do arquivo:\n");
  while (fread(&reg, sizeof(Registro), 1, file) > 0) {
    char* tmp = (char*)malloc(sizeof(char) * 20);
    strncpy(tmp, reg.dado2, 20);
    printf("\t%d %ld %s\n", reg.chave, reg.dado1, tmp);
  }
}