#include "../lib/uniao.h"

// numero de comparacões - fazer

int main(int argc, char **argv) {
  int metodo;
  int situacao;  // aleotaria, crescente ou descendente
  int chave;
  int quantidade;
  bool exibirRegistros;

  if (argc != 5 && argc != 6) {
    printf("Argumentos inválidos");
    exit(1);
  }

  metodo = atoi(argv[1]);
  quantidade = atoi(argv[2]);
  situacao = atoi(argv[3]);
  chave = atoi(argv[4]);
  exibirRegistros = strcmp(argv[5], "-P") == 0 || strcmp(argv[5], "-p") == 0;

  if (quantidade < 0 || quantidade > 2000000) {
    printf("Quantidade inválida\n");

    exit(1);
  }

  pesquisaMetodo(metodo, situacao, chave, quantidade, exibirRegistros);

  return 0;
}
