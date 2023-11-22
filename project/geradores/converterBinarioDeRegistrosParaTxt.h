#ifndef CONVERTE_BINARIO_DE_REGISTRO_PARA_TXT
#define CONVERTE_BINARIO_DE_REGISTRO_PARA_TXT

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "../lib/compartilhado.h"

char* formatNewName(char filename[], char suffix[], char ext[]);
int converterBinarioDeRegistrosParaTxt();
char* formatNewName(char filename[], char suffix[], char ext[]);

#endif  // !CONVERTE_BINARIO_DE_REGISTRO_PARA_TXT
