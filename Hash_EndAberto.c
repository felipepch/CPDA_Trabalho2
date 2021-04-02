#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#define M 800000
#define N 400000

// estrutura Item com numero e uma chave
typedef struct{
    int n;
    int chave;
}Item;

// nossa tabela hash do tipo Item
Item tabelaHash[M];

// inicializa nossa tabela com o valor de chave -1
void inicializarTabela(){
    int i;
    for(i = 0; i < M; i++)
        tabelaHash[i].chave = -1;
}

// função de espalhamento (resto da divisão da chave por M)
int gerarCodigoHash(int chave){
    return chave % M;
}

// inserir um item na tabela
void inserir(int v[]){
    Item item;
    int j=1;
    for (int i=0; i<N ; i++) {
        item.chave = v[i];
        item.n = i+1;
        int indice = gerarCodigoHash(item.chave);
        while(tabelaHash[indice].chave != -1) {

            indice = gerarCodigoHash(indice + j);
            j++;

        }
        if (indice < M)
            tabelaHash[indice] = item;

    }
}

Item* buscar(int key){
    int indice = gerarCodigoHash(key);
    int j=1;
    while(tabelaHash[indice].chave != -1){
        if(tabelaHash[indice].chave == key)
            return &tabelaHash[indice];
        else if (gerarCodigoHash(indice + j) < M){
            indice = gerarCodigoHash(indice + j);
            j++;
        }

    }
    return NULL;
}

void imprimir(){
    int i;
    printf("\n------------------------TABELA---------------------------\n)");
    for(i = 0; i < M; i++){
        if(tabelaHash[i].chave != -1)
            printf("%2d = %3d \t %d\n", i, tabelaHash[i].chave, tabelaHash[i].n);
        else
            printf("%2d =\n", i);
    }
    printf("\n----------------------------------------------------------\n");
}

void inicializarAleatoriamente(int v[], int n){
    int i;
    for(i = 0; i < n; i++)
        v[i] = rand();
}

int main() {

    srand(time(NULL));
    int op, chave,i;
    Item *item;
    int vetor[N];
    double start, stop, elapsed;

    inicializarAleatoriamente(vetor,N);

    inicializarTabela();

    do{
        printf("1 - Inserir\n2 - Buscar\n3 - Imprimir\n0 - Sair\n");
        scanf("%d", &op);

        switch(op){
        case 0:
            printf("Saindo...\n");
            break;
        case 1:
            start = (double) clock() / CLOCKS_PER_SEC;
            inserir(vetor);
            stop = (double) clock() / CLOCKS_PER_SEC;
            elapsed = stop - start;
            printf("Tempo total em segundos: %f\n", elapsed);
            break;
        case 2:
            start = (double) clock() / CLOCKS_PER_SEC;
            for (i=0 ; i<N ; i++)
                buscar(vetor[i]);
            stop = (double) clock() / CLOCKS_PER_SEC;
            elapsed = stop - start;
            printf("Tempo total em segundos: %f\n", elapsed);
            break;
        case 3:
            start = (double) clock() / CLOCKS_PER_SEC;
            imprimir();
            stop = (double) clock() / CLOCKS_PER_SEC;
            elapsed = stop - start;
            printf("Tempo total em segundos: %f\n", elapsed);
            break;
        default:
            printf("Opcao invalida!\n");
        }

    }while(op != 0);

    return 0;
}
