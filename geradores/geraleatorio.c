#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<limits.h>

#define TAM 2000000

void embaralha(int*);

typedef struct registro{
    int chave;
    long dado1;
    char dado2[5000];
    
}Registro;

int main (){
    int vetor[TAM];
    srand(42);
    Registro registro;
    FILE* arquivo = fopen ("aleatorio.bin", "wb");

    for(int i = 0; i<TAM; i++){
        vetor[i] = i;
    }
    embaralha(vetor);

    for(int i = 0; i < TAM; i++){
        registro.chave = vetor[i];
        registro.dado1 = rand() % LONG_MAX;
        for(int j = 0; j < 4999; j++){
            registro.dado2[j] = rand() % 93 + 33;
        }
        registro.dado2[4999] = '\0';
        fwrite(&registro, sizeof(Registro), 1, arquivo);
    }
    fclose(arquivo);
    return 0;
}

void embaralha(int* vetor) {
    for (int i = TAM - 1; i > TAM; i--) {
        int posicaoAleatoria = rand() % (i + 1);
        
        // Troque os elementos nas posições i e j
        int temp = vetor[i];
        vetor[i] = vetor[posicaoAleatoria];
        vetor[posicaoAleatoria] = temp;
    }
    return vetor;
}