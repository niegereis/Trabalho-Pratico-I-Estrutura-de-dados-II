#include "../lib/uniao.h"

void analiseInicia(Analise* analise){
    analise->comparacaoInsercao = 0;
    analise->comparacaoPesquisa = 0;
    analise->transferenciaInsercao = 0;
    analise->transferenciaPesquisa = 0;
}

void imprimeRegistro(Registro reg){
    printf("Registro:\n\tChave: %d\n\tDado 1: %ld\n\tDado 2: [PLACEHOLDER]", reg.chave, reg.dado1);
}

void imprimeAnalise(Analise an){
    printf("\nInserção:\n\tComparações: %d\n\tTransferências: %d\n\tTempo(em nanosegundos): %ld", an.comparacaoInsercao, an.transferenciaInsercao, an.tempoInsere);
    printf("\nPesquisa:\n\tComparações: %d\n\tTransferências: %d\n\tTempo(em nanosegundos): %ld\n", an.comparacaoPesquisa, an.transferenciaPesquisa, an.tempoPesquisa);
}


void pesquisaMetodo(int metodo, int situacao, int chave, int quantidade){
    Analise analise;
    analiseInicia(&analise);
    Registro encontrado;
    short achou = 0;
    FILE* arquivo;


    switch (situacao){
    case 1:
         arquivo = fopen("./arquivos/crescente.bin", "r+b");
            
        break;

    case 2:
         arquivo = fopen("./arquivos/decrescente.bin", "r+b");
        break;

    case 3:
         arquivo = fopen("./arquivos/aleatorio.bin", "r+b");
         break;

    default:
        printf("Invalido\n");
        return;
    }

    if(arquivo == NULL){
        perror("Não foi possível abrir o arquivo.\n");
        return;
    }
    

    switch (metodo){
    case 1://sequencial
        encontrado = acessoSequencialIndexado(&analise, chave, &achou, arquivo, quantidade);
        printf("   %d   ", achou);
        break;

    case 2://arvore binaria
        encontrado = arvoreBinaria(&analise, chave, &achou, arquivo, quantidade);
        break;

    case 3://arvore b
        encontrado = arvoreB(&analise, chave, &achou, arquivo, quantidade);
        break;

    case 4://arvore b*
        encontrado = arvoreBEstrela(&analise, chave, &achou, arquivo, quantidade);
        break;

    
    default:
        printf("Invalido\n");
        break;
    }

    fclose(arquivo);


    if(achou == 1){
        imprimeRegistro(encontrado);
        imprimeAnalise(analise);
    }
    else printf("nope\n");
}