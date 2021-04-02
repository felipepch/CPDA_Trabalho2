#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define N 400000
#define P 10000
// tipo item
typedef struct {
    int chave;
    char n;
} Item;

// tipo nó usado na lista encadeada
typedef struct no {
    Item item;
    struct no *proximo;
} No;

// tipo lista com um ponteiro para o primeiro nó
typedef struct {
    No *inicio;
    int tam;
} Lista;

// nossa tabela (vetor de ponteiros para listas)
Lista *tabela[P];



// imprime um item
void imprimirItem(Item i) {
    printf("\tNumero: %d\tChave: %d\n", i.n, i.chave);
}

// cria uma lista vazia e retorna seu endereço na memória
Lista* criarLista() {
    Lista *l = malloc(sizeof(Lista));
    l->inicio = NULL;
    l->tam = 0;
    return l;
}

void inserirInicio(Item i, Lista *lista) {
    No *no = malloc(sizeof(No));
    no->item = i;
    no->proximo = lista->inicio;
    lista->inicio = no;
    lista->tam++;
}

// busca um elemento na lista
No* buscarNo(int mat, No *inicio) {

    while(inicio != NULL) {
        if(inicio->item.chave == mat)
            return inicio;
        else
            inicio = inicio->proximo;
    }
    return NULL;// chave não encontrada
}

void imprimirLista(No *inicio) {
    while(inicio != NULL) {
        imprimirItem(inicio->item);
        inicio = inicio->proximo;
    }
}

// inicializa a tabela com uma lista vazia em cada posição do vetor
void inicializar(){
    int i;
    for(i = 0; i < P; i++)
        tabela[i] = criarLista();
}

// função de espalhamento
int funcaoEspalhamento(int mat){
    return mat % P;
}

// cria item e o insere na tabela
void inserTabela(int v[]){
    Item it;
    for (int i=0 ; i<N ; i++) {
        it.chave = v[i];
        it.n = i+1;
        int indice = funcaoEspalhamento(it.chave);
        inserirInicio(it, tabela[indice]);
    }
}

// busca um item. Seu retorno é um endereço ou NULL
Item* buscarItemTabela(int mat){
    int indice = funcaoEspalhamento(mat);
    No *no = buscarNo(mat, tabela[indice]->inicio);
    if(no)
        return &no->item;
    else
        return NULL;
}

// imprimir tabela
void imprimirTabela(){
    int i;
    printf("\n---------------------TABELA-------------------------\n");
    for(i = 0; i < P; i++){
        printf("%d - Lista tamanho: %d\n", i, tabela[i]->tam);
        imprimirLista(tabela[i]->inicio);
    }
    printf("---------------------FIM TABELA-----------------------\n");
}

void inicializarAleatoriamente(int v[], int n){
    int i;
    for(i = 0; i < n; i++)
        v[i] = rand();
}

int main() {
    srand(time(NULL));
    int op, mat,j;
    Item *i;
    int vetor[N];
    double start, stop, elapsed;

    inicializarAleatoriamente(vetor,N);

    inicializar();

    do {
        printf("\n0 - Sair\n1 - Inserir\n2 - Buscar\n3 - Imprimir tabela\n");
        scanf("%d", &op);
        switch(op) {
        case 0:
            printf("saindo...\n");
            break;
        case 1:
            start = (double) clock() / CLOCKS_PER_SEC;
            inserTabela(vetor);
            stop = (double) clock() / CLOCKS_PER_SEC;
            elapsed = stop - start;
            printf("Tempo total em segundos: %f\n", elapsed);
            break;
        case 2:
            start = (double) clock() / CLOCKS_PER_SEC;
            for (j=0 ; j<N ; j++)
                buscarItemTabela(vetor[j]);
            stop = (double) clock() / CLOCKS_PER_SEC;
            elapsed = stop - start;
            printf("Tempo total em segundos: %f\n", elapsed);
            break;
        case 3:
            start = (double) clock() / CLOCKS_PER_SEC;
            imprimirTabela();
            stop = (double) clock() / CLOCKS_PER_SEC;
            elapsed = stop - start;
            printf("Tempo total em segundos: %f\n", elapsed);
            break;
        default:
            printf("Opcao invalida!\n");
        }
    } while(op != 0);

    return 0;
}
