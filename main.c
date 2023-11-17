#include <stdio.h>
#include <stdlib.h>

// numero de comparações - fazer 

int main(int argc, char *argv[]){

    int metodo;
    int situacao;
    int chave;
    int quantidade;

    if (argc != 5 && argc != 6){
        printf("Argumentos inválidos");
        exit(1);
    }

    quantidade = atoi(argv[2]);
    metodo = atoi(argv[3]);
    chave = atoi(argv[4]);
    metodo = atoi(argv[0]);

    if (metodo < 1 || metodo > 4){
        printf("Número de métodos inválido");
    }

    if (quantidade < 0 || quantidade > 2000000){

        printf("Quantidade inválida");

    }

    if (situacao != 2 || situacao != 3 || situacao !=1){
        printf("Situação inválida!");
    }
    


    return 0;
}