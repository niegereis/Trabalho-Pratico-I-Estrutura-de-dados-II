#include "../lib/arvoreB.h"

void InicializaArvoreB(TipoApontador *arvore) { (*arvore) = NULL; }

// Função para pesquisar um item na árvore
bool Pesquisa(Registro *x, TipoApontador Ap, Analise *analise) {
  long i = 1;

  if (Ap == NULL) {  // Se a árvore for vazia
    analise->comparacaoPesquisa++;
    return false;
  }

  analise->comparacaoPesquisa++;
  while (i < Ap->n && x->chave > Ap->r[i - 1].chave) {
    i++;                            // incrementando o i
    analise->comparacaoPesquisa++;  // incrementa o número de comparações
  }
  // quanto mais você procura por uma chave e compara com as outras pra ver se
  // vc achou, sempre vai ter uma comparação

  analise->comparacaoPesquisa++;
  if (x->chave == Ap->r[i - 1].chave) {
    *x = Ap->r[i - 1];
    analise->comparacaoPesquisa++;
    return true;
  }

  analise->comparacaoPesquisa++;
  if (x->chave < Ap->r[i - 1].chave) {
    return Pesquisa(x, Ap->p[i - 1], analise);  // chamada recursiva
  } else {
    return Pesquisa(x, Ap->p[i], analise);
  }
}

// Inserir o registro dentro da página apontada por Ap
// TipoRegistro Reg = Registro que vc vai inserir
void InsereNaPagina(TipoApontador Ap, Registro Reg, TipoApontador ApDir,
                    Analise *analise) {
  short NaoAchouPosicao;
  int k;
  k = Ap->n;
  NaoAchouPosicao = (k > 0);

  while (NaoAchouPosicao) {  // Enquanto não achamos a posição certa para
                             // inserir a chave
    analise->comparacaoInsercao++;
    if (Reg.chave >=
        Ap->r[k - 1].chave) {  // Se a chave que a gente quer inserir for maior
                               // que a ultima chave de uma determinada página q
      NaoAchouPosicao = false;  //  Achou a posição onde inserir
      break;
    }
    Ap->r[k] = Ap->r[k - 1];
    Ap->p[k + 1] = Ap->p[k];
    k--;
    if (k < 1) NaoAchouPosicao = false;
  }

  Ap->r[k] = Reg;
  Ap->p[k + 1] =
      ApDir;  // empurra o elemento para direita para inserir o novo item
  Ap->n++;    // incrementa o numero de itens em uma página
}

// Ap = Apontador para um tipo de registro específico

// Verifica se a página tem espaço para inserir o item novo ou teremos que criar
// uma página nova
void Ins(Registro Reg, TipoApontador Ap, short *Cresceu, Registro *RegRetorno,
         TipoApontador *ApRetorno, Analise *analise) {
  long i = 1;
  long j;

  // Apontador para a página temporária (pagina nova ou não)
  TipoApontador ApTemp;

  if (Ap == NULL) {
    *Cresceu = true;
    (*RegRetorno) = Reg;
    (*ApRetorno) = NULL;  // Se a árvore for vazia
    return;
  }

  while (i < Ap->n && Reg.chave > Ap->r[i - 1].chave) {
    analise->comparacaoInsercao++;
    i++;
  }  // Enquanto o valor de i for menor que o numero de itens dentro de uma
     // página
  // Enquanto o a chave que queremos inserir for maior que a chave que está na
  // página, incrementa o i ate achar a posição onde o item tem q ser inserido

  // Se esse item ja tiver na árvore, não vai ser colocado de novo, parando a
  // recursão
  if (Reg.chave == Ap->r[i - 1].chave) {
    printf(" Erro: Registro ja esta presentei\n");
    analise->comparacaoInsercao++;
    *Cresceu = false;
    return;
  }
  analise->comparacaoInsercao++;
  if (Reg.chave < Ap->r[i - 1].chave)
    i--;  // Se a chave que queremos inserir for menor que a chave localizada
  Ins(Reg, Ap->p[i], Cresceu, RegRetorno, ApRetorno,
      analise);  // i volta a ter valor 1
  if (!*Cresceu) return;

  if (Ap->n < 2 * M) /* Pagina tem espaco */
  {
    InsereNaPagina(Ap, *RegRetorno, *ApRetorno,
                   analise); /* RegRetorno seria tipo o retorno do registro */
    *Cresceu = false;  // Não cresceu, ja que nao foi criada uma nova página
    return;
  }
  /* Overflow : Pagina tem que ser dividida */
  ApTemp = (TipoApontador)malloc(
      sizeof(TipoPagina));  // a página nova vai ser criada e o ApTemp que é o
                            // apontador temporário vai receber essa alocação
  ApTemp->n = 0;
  ApTemp->p[0] = NULL;  // tudo vazio

  if (i < M + 1) {
    InsereNaPagina(
        ApTemp, Ap->r[2 * M - 1], Ap->p[2 * M],
        analise);  // Vai inserir o item que existe na página que existe. Os
                   // registros e ponteiros são distribuídos entre a página
                   // atual e a nova página temporária
    Ap->n--;
    InsereNaPagina(Ap, *RegRetorno, *ApRetorno, analise);
  } else
    InsereNaPagina(ApTemp, *RegRetorno, *ApRetorno, analise);

  for (j = M + 2; j <= 2 * M; j++)
    InsereNaPagina(ApTemp, Ap->r[j - 1], Ap->p[j], analise);

  Ap->n = M;
  ApTemp->p[0] = Ap->p[M + 1];
  *RegRetorno = Ap->r[M];
  *ApRetorno = ApTemp;
}

void Insere(Registro Reg, TipoApontador *Ap, Analise *analise) {
  short Cresceu;
  Registro RegRetorno;
  TipoPagina *ApRetorno, *ApTemp;

  Ins(Reg, *Ap, &Cresceu, &RegRetorno, &ApRetorno, analise);

  if (Cresceu) /* Arvore cresce na altura pela raiz */
  {
    ApTemp = (TipoPagina *)malloc(sizeof(TipoPagina));
    ApTemp->n = 1;
    ApTemp->r[0] = RegRetorno;
    ApTemp->p[1] = ApRetorno;
    ApTemp->p[0] = *Ap;
    *Ap = ApTemp;
  }
}

void LiberaPagina(TipoApontador Ap) {
  if (Ap != NULL) {
    for (int i = 0; i <= Ap->n; i++) {
      LiberaPagina(Ap->p[i]);  // Recursivamente libera os filhos
    }
    free(Ap);  // Libera a memória da página
  }
}

void LiberaArvore(TipoApontador *Arvore) {
  if (*Arvore != NULL) {
    LiberaPagina(*Arvore);  // Inicia a liberação da árvore
    *Arvore = NULL;         // A árvore agora está vazia
  }
}

Registro arvoreB(Analise *analise, int chave, short *achou, FILE *arquivo,
                 int quantidade) {
  Registro registroEncontrado;
  bool valido;
  struct timespec inicio, fim;

  TipoApontador arvore;
  InicializaArvoreB(&arvore);

  clock_gettime(CLOCK_REALTIME, &inicio);
  int i = 0;
  while ((fread(&registroEncontrado, sizeof(Registro), 1, arquivo) == 1) &&
         i < quantidade) {
    i++;
    Insere(registroEncontrado, &arvore, analise);
  }
  analise->transferenciaInsercao = i;
  clock_gettime(CLOCK_REALTIME, &fim);
  analise->tempoInsere =
      (fim.tv_sec - inicio.tv_sec) * 1e9 + (fim.tv_nsec - inicio.tv_nsec);

  registroEncontrado.chave = chave;
  clock_gettime(CLOCK_MONOTONIC, &inicio);
  valido = Pesquisa(&registroEncontrado, arvore, analise);
  clock_gettime(CLOCK_MONOTONIC, &fim);
  analise->tempoPesquisa =
      (fim.tv_sec - inicio.tv_sec) * 1e9 + (fim.tv_nsec - inicio.tv_nsec);
  LiberaArvore(&arvore);
  if (!valido) return registroEncontrado;

  *achou = 1;
  return registroEncontrado;
}