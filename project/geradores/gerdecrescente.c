#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<limits.h>

#define TAM 200

typedef struct registro{
    int chave;
    long dado1;
    char dado2[5000];
    
}Registro;

int main (){
    srand(time(NULL));
    Registro registro;
    FILE* arquivo = fopen ("../arquivos/decrescente.bin", "wb");
    for(int i = TAM-1; i >= 0; i--){
        registro.chave = i;
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