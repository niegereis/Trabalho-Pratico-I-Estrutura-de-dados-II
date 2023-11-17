#include "arvoreB.h"
#include "../metodos.h"

/*Inicializando a arvore*/
void InicializaArvoreB (TipoApontador Arvore, Analise* analise){
    
    clock_t inicio = clock();
    analise->comparacao = 0;
    Arvore = NULL;
}

void leArquivo(FILE* arq, int situacao, int quantidade, TipoApontador Arvore, TipoRegistro x, Analise* analise) {
    int i=0;
    if(situacao==1) {
        arq = fopen("crescente.bin", "rb");
        while((fread(&x, sizeof(TipoRegistro), 1, arq) == 1) && i<quantidade) {
            i++;
            Insere(x, Arvore, analise);
        }
        fclose (arq);
    }

    if(situacao==2) {
        arq = fopen("decrescente.bin", "rb");
        while((fread(&x, sizeof(TipoRegistro), 1, arq) == 1) && i<quantidade) {
            i++;
            Insere(x, Arvore, analise);
        }
        fclose (arq);
    }

    if(situacao==3) {
        arq = fopen("aleatorio.bin", "rb");
        while((fread(&x, sizeof(TipoRegistro), 1, arq) == 1) && i<quantidade) {
            i++;
            Insere(x, Arvore, analise);
        }
        fclose (arq);
    }

    analise->numeroTransferencia = i; 

}

// Função para pesquisar um item na árvore
void Pesquisa(TipoRegistro *x, TipoApontador Ap, Analise* analise){
    long i = 1;

    if (Ap == NULL){ // Se a árvore for vazia 
        analise->comparacao++;
        printf("TipoRegistro nao esta presente na arvore\n");
        return;
    }
    analise->comparacao++;
 
    while (i < Ap->n &&x->Chave > Ap->r[i-1].Chave){
        i++; // incrementando o i
        analise->comparacao++; // incrementa o número de comparações
    }
    // quanto mais você procura por uma chave e compara com as outras pra ver se vc achou, sempre vai ter uma comparação
    analise->comparacao++;

    if (x->Chave == Ap->r[i-1].Chave){
        *x = Ap->r[i-1];
        analise->comparacao++;
        return;
    }

    analise->comparacao++;
    if (x->Chave < Ap->r[i-1].Chave){
        analise->comparacao++;
        Pesquisa(x, Ap->p[i-1], analise); // chamada recursiva 
    }
    else {
        analise->comparacao++;
        Pesquisa(x, Ap->p[i], analise);
    }
}

void Imprime(TipoApontador arvore){
    int i = 0;

    if (arvore == NULL) {
        return;
    }

    while (i <= arvore->n) {
        Imprime(arvore->p[i]);
        if (i != arvore->n)
           printf("%d ", arvore->r[i].Chave); 
        i++;
    }
}


// Inserir o registro dentro da página apontada por Ap
// TipoRegistro Reg = Registro que vc vai inserir
void InsereNaPagina (TipoApontador Ap, TipoRegistro Reg, TipoApontador ApDir, Analise *analise){
    short NaoAchouPosicao;
    int k;
    k = Ap->n; NaoAchouPosicao = (k > 0);

    while (NaoAchouPosicao){ // Enquanto não achamos a posição certa para inserir a chave
        analise->comparacao++;
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
void Ins (TipoRegistro Reg, TipoApontador Ap, short *Cresceu, TipoRegistro *RegRetorno, TipoApontador *ApRetorno, Analise *analise){ 
    long i = 1; long j;
    TipoApontador ApTemp; // Apontador para a página temporária (pagina nova ou não)

    if (Ap == NULL){
        *Cresceu = true; (*RegRetorno) = Reg; (*ApRetorno) = NULL; // Se a árvore for vazia 
        return;
    }

    while (i < Ap->n && Reg.Chave > Ap->r[i- 1].Chave) analise->comparacao++; i++; // Enquanto o valor de i for menor que o numero de itens dentro de uma página 
    // Enquanto o a chave que queremos inserir for maior que a chave que está na página, incrementa o i ate achar a posição onde o item tem q ser inserido

    if (Reg.Chave == Ap->r[i-1].Chave){ // Se esse item ja tiver na árvore, não vai ser colocado de novo, parando a recursão
        printf(" Erro: Registro ja esta presentei\n"); 
        *Cresceu = false;
        return;
    }

    if (Reg.Chave < Ap->r[i-1].Chave) i--; // Se a chave que queremos inserir for menor que a chave localizada, ou seja que o apontador ta apontadno a chave
    Ins (Reg, Ap->p[i], Cresceu, RegRetorno, ApRetorno, analise); // i volta a ter valor 1 
    if (!*Cresceu) return;
    if (Ap->n < MM) /* Pagina tem espaco */
    {
        InsereNaPagina (Ap, *RegRetorno, *ApRetorno, analise); /* RegRetorno seria tipo o retorno do registro */
        *Cresceu = false; // Não cresceu, ja que nao foi criada uma nova página
        return;
    }
    /* Overflow : Pagina tem que ser dividida */
    ApTemp = (TipoApontador)malloc(sizeof(TipoPagina)); // a página nova vai ser criada e o ApTemp que é o apontador temporário vai receber essa alocação
    ApTemp->n = 0; ApTemp->p[0] = NULL; // tudo vazio

    if (i < M + 1){
        InsereNaPagina(ApTemp, Ap->r[MM-1], Ap->p[MM], analise); //Vai inserir o item que existe na página que existe. Os registros e ponteiros são distribuídos entre a página atual e a nova página temporária 
        Ap->n--;
        InsereNaPagina (Ap, *RegRetorno, *ApRetorno, analise);
    }
    else 
        InsereNaPagina(ApTemp, *RegRetorno, *ApRetorno, analise);

    for (j = M + 2;j <=MM; j++)
        InsereNaPagina(ApTemp, Ap->r[j-1],Ap->p[j], analise);

    Ap->n = M; ApTemp->p[0] = Ap->p[M+1];
    *RegRetorno = Ap->r[M]; *ApRetorno = ApTemp;
}

void Insere(TipoRegistro Reg, TipoApontador *Ap, Analise *analise){
    short Cresceu;
    TipoRegistro RegRetorno;
    TipoPagina *ApRetorno, *ApTemp;

    Ins (Reg, *Ap, &Cresceu, &RegRetorno, &ApRetorno, &analise);

    if (Cresceu) /* Arvore cresce na altura pela raiz */
    {
        ApTemp = (TipoPagina*)malloc( sizeof(TipoPagina));
        ApTemp->n = 1;
        ApTemp->r[0] = RegRetorno;
        ApTemp->p[1] = ApRetorno;
        ApTemp->p[0] = *Ap; 
        *Ap = ApTemp;
    }
}