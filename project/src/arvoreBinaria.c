#include "arvoreBinaria.h"

bool ArvoreBinariaPesquisa(FILE* arvoreBinaria, long chave, Registro* r,
                           Analise* analise) {
  fseek(arvoreBinaria, 0, 0);

  int i = 0;
  NoExt no;
  while (fread(&no, sizeof(NoExt), 1, arvoreBinaria) == 1) {
    analise->transferenciaPesquisa++;

    analise->comparacaoPesquisa++;
    if (chave != no.registro.chave) {
      analise->comparacaoPesquisa++;
      if ((chave > no.registro.chave)) {
        fseek(arvoreBinaria, (sizeof(NoExt) * (no.pDir - 1)), 0);
        i = no.pDir;
        (*r) = no.registro;
      }

      analise->comparacaoPesquisa++;
      if ((chave < no.registro.chave)) {
        fseek(arvoreBinaria, (sizeof(NoExt) * (no.pEsq - 1)), 0);
        i = no.pEsq;
        (*r) = no.registro;
      }
    } else {
      (*r) = no.registro;
      return true;
    }
  }

  printf("O valor não se encontra no arquivo.\n");
  return 0;
}

void ArvoreBinariaCria(FILE* arq, FILE* arvoreBinaria, int quantidade,
                       Analise* analise) {
  long j = 1;
  NoExt noComRegistro;
  NoExt noQuePercorre;
  Registro registro;
  int escreveu = false;
  long i = 0;

  while (i < quantidade && (fread(&registro, sizeof(Registro), 1, arq) == 1)) {
    analise->transferenciaInsercao++;
    noComRegistro.registro = registro;
    noComRegistro.pDir = -1;
    noComRegistro.pEsq = -1;
    escreveu = false;

    fseek(arvoreBinaria, 0, SEEK_SET);

    while (escreveu == 0) {
      int qtdLida;

      analise->transferenciaInsercao++;
      if ((qtdLida = fread(&noQuePercorre, sizeof(NoExt), 1, arvoreBinaria)) ==
          1) {
        analise->comparacaoInsercao++;
        if (noQuePercorre.registro.chave == noComRegistro.registro.chave)
          continue;

        analise->comparacaoInsercao++;
        if (noComRegistro.registro.chave < noQuePercorre.registro.chave) {
          analise->comparacaoInsercao++;
          if (noQuePercorre.pEsq == -1) {
            noQuePercorre.pEsq = j;
            j++;
            fseek(arvoreBinaria, (sizeof(NoExt) * -1), 1);
            fwrite(&noQuePercorre, sizeof(NoExt), 1, arvoreBinaria);

            fseek(arvoreBinaria, 0, SEEK_END);
            fwrite(&noComRegistro, sizeof(NoExt), 1, arvoreBinaria);

            escreveu = true;
          } else {
            fseek(arvoreBinaria, 0, SEEK_SET);
            fseek(arvoreBinaria, (sizeof(NoExt) * (noQuePercorre.pEsq - 1)), 0);
          }
        }
        analise->comparacaoInsercao++;
        if (noComRegistro.registro.chave > noQuePercorre.registro.chave) {
          analise->comparacaoInsercao++;
          if (noQuePercorre.pDir == -1) {
            noQuePercorre.pDir = j;
            j++;
            fseek(arvoreBinaria, (sizeof(NoExt) * -1), 1);
            fwrite(&noQuePercorre, sizeof(NoExt), 1, arvoreBinaria);

            fseek(arvoreBinaria, 0, SEEK_END);
            fwrite(&noComRegistro, sizeof(NoExt), 1, arvoreBinaria);

            escreveu = true;

          } else {
            fseek(arvoreBinaria, 0, SEEK_SET);
            fseek(arvoreBinaria, (sizeof(NoExt) * (noQuePercorre.pDir - 1)), 0);
          }
        }
      } else {
        fwrite(&noComRegistro, sizeof(NoExt), 1, arvoreBinaria);
        j++;
        escreveu = 1;
      }
    }
    i++;
  }
}

Registro arvoreBinaria(Analise* analise, int chave, short* achou, FILE* arquivo,
                       int quantidade) {
  Registro registro;

  struct timespec inicio, fim;
  FILE* arvoreBinaria = fopen("./arquivos/arvoreBinaria.bin", "w+b");
  if (arvoreBinaria == NULL) {
    printf("Erro ao abrir os arquivos.\n");
    return registro;
  }

  clock_gettime(CLOCK_MONOTONIC, &inicio);
  ArvoreBinariaCria(arquivo, arvoreBinaria, quantidade, analise);
  clock_gettime(CLOCK_MONOTONIC, &fim);
  analise->tempoInsere = fim.tv_nsec - inicio.tv_nsec;

  clock_gettime(CLOCK_MONOTONIC, &inicio);
  *achou = ArvoreBinariaPesquisa(arvoreBinaria, chave, &registro, analise);
  clock_gettime(CLOCK_MONOTONIC, &fim);
  analise->tempoPesquisa = fim.tv_nsec - inicio.tv_nsec;

  fclose(arvoreBinaria);

  return registro;
}