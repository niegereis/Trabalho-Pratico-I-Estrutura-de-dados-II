#include "arvoreBinaria.h"

/*void Arvore_Inicia(No** pRaiz) {
    *pRaiz = NULL ;
}*/

void imprimirArvore(FILE* arvoreBinaria) {
    NoExt no;

    // Reposiciona o indicador de posição para o início do arquivo
    fseek(arvoreBinaria, 0, SEEK_SET);

    // Lê cada nó e imprime a chave
    while (fread(&no, sizeof(NoExt), 1, arvoreBinaria) == 1) {
        printf("Esquerda:%d Chave: %ld Direita:%d\n", no.pEsq, no.item.chave, no.pDir);
        // Você pode imprimir outros campos de 'no' conforme necessário
    }
}


void PesquisaExterna(FILE* arq, FILE* arvoreBinaria, int situacao, int quantidade) {

    if (arvoreBinaria == NULL || arq == NULL) {
        printf("Erro ao abrir os arquivos.\n");
        return; // Ou tome a ação apropriada em caso de erro.
    }
    
    int j=1;
    NoExt no1;
    NoExt noAnt;
    Item x;
    int vdd = 0;
    int i = 0;
    /*arvoreBinaria = fopen("arvoreExt.bin", "w+b");

    if(situacao==1) {
        arq = fopen("crescente.bin", "rb");
    }
    else if(situacao==2) {
        arq = fopen("decrescente.bin", "rb");
    }
    else if(situacao==3) {
        arq = fopen("aleatorio.bin", "rb");
    }*/


    while((fread(&x, sizeof(Item), 1, arq) == 1) && i<quantidade) { 
        no1.item = x;
        no1.pDir = -1;
        no1.pEsq = -1;

        imprimirArvore(arvoreBinaria);
        fseek(arvoreBinaria, 0, SEEK_SET);
        
        vdd = 0;

        while(vdd == 0) {
            if(fread(&noAnt, sizeof(NoExt), 1, arvoreBinaria) == 1) {
                if(no1.item.chave < noAnt.item.chave) {

                    if(noAnt.pEsq == -1) {
                        printf("Esquerda é -1\n");
                        
                        noAnt.pEsq = j;
                        fseek(arvoreBinaria, (sizeof(NoExt)*-1), 1);
                        fwrite(&noAnt, sizeof(NoExt), 1, arvoreBinaria);
                        
                        j++;

                        fseek(arvoreBinaria, 0, SEEK_END);
                        fwrite(&no1, sizeof(NoExt), 1, arvoreBinaria); 

                        vdd = 1;
                    }
                    else {
                        fseek(arvoreBinaria, (sizeof(NoExt) * noAnt.pEsq), 0);
                    }
                }

                if(no1.item.chave > noAnt.item.chave) {

                    if(noAnt.pDir == -1) {
                        noAnt.pDir = j;
                        j++;
                        fseek(arvoreBinaria, (sizeof(NoExt)*-1), 1);
                        fwrite(&noAnt, sizeof(NoExt), 1, arvoreBinaria);

                        fseek(arvoreBinaria, 0, SEEK_END);
                        fwrite(&no1, sizeof(NoExt), 1, arvoreBinaria);

                        vdd = 1;

                    }
                    else {
                        fseek(arvoreBinaria, (sizeof(NoExt) * noAnt.pDir), 0);
                    }
                }
            }
            else {
                fwrite(&no1, sizeof(NoExt), 1, arvoreBinaria);
                j++;
                vdd = 1; 
            }
        }
        i++;
    }
}


/*bool ArvorePesquisa(No* pRaiz , Chave c, Item *pX) {
    No *pAux ;
    pAux = pRaiz ;

    while (pAux != NULL ) {
        if (c == pAux->item.chave ) {
            *pX = pAux->item ;
            return true ;
        }
        else if (c > pAux->item.chave)
            pAux = pAux->pDir;
        else
            pAux = pAux->pEsq ;
    }
    return false;
}

bool ArvoreInsere(No** ppRaiz, Item x) {
    No** ppAux ;
    ppAux = ppRaiz ;

    while (* ppAux != NULL ) {
        if (x.chave < (*ppAux)->item.chave)
            ppAux = &((*ppAux)->pEsq);
        else if (x.chave > (*ppAux)->item.chave)
            ppAux = &((*ppAux)->pDir);
        else
            return false ;
    }
    *ppAux = NoCria (x);
    return true ;
}

No *NoCria(Item x) {
    No *pAux = (No*) malloc (sizeof (No));
    pAux->item = x;
    pAux->pEsq = NULL ;
    pAux->pDir = NULL ;
    return pAux ;
}

void PreOrdem (No *p) {
    if (p == NULL)
        return;
    printf("%ld\n", p->item.chave);
    PreOrdem(p->pEsq);
    PreOrdem(p->pDir);
}

void PosOrdem (No *p) {
    if (p == NULL)
        return ;
    PosOrdem(p->pEsq);
    PosOrdem(p->pDir);
    printf("%ld\n", p->item.chave) ;
}

void Central(No *p) {
    if (p == NULL)
        return;
    Central(p->pEsq);
    printf("%ld\n", p->item.chave);
    Central(p->pDir);
}*/