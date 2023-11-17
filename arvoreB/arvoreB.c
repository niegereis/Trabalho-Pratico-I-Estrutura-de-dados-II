#include "arvoreB.h"


/*Inicializando a arvore*/
void Inicializa (TipoApontador Arvore){
    Arvore = NULL;
}

// Função para pesquisar um item na árvore
void Pesquisa(TipoRegistro *x, TipoApontador Ap){
    long i = 1;

    if (Ap == NULL){
        printf("TipoRegistro nao esta presente na arvore\n");
        return;
    }
 
    while (i < Ap->n &&x->Chave > Ap->r[i-1].Chave) i++;

    if (x->Chave == Ap->r[i-1].Chave){
        *x = Ap->r[i-1];
        return;
    }

    if (x->Chave < Ap->r[i-1].Chave)
        Pesquisa(x, Ap->p[i-1]);
    else 
        Pesquisa(x, Ap->p[i]);
}

void Imprime(TipoApontador arvore){
    int i = 0;

    if (arvore == NULL) return;

    while (i <= arvore->n) {
        Imprime(arvore->p[i]);
        if (i != arvore->n)
           printf("%d ", arvore->r[i].Chave); 
        i++;
    }
}


// Inserir o registro dentro da página apontada por Ap
// TipoRegistro Reg = Registro que vc vai inserir
void InsereNaPagina (TipoApontador Ap, TipoRegistro Reg, TipoApontador ApDir){
    short NaoAchouPosicao;
    int k;
    k = Ap->n; NaoAchouPosicao = (k > 0);

    while (NaoAchouPosicao){ // Enquanto não achamos a posição certa para inserir a chave
        if (Reg.Chave >= Ap->r[k-1].Chave){ // Se a chave que a gente quer inserir for maior que a ultima chave de uma determinada página q
            NaoAchouPosicao = false; //  Achou a posição onde inserir
            break;
        }
        Ap->r[k] = Ap->r[k-1];
        Ap->p[k+1] = Ap->p[k];
        k--;
        if (k < 1) NaoAchouPosicao = false;
    }

    Ap->r[k] = Reg;
    Ap->p[k+1] = ApDir; // empurra o elemento para direita para inserir o novo item
    Ap->n++; // incrementa o numero de itens em uma página
}

// Ap = Apontador para um tipo de registro específico

// Verifica se a página tem espaço para inserir o item novo ou teremos que criar uma página nova
void Ins (TipoRegistro Reg, TipoApontador Ap, short *Cresceu, 
TipoRegistro *RegRetorno, TipoApontador *ApRetorno){ 
    long i = 1; long j;
    TipoApontador ApTemp; // Apontador para a página temporária (pagina nova ou não)

    if (Ap == NULL){
        *Cresceu = true; (*RegRetorno) = Reg; (*ApRetorno) = NULL; // Se a árvore for vazia 
        return;
    }

    while (i < Ap->n && Reg.Chave > Ap->r[i- 1].Chave) i++; // Enquanto o valor de i for menor que o numero de itens dentro de uma página 
    // Enquanto o a chave que queremos inserir for maior que a chave que está na página, incrementa o i ate achar a posição onde o item tem q ser inserido

    if (Reg.Chave == Ap->r[i-1].Chave){ // Se esse item ja tiver na árvore, não vai ser colocado de novo, parando a recursão
        printf(" Erro: Registro ja esta presentei\n"); 
        *Cresceu = false;
        return;
    }

    if (Reg.Chave < Ap->r[i-1].Chave) i--; // Se a chave que queremos inserir for menor que a chave localizada, ou seja que o apontador ta apontadno a chave
    Ins (Reg, Ap->p[i], Cresceu, RegRetorno, ApRetorno); // i volta a ter valor 1 
    if (!*Cresceu) return;
    if (Ap->n < MM) /* Pagina tem espaco */
    {
        InsereNaPagina (Ap, *RegRetorno, *ApRetorno); /* RegRetorno seria tipo o retorno do registro */
        *Cresceu = false; // Não cresceu, ja que nao foi criada uma nova página
        return;
    }
    /* Overflow : Pagina tem que ser dividida */
    ApTemp = (TipoApontador)malloc(sizeof(TipoPagina)); // a página nova vai ser criada e o ApTemp que é o apontador temporário vai receber essa alocação
    ApTemp->n = 0; ApTemp->p[0] = NULL; // tudo vazio

    if (i < M + 1){
        InsereNaPagina(ApTemp, Ap->r[MM-1], Ap->p[MM]); //Vai inserir o item que existe na página que existe. Os registros e ponteiros são distribuídos entre a página atual e a nova página temporária 
        Ap->n--;
        InsereNaPagina (Ap, *RegRetorno, *ApRetorno);
    }
    else 
        InsereNaPagina(ApTemp, *RegRetorno, *ApRetorno);

    for (j = M + 2;j <=MM; j++)
        InsereNaPagina(ApTemp, Ap->r[j-1],Ap->p[j]);

    Ap->n = M; ApTemp->p[0] = Ap->p[M+1];
    *RegRetorno = Ap->r[M]; *ApRetorno = ApTemp;
}

void Insere(TipoRegistro Reg, TipoApontador *Ap){
    short Cresceu;
    TipoRegistro RegRetorno;
    TipoPagina *ApRetorno, *ApTemp;

    Ins (Reg, *Ap, &Cresceu, &RegRetorno, &ApRetorno);

    if (Cresceu) /* Arvore cresce na altura pela raiz */
    {
        ApTemp = (TipoPagina*)malloc( sizeof(TipoPagina));
        ApTemp->n = 1;
        ApTemp->r[0] = RegRetorno;
        ApTemp->p[1] = ApRetorno;
        ApTemp->p[0] = *Ap; *Ap = ApTemp;
    }
}