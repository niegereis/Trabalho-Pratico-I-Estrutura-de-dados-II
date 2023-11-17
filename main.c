#include <stdio.h>
#include <stdlib.h>

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
    


    return 0;
}