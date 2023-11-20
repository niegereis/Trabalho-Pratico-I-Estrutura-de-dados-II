#include <stdio.h>
#include <stdlib.h>
#include "arvoreB.h"
#include <string.h>
//#include "arvoreBinaria.h"

FILE *leArquivo(int situacao){

    FILE *arquivo; 

    if (situacao == 1){ //arquivo ordenado ascendente
        arquivo = fopen("crescente.bin", "rb");
        if (arquivo){
            return arquivo;
        }
        else {
            return NULL;
        }

    }
    if (situacao == 2){ //arquivo ordenado ascendente
        arquivo = fopen("decrescente.bin", "rb");
        if (arquivo){
            return arquivo;
        }
        else {
            return NULL;
        }

    }

    if (situacao == 3){ //arquivo ordenado ascendente
        arquivo = fopen("aleatorio.bin", "rb");
        if (arquivo){
            return arquivo;
        }
        else {
            return NULL;
        }

    }

    else {
        return NULL;
    }
}

void pesquisaMetodo(int metodo, int situacao, FILE *arquivo, int quantidade, TipoRegistro reg, int operacao, Analise *analise, int chave){

    if (metodo == 1){
        //acesso sequencial
    }
    else if (metodo == 2){
        //arvore binaria
    }

    else if (metodo ==3){

        arvoreB(analise, arquivo, &reg, situacao, quantidade, operacao);
    }
    else if (metodo == 4){
        //arvore B* 
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
    int operacao;
    

    FILE* arquivo;
    Analise analise;
    TipoRegistro reg;
   
    if (argc != 5 && argc != 6){
        printf("Argumentos inválidos");
        exit(1);
    }

    quantidade = atoi(argv[2]);
    situacao = atoi(argv[3]);
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

    if (situacao != 1 || situacao != 2 || situacao !=3){
        printf("Situação inválida!\n");

        exit(1);
    }

    if (argc == 6) {
        if (strcmp(argv[5], "-P") != 0){
            printf("Argumento inválido\n");

            exit(1);
        }

        else {

            operacao = 1;
            arquivo = leArquivo(situacao);
            pesquisaMetodo(metodo, situacao, arquivo, quantidade, reg, operacao, &analise, chave);

        }

    }
    
   // pesquisaMetodo(metodo, situacao, arquivo, quantidade, Ap,  reg, &analise);
    arquivo = leArquivo(situacao);
    pesquisaMetodo(metodo, situacao, arquivo, quantidade, reg, operacao, &analise, chave);


    fclose(arquivo);
    return 0;
}

