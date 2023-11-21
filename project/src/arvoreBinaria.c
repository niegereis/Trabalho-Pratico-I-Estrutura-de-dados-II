#include "../lib/arvoreBinaria.h"

No* NoCria(Registro x) {
    No *pAux = (No*) malloc (sizeof (No));
    pAux->item = x;
    pAux->pEsq = NULL ;
    pAux->pDir = NULL ;
    return pAux ;
}

Arvore Arvore_Inicia() {
    Arvore pRaiz;
    pRaiz = NULL;
    return pRaiz;
}

bool leArquivoBin(FILE* arq, int quantidade, Arvore arvore, Analise* analise) {
    int i=0;
    Registro x;
    while((fread(&x, sizeof(Registro), 1, arq) == 1) && i<quantidade) {
        analise->transferenciaInsercao++;
        i++;
        ArvoreInsere(&arvore, x, analise);
    }
    return true;
}

bool ArvorePesquisa(No* pRaiz , int c, Registro *pX, Analise* analise) {
    No *pAux ;
    pAux = pRaiz ;

    while (pAux != NULL ) {
        if (c == pAux->item.chave ) {
            analise->comparacaoPesquisa++;
            *pX = pAux->item ;
            return true ;
        }
        else if (c > pAux->item.chave){
            pAux = pAux->pDir;
            analise->comparacaoPesquisa++;
        }
        else
            pAux = pAux->pEsq ;
    }
    return false;
}

bool ArvoreInsere(No** ppRaiz, Registro x, Analise* analise) {
    No** ppAux ;
    ppAux = ppRaiz ;

    while (* ppAux != NULL ) {
        if (x.chave < (*ppAux)->item.chave){
            analise->comparacaoInsercao++;
            ppAux = &((*ppAux)->pEsq);
        }
        else if (x.chave > (*ppAux)->item.chave){
            analise->comparacaoInsercao++;
            ppAux = &((*ppAux)->pDir);
        }
        else
            return false ;
    }
    *ppAux = NoCria(x);
    return true ;
}



// void PreOrdem (No *p) {
//     if (p == NULL)
//         return;
//     printf("%ld\n", p->item.chave);
//     PreOrdem(p->pEsq);
//     PreOrdem(p->pDir);
// }

// void PosOrdem (No *p) {
//     if (p == NULL)
//         return ;
//     PosOrdem(p->pEsq);
//     PosOrdem(p->pDir);
//     printf("%ld\n", p->item.chave) ;
// }

// void Central(No *p) {
//     if (p == NULL)
//         return;
//     Central(p->pEsq);
//     printf("%ld\n", p->item.chave);
//     Central(p->pDir);
// }

Registro arvoreBinaria(Analise* analise, int chave, short* achou, FILE* arquivo, int quantidade){
    Registro registroEncontrado;
    bool valido;
   struct timespec inicio, fim;
    Arvore arvore = Arvore_Inicia();
    clock_gettime(CLOCK_MONOTONIC, &inicio);

    valido = leArquivoBin(arquivo, quantidade, arvore, analise);
    clock_gettime(CLOCK_MONOTONIC, &fim);
    analise->tempoInsere = fim.tv_nsec - inicio.tv_nsec;

    if(!valido) return registroEncontrado; 

    clock_gettime(CLOCK_MONOTONIC, &inicio);
    valido = ArvorePesquisa(arvore , chave, &registroEncontrado, analise);
    clock_gettime(CLOCK_MONOTONIC, &fim);
    analise->tempoPesquisa = fim.tv_nsec - inicio.tv_nsec;

    if(!valido) return registroEncontrado;  

    *achou = 1;
    return registroEncontrado;
}