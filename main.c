#include <stdio.h>
#include <stdlib.h>
#include "arvoreB/arvoreB.h"


int pesquisaMetodo(int metodo, int situacao, FILE *arquivo, int quantidade, TipoApontador Ap, TipoRegistro reg){

    if (metodo == 1){
        /*acesso sequencial*/
    }
    else if (metodo == 2){
        /*arvore binaria*/
    }

    else if (metodo ==3){

        leArquivo(arquivo, situacao, quantidade, Ap, reg);
        /*arvore B*/
    }
    else if (metodo == 4){
        /* arvore B* */
    }
    else {
        printf("Invalido\n");
    }
    
}

// numero de comparacões - fazer 

int main(int argc, char *argv[]){

    int metodo;
    int situacao; // aleotaria, crescente ou descendente 
    int chave;
    int quantidade;

    if (argc != 5 || argc != 6){
        printf("Argumentos inválidos");
        exit(1);
    }

    quantidade = atoi(argv[2]);
    metodo = atoi(argv[3]);
    chave = atoi(argv[4]);
    metodo = atoi(argv[1]);

    if (metodo < 1 || metodo > 4){
        printf("Número de métodos inválido\n");

        exit(1);
    }

    if (quantidade < 0 || quantidade > 2000000){

        printf("Quantidade inválida\n");

        exit(1);

    }

    if (situacao != 2 || situacao != 3 || situacao !=1){
        printf("Situação inválida!\n");

        exit(1);
    }
    
    FILE *arquivo;

    //arquivo = arquivoSituacao(situacao);


    free(arquivo);
    return 0;
}

