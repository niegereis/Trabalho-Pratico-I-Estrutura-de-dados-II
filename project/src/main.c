#include "../lib/uniao.h"

// numero de comparacões - fazer

void incrementAnalise(Analise* global, Analise a);
void dividePor(Analise* global, int qtd);

int main(int argc, char** argv) {
  int metodo;
  int situacao;  // aleotaria, crescente ou descendente
  int chave;
  int quantidade;
  bool exibirRegistros = false;

  if (argc != 4 && argc != 5 && argc != 6) {
    printf("Argumentos inválidos\n");
    printf("./output/main <metodo> <quantidade> <situacao> <chave-buscada>");
    printf("\n<metodo>\n");
    printf("\t1 - busca sequencial binaria\n");
    printf("\t2 - arvore binaria\n");
    printf("\t3 - arvore b\n");
    printf("\t3 - arvore b*\n");
    printf("<quantidade>\n");
    printf("\tvalor inteiro\n");
    printf("<situacao>\n");
    printf("\t1 - crescente\n");
    printf("\t2 - decrescente\n");
    printf("\t3 - desordenado\n");
    printf("<chave-buscada>\n");
    printf("\tvalor inteiro\n");
    exit(1);
  }

  metodo = atoi(argv[1]);
  quantidade = atoi(argv[2]);
  situacao = atoi(argv[3]);
  if (argc >= 5) chave = atoi(argv[4]);
  if (argc == 6)
    exibirRegistros = strcmp(argv[5], "-P") == 0 || strcmp(argv[5], "-p") == 0;

  if (quantidade < 0 || quantidade > 2000000) {
    printf("Quantidade inválida\n");

    exit(1);
  }

  if (argc >= 5) {
    Analise preProcesso;
    pesquisaMetodo(metodo, situacao, chave, quantidade, exibirRegistros,
                   &preProcesso, true);
  } else {
    Analise global;
    const int qtd = 20;
    int chavesBuscadas[qtd];
    for (int i = 0; i < qtd; i++) {
      Analise preProcesso;
      chave = rand() % quantidade;
      chavesBuscadas[i] = chave;
      pesquisaMetodo(metodo, situacao, chave, quantidade, false, &preProcesso,
                     false);

      incrementAnalise(&global, preProcesso);
    }
    dividePor(&global, qtd);
    printf("\nChaves buscadas:\n");
    for (int i = 0; i < qtd; i++) {
      printf("%d ", chavesBuscadas[i]);
    }
    imprimeAnalise(global);
  }

  return 0;
}

void incrementAnalise(Analise* global, Analise a1) {
  global->comparacaoInsercao += (a1.comparacaoInsercao);
  global->comparacaoPesquisa += (a1.comparacaoPesquisa);
  global->tempoInsere += (a1.tempoInsere);
  global->tempoPesquisa += (a1.tempoPesquisa);
  global->transferenciaInsercao += (a1.transferenciaInsercao);
  global->transferenciaPesquisa += (a1.transferenciaPesquisa);
}

void dividePor(Analise* global, int qtd) {
  global->comparacaoInsercao /= (float)qtd;
  global->comparacaoPesquisa /= (float)qtd;
  global->tempoInsere /= (float)qtd;
  global->tempoPesquisa /= (float)qtd;
  global->transferenciaInsercao /= (float)qtd;
  global->transferenciaPesquisa /= (float)qtd;
}
