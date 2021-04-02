#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 500000
// estrututa nó
typedef struct no {
    int conteudo;
    struct no *esquerda, *direita;
} No;

// estrutura árvore com um ponteiro para um nó
typedef struct {
    No *raiz;
    int tam;
} ArvB;

void inserirDireita(No *no, int valor);

// procedimento para inserir um elemento na subárvore esquerda
void inserirEsquerda(No *no, int valor) {
    if(no->esquerda == NULL) {
        No *novo = (No*)malloc(sizeof(No));
        novo->conteudo = valor;
        novo->esquerda = NULL;
        novo->direita = NULL;
        no->esquerda = novo;
    } else {
        if(valor < no->esquerda->conteudo)
            inserirEsquerda(no->esquerda, valor);
        if(valor > no->esquerda->conteudo)
            inserirDireita(no->esquerda, valor);
    }
}

// procedimento para inserir um elemento na subárvore direita
void inserirDireita(No *no, int valor) {
    if(no->direita == NULL) {
        No *novo = (No*)malloc(sizeof(No));
        novo->conteudo = valor;
        novo->esquerda = NULL;
        novo->direita = NULL;
        no->direita = novo;
    } else {
        if(valor > no->direita->conteudo)
            inserirDireita(no->direita, valor);
        if(valor < no->direita->conteudo)
            inserirEsquerda(no->direita, valor);
    }
}

void inserir(ArvB *arv, int valor) {
    if(arv->raiz == NULL) {
        No *novo = (No*)malloc(sizeof(No));
        novo->conteudo = valor;
        novo->esquerda = NULL;
        novo->direita = NULL;
        arv->raiz = novo;
    } else {
        if(valor < arv->raiz->conteudo)
            inserirEsquerda(arv->raiz, valor);
        if(valor > arv->raiz->conteudo)
            inserirDireita(arv->raiz, valor);
    }
}

No* inserirNovaVersao(No *raiz, int valor) {
    if(raiz == NULL) {
        No *novo = (No*)malloc(sizeof(No));
        novo->conteudo = valor;
        novo->esquerda = NULL;
        novo->direita = NULL;
        return novo;
    } else {
        if(valor < raiz->conteudo)
            raiz->esquerda = inserirNovaVersao(raiz->esquerda, valor);
        if(valor > raiz->conteudo)
            raiz->direita = inserirNovaVersao(raiz->direita, valor);
        return raiz;
    }
}

// função que retorna o tamanho de uma árvore
int tamanho(No *raiz) {
    if(raiz == NULL)
        return 0;
    else
        return 1 + tamanho(raiz->esquerda) + tamanho(raiz->direita);
}

// função para buscar um elemento na árvore
int buscar(No *raiz, int chave) {
    if(raiz == NULL) {
        return 0;
    } else {
        if(raiz->conteudo == chave)
            return 1;
        else {
            if(chave < raiz->conteudo)
                return buscar(raiz->esquerda, chave);
            else
                return buscar(raiz->direita, chave);
        }
    }
}

void imprimirPreOrdem(No *raiz) {
    if(raiz != NULL) {
        printf("%d ", raiz->conteudo);
        imprimirPreOrdem(raiz->esquerda);
        imprimirPreOrdem(raiz->direita);
    }
}

void imprimirPosOrdem(No *raiz) {
    if(raiz != NULL) {
        imprimirPosOrdem(raiz->esquerda);
        imprimirPosOrdem(raiz->direita);
        printf("%d ", raiz->conteudo);
    }
}

void imprimirEmOrdem(No *raiz) {
    if(raiz != NULL) {
        imprimirEmOrdem(raiz->esquerda);
        printf("%d ", raiz->conteudo);
        imprimirEmOrdem(raiz->direita);
    }
}

// função para a remoção de um nó
No* remover(No *raiz, int chave) {
    if(raiz == NULL)
        return NULL;
    else {
        if(raiz->conteudo == chave) {
            // remove nós folhas (nós sem filhos)
            if(raiz->esquerda == NULL && raiz->direita == NULL) {
                free(raiz);
                return NULL;
            }
            else{
                // remover nós que possuem apenas 1 filho
                if(raiz->esquerda == NULL || raiz->direita == NULL){
                    No *aux;
                    if(raiz->esquerda != NULL)
                        aux = raiz->esquerda;
                    else
                        aux = raiz->direita;
                    free(raiz);
                    return aux;
                }
                else{
                    No *aux = raiz->esquerda;
                    while(aux->direita != NULL)
                        aux = aux->direita;
                    raiz->conteudo = aux->conteudo;
                    aux->conteudo = chave;
                    raiz->esquerda = remover(raiz->esquerda, chave);
                    return raiz;
                }
            }
        } else {
            if(chave < raiz->conteudo)
                raiz->esquerda = remover(raiz->esquerda, chave);
            else
                raiz->direita = remover(raiz->direita, chave);
            return raiz;
        }
    }
}

void inicializarAleatoriamente(int v[], int n){
    int i;
    for(i = 0; i < n; i++)
        v[i] = rand();
}


// ffunção principal
int main() {
    srand(time(NULL));
    int op, valor, v[N], i;
    ArvB arv;
    arv.raiz = NULL;

    No *raiz = NULL;

    double start, stop, elapsed;

    inicializarAleatoriamente(v,N);

    do {
        printf("\n0 - sair\n1 - inserir\n2 - imprimir EM ORDEM\n3 - imprimir POS ORDEM\n4 - imprimir PRE ORDEM\n5 - Buscar\n6 - Remover\n");
        scanf("%d", &op);

        switch(op) {
        case 0:
            printf("\nSaindo...\n");
            break;
        case 1:
            start = (double) clock() / CLOCKS_PER_SEC;
            for (i=0 ; i<N ; i++)
                raiz = inserirNovaVersao(raiz, v[i]);
            stop = (double) clock() / CLOCKS_PER_SEC;
            elapsed = stop - start;
            printf("Tempo total em segundos: %f\n", elapsed);
            break;
        case 2:
            printf("\nImpressao EM ORDEM da arvore binaria:\n");
            imprimirEmOrdem(raiz);
            printf("\n");
            printf("Tamanho: %d\n", tamanho(raiz));
            break;
        case 3:
            printf("\nImpressao POS ORDEM da arvore binaria:\n");
            imprimirPosOrdem(raiz);
            printf("\n");
            printf("Tamanho: %d\n", tamanho(raiz));
            break;
        case 4:
            printf("\nImpressao PRE ORDEM da arvore binaria:\n");
            imprimirPreOrdem(raiz);
            printf("\n");
            printf("Tamanho: %d\n", tamanho(raiz));
            break;
        case 5:
            start = (double) clock() / CLOCKS_PER_SEC;
            for (i=0 ; i<N ; i++)
                buscar(raiz, v[i]);
            stop = (double) clock() / CLOCKS_PER_SEC;
            elapsed = stop - start;
            printf("Tempo total em segundos: %f\n", elapsed);
            break;
        case 6:
            start = (double) clock() / CLOCKS_PER_SEC;
            for (i=0 ; i<N ; i++)
                raiz = remover(raiz, v[i]);
            stop = (double) clock() / CLOCKS_PER_SEC;
            elapsed = stop - start;
            printf("Tempo total em segundos: %f\n", elapsed);
            break;
        default:
            printf("\nOpcao invalida...\n");
        }
    } while(op != 0);
}
