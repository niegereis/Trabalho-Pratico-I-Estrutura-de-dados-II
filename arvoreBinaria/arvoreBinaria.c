#include "arvoreBinaria.h"

void Arvore_Inicia(No** pRaiz) {
    *pRaiz = NULL ;
}

void leArquivo(FILE* arq, int situacao, int quantidade, Arvore arvore, Item x) {
    int i=0;
    if(situacao==1) {
        arq = fopen("crescente.bin", "rb");
        while((fread(&x, sizeof(Item), 1, arq) == 1) && i<quantidade) {
            i++;
            ArvoreInsere(&arvore, x);
        }
        fclose (arq);
    }

    if(situacao==2) {
        arq = fopen("decrescente.bin", "rb");
        while((fread(&x, sizeof(Item), 1, arq) == 1) && i<quantidade) {
            i++;
            ArvoreInsere(&arvore, x);
        }
        fclose (arq);
    }

    if(situacao==3) {
        arq = fopen("aleatorio.bin", "rb");
        while((fread(&x, sizeof(Item), 1, arq) == 1) && i<quantidade) {
            i++;
            ArvoreInsere(&arvore, x);
        }
        fclose (arq);
    }

}

bool ArvorePesquisa(No* pRaiz , Chave c, Item *pX) {
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
}