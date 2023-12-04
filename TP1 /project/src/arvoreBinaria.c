#include "arvoreBinaria.h"

bool ArvoreBinariaPesquisa(FILE* arvoreBinaria, long chave, Registro* r, Analise* analise) {
  // Reposiciona o ponteiro do arquivo no início
  fseek(arvoreBinaria, 0, 0);

  // Declaração de uma estrutura NoExt para armazenar nós da árvore
  NoExt no;

  // Loop enquanto a leitura do nó for bem-sucedida
  while (fread(&no, sizeof(NoExt), 1, arvoreBinaria) == 1) {
    analise->transferenciaPesquisa++;

    // Compara a chave do nó com a chave desejada
    analise->comparacaoPesquisa++;
    if (chave != no.registro.chave) {
      // Se a chave desejada for maior que a chave do nó
      analise->comparacaoPesquisa++;
      if ((chave > no.registro.chave)) {
        // Reposiciona o ponteiro do arquivo no próximo nó à direita
        fseek(arvoreBinaria, (sizeof(NoExt) * (no.pDir - 1)), 0);
        (*r) = no.registro; // Atualiza o registro com o nó atual
      }

      // Se a chave desejada for menor que a chave do nó
      analise->comparacaoPesquisa++;
      if ((chave < no.registro.chave)) {
        // Reposiciona o ponteiro do arquivo no próximo nó à esquerda
        fseek(arvoreBinaria, (sizeof(NoExt) * (no.pEsq - 1)), 0);
        (*r) = no.registro; // Atualiza o registro com o nó atual
      }
    } else {
      // Se a chave desejada for igual à chave do nó, encontrou o valor
      (*r) = no.registro;
      return true;
    }
  }

  // Se o loop terminar e não encontrar a chave, exibe uma mensagem e retorna falso
  printf("O valor não se encontra no arquivo.\n");
  return 0;
}

void ArvoreBinariaCria(FILE* arq, FILE* arvoreBinaria, int quantidade, Analise* analise) {
  long j = 1; // Variável para atribuir valores aos ponteiros dos nós
  NoExt noComRegistro; // Nó que contém o registro a ser inserido na árvore
  NoExt noQuePercorre; // Nó que percorre a árvore durante a inserção
  Registro registro; // Registro lido do arquivo original
  int escreveu = false; // Flag para indicar se o registro foi inserido
  long i = 0; // Contador de registros lidos

  // Loop para inserir cada registro na árvore
  while (i < quantidade && (fread(&registro, sizeof(Registro), 1, arq) == 1)) {
    analise->transferenciaInsercao++;
    noComRegistro.registro = registro;
    noComRegistro.pDir = -1;
    noComRegistro.pEsq = -1;
    escreveu = false;

    fseek(arvoreBinaria, 0, SEEK_SET);

    // Loop para percorrer a árvore e inserir o registro
    while (escreveu == 0) {
      int qtdLida;

      analise->transferenciaInsercao++;
      if ((qtdLida = fread(&noQuePercorre, sizeof(NoExt), 1, arvoreBinaria)) == 1) {
        analise->comparacaoInsercao++;
        if (noQuePercorre.registro.chave == noComRegistro.registro.chave)
          continue;

        analise->comparacaoInsercao++;
        if (noComRegistro.registro.chave < noQuePercorre.registro.chave) {
          analise->comparacaoInsercao++;
          if (noQuePercorre.pEsq == -1) {
            // Se não houver filho à esquerda, insere o registro à esquerda
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
        } else {
          analise->comparacaoInsercao++;
          if (noQuePercorre.pDir == -1) {
            // Se não houver filho à direita, insere o registro à direita
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
        // Se não houver mais nós para ler, insere o registro no final do arquivo
        fwrite(&noComRegistro, sizeof(NoExt), 1, arvoreBinaria);
        j++;
        escreveu = true;
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
  analise->tempoInsere = (fim.tv_sec - inicio.tv_sec) * 1e9 + (fim.tv_nsec - inicio.tv_nsec);

  clock_gettime(CLOCK_MONOTONIC, &inicio);
  *achou = ArvoreBinariaPesquisa(arvoreBinaria, chave, &registro, analise);
  clock_gettime(CLOCK_MONOTONIC, &fim);
  analise->tempoPesquisa = (fim.tv_sec - inicio.tv_sec) * 1e9 + (fim.tv_nsec - inicio.tv_nsec);

  fclose(arvoreBinaria);

  return registro;
}

