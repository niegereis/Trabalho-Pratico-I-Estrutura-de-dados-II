#include "arvoreBinaria.h"

void Arvore_Inicia(No** pRaiz) {
    *pRaiz = NULL ;
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