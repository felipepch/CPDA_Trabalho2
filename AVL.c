#include<stdio.h>
#include<stdlib.h>
#include <time.h>
#include<windows.h>
#define MAX 100
#define N 100000

void configtela()//fun��o q configura o tamanho da tela e do buffer
{
COORD outbuff;
outbuff.X = 81;
outbuff.Y = 40;
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
SetConsoleScreenBufferSize(hConsole, outbuff);
Sleep(130);
SMALL_RECT windowSize = {0, 0, 80, 39};
SetConsoleWindowInfo(hConsole, TRUE, &windowSize);
}

void limpa_tela()
{
    system("cls");
}

void menu_principal()
{
    printf(" ====================================== MENU ===================================\n\n");
}

typedef struct No
{
    int Id; //Valor que � informado para o n�
    struct No *Esquerda; //Liga��o com outro n�(valor) pela esquerda
    struct No *Direita; //Liga��o com outro n�(valor) pela direita
    int Altura; //Altura do N�
} No;

/* Fun��o que retorna o fator de balanceamento do n� */
int Balanceamento(No *Raiz)
{
    if (Raiz == NULL)
    return 0;
    return Altura(Raiz-> Esquerda) - Altura(Raiz-> Direita);
}

/* Fun��o que retorna o maior valor entre dois inteiros (Utilizado pelas rota��es */
int Maior(int a, int b);

/* Fun��o que retorna o maior valor entre dois inteiros (Utilizado pelas rota��es */
int Maior(int a, int b)
{
    return (a > b)? a : b;
}

/* Fun��o para a rota��o da sub-�rvore (� direita) */
No *RotDir(No *Raiz)
{
    No *AuxiliarEsquerda = Raiz-> Esquerda;
    No *AuxiliarDireita = AuxiliarEsquerda-> Direita;

    // Realizando rota��o
    AuxiliarEsquerda-> Direita = Raiz;
    Raiz-> Esquerda = AuxiliarDireita;

    // Atualizando alturas
    Raiz-> Altura = Maior(Altura(Raiz-> Esquerda), Altura(Raiz-> Direita))+1;
    AuxiliarEsquerda-> Altura = Maior(Altura(AuxiliarEsquerda-> Esquerda), Altura(AuxiliarEsquerda-> Direita))+1;

    // Retornando a nova raiz (Raiz alterada)
    return AuxiliarEsquerda;
}

/* Fun��o para a rota��o da sub-�rvore (� esquerda) */
No *RotEsq(No *Raiz)
{
    No *AuxiliarDireita = Raiz-> Direita;
    No *AuxiliarEsquerda = AuxiliarDireita-> Esquerda;

    // Realizando rota��o
    AuxiliarDireita-> Esquerda = Raiz;
    Raiz-> Direita = AuxiliarEsquerda;

    // Atualizando alturas
    Raiz->Altura = Maior(Altura(Raiz-> Esquerda), Altura(Raiz-> Direita))+1;
    AuxiliarDireita->Altura = Maior(Altura(AuxiliarDireita-> Esquerda), Altura(AuxiliarDireita-> Direita))+1;

    // Retornando a nova raiz (Raiz alterada)
    return AuxiliarDireita;
}

/* Fun��o para verificar se o ponteiro Raiz do tipo No (registro) � nulo */
int IsNull(No *Raiz) //Podia ser feito sem ela, mas dava mais trabalho pra fazer toda vez que fosse preciso verificar isso
{
	return (Raiz == (No*)NULL); //Sempre retorna nulo se for
}

/* Fun��o que verifica e imprime na tela a altura da �rvore ou do n� */
int Altura(No *Raiz)
{
    if (Raiz == NULL) //Se raiz for nulo
        return -1;
    return Raiz-> Altura; //Sen�o usa recursividade
}

/* Fun��o auxiliar que aloca um novo n� para a chava informada - Chamada pela fun��o AdicionarNo */
No* NovoNo(int Id)
{
    No* Raiz = (No*)malloc(sizeof(No)); //Aloca espa�o na mem�ria para o registro
    Raiz-> Id = Id; //Id de Raiz recebe a chave informada pelo usu�rio
    Raiz-> Esquerda = NULL; // Como o n� � novo -> Esquerda e -> Direita apontam para nulo
    Raiz-> Direita = NULL;
    Raiz-> Altura = 0;  // O novo n� inserido � inicialmente uma folha portanto sua altura � 1
    return(Raiz); //Retorna a Raiz
}

/* Fun��o que insere um novo N� - Utiliza a fun��o auxiliar NovoNo */
No* AdicionarNo(No *Raiz, int Id)
{
    /* Passo 1 - Executa a inser��o normal */
    if(Raiz == NULL) //Se a Raiz � nula(Vazia)
    {
        return(NovoNo(Id)); //Chama a fun��o auxiliar que insere a chave informada pelo usu�rio
    }
else
    if(Raiz != NULL) //Se a Raiz n�o for nula(Vazia)
    {
        if(Id < Raiz-> Id) //Verifica se a chave informada pelo usu�rio � menor que a chave da Raiz
        {
            Raiz-> Esquerda  = AdicionarNo(Raiz-> Esquerda, Id); //se for menor, chama novamente a fun��o(recursividade), fazendo a �ltima chave(esquerda) apontar para a nova chave
        }
     //Sen�o (veja linha abaixo)
        if(Id > Raiz-> Id) //Verifica se a chave informada pelo usu�rio � maior que a chave da Raiz
        {
            Raiz-> Direita = AdicionarNo(Raiz-> Direita, Id); //sen�o for menor, � maior e chama novamente a fun��o(recursividade), fazendo a �ltima chave(direita) apontar para a nova chave
        }

        /* Passo 2 - Atualiza a altura do novo n� (em rela��o ao anterior) */
        Raiz-> Altura = Maior(Altura(Raiz-> Esquerda), Altura(Raiz-> Direita)) + 1;

        /* Passo 3 - Declarada uma v�ri�vel inteira que tem por objetivo obter o fator de balanceamento deste n� em rela��o ao anterior(pai) para saber se a arvore ficou desbalanceada*/
        int fb = Balanceamento(Raiz); //Verifica o fator de balanceamento

        //Se o novo n� causou desbalanceamento da �rvore, ser� necess�rio obter o balanceamento por meio de uma das 4 formas (dependendo do caso)

        //Rota��o simples � esquerda
        if (fb > 1 && Id < Raiz-> Esquerda-> Id) //Se o fator de balanceamento da Raiz for maior que 1 e o Id informado pelo usu�rio for menor que o Id que est� na Raiz -> Esquerda
            return RotDir(Raiz); //Retorna a Raiz, depois de aplicada a Rota��o � Direita(Fun��o)

        //Rota��o simples � direita
        if (fb < -1 && Id > Raiz-> Direita-> Id)
            return RotEsq(Raiz);

        //Rota��o dupla � esquerda
        if (fb > 1 && Id > Raiz-> Esquerda-> Id)
        {
            Raiz-> Esquerda =  RotEsq(Raiz-> Esquerda);
            return RotDir(Raiz);
        }

        //Rota��o dupla � direita
        if (fb < -1 && Id < Raiz-> Direita-> Id)
        {
            Raiz-> Direita = RotDir(Raiz-> Direita);
            return RotEsq(Raiz);
        } //Fim das rota��es

        /* Passo 4 - Retorna a nova Raiz(alterada) */
        return Raiz;
    }
}

/* Fun��o para buscar um n� e saber se um valor existe na �rvore */
No* BuscarNo(No *Raiz, int Id)
{
    if (Raiz == (No*) NULL) //Se Raiz for igual a nulo
        return NULL; //Retorna Nulo

    if (Raiz-> Id == Id) //Se Id de Raiz for igual a Id passado por par�metro
        return Raiz; //Retorna a pr�pria Raiz pois n�o h� nada a ser feito pois o valor j� existe na �rvore e n�o vamos duplicar esse bagulho, he he, t� gostando dessa parada Brendon

    if (Id > Raiz-> Id) //Se Id(par�metro) for maior que Id de Raiz
        return BuscarNo(Raiz-> Direita, Id); //Chama novamente a fun��o (recursividade) para iserir o valor a direita
    else if (Id < Raiz-> Id) //Caso n�o seja Maior, ent�o � menor e
        return BuscarNo(Raiz-> Esquerda, Id); //chama novamente a fun��o para inserir a esquerda informando os novos par�metros
}

/* Procedimento para exibir (imprimir) os valores na ordem em que foram inseridos aplicando recursividade */
void PreOrdem(No *NoAtual)
{
    if(NoAtual == (No*) NULL) //Se o ponteiro NoAtual do Tipo No(registro) for nulo
        return; //Retorna Nulo
  //Sen�o
    printf("%d ", NoAtual->Id ); //Imprime um inteiro Id de Atual
    PreOrdem(NoAtual-> Esquerda); //E chama novamente a fun��o para imprimir esquerda caso n�o seja nulo
    PreOrdem(NoAtual-> Direita); //E a direita caso n�o seja nulo
}

/* Procedimento para exibir (imprimir) os valores na ordem (maior e menor ao lado do valor) em que foram inseridos aplicando recursividade */
void PosOrdem(No *NoAtual)
{
    if (NoAtual == (No*) NULL) //Se o ponteiro passado como par�mentro for nulo
        return; //Retorna nulo
  //Sen�o
    PosOrdem(NoAtual-> Esquerda); //Chama novamente a fun��o apontando para a esquerda
    PosOrdem(NoAtual-> Direita); //E depois para a direita
    printf("%d ", NoAtual->Id ); //imprimindo o valor
}

/* Procedimento para exibir (imprimir) os valores na ordem em que foram inseridos (tipo pr�-ordem) aplicando recursividade */
void EmOrdem(No *NoAtual) //Varredura e-r-d (= inorder traversal = percurso em in-ordem) Ordem Raiz-Esquerda_Direita.
{
    if (NoAtual == (No*) NULL) //Se o ponteiro NoAtual do tipo No(registro) for nulo
        return; //Retorna nulo
  //Sen�o
    EmOrdem(NoAtual-> Esquerda); //Sen�o chama novamente a fun��o indo para a esquerda
    printf("%d ", NoAtual->Id ); //Imprimindo o Id
    EmOrdem(NoAtual-> Direita); //E depois chamando novamente a fun��o indo para a direita
}

/* Procedimento para exibir (imprimir) os valores na ordem em que foram inseridos (tipo p�s-ordem) aplicando recursividade */


/* Fun��o auxiliar(ser� utilizada pela fun��o RemoverNo) que retorna o menor valor(Id, ou chave) encontrado na �rvore */
No* MenorId(No *Raiz)
{
    No *Atual = Raiz; //Vari�vel Auxiliar do tipo No(registro) � igual a Raiz

    /* Repeti��o(La�o) para baixo at� encontrar a folha mais a esquerda(Menor valor) (A �rvore j� est� balanceada aqui)*/
    while (Atual-> Esquerda != NULL) //Enquanto esquerda de Atual n�o for Nulo
        Atual = Atual-> Esquerda; //Atual recebe (� igual) a Atual -> Esquerda (desce um n�vel na �rvore)

    return Atual; //retorna Atual
}

/* Fun��o para remover o n� da �rvore sem ponteiro para ponteiro */
No* RemoverNo(No *Raiz, int Id)
{
    /* Passo 1 - Executa a remo��o normal */
    if (Raiz == NULL)
        return Raiz;

    if ( Id < Raiz->Id ) //Verifica se a chave informada pelo usu�rio � menor que a chave da Raiz
        Raiz->Esquerda = RemoverNo(Raiz->Esquerda, Id); //se for menor, chama novamente a fun��o(recursividade), fazendo a �ltima chave(esquerda) apontar para a nova chave

else //Sen�o (veja linha abaixo)

    if( Id > Raiz->Id ) //Verifica se a chave informada pelo usu�rio � maior que a chave da Raiz
        Raiz->Direita = RemoverNo(Raiz->Direita, Id); //sen�o for menor, � maior e chama novamente a fun��o(recursividade), fazendo a �ltima chave(direita) apontar para a nova chave

    else //Se n�o � nenhum dos casos acima (maior ou menor), ent�o � igual e este ser� o n� a ser removido
    {
        if( (Raiz->Esquerda == NULL) || (Raiz->Direita == NULL) ) //Verifica se o n� tem pelo menos 1 filho (folha)
        {
            No *Temp = Raiz->Esquerda ? Raiz->Esquerda : Raiz->Direita;

            if(Temp == NULL) //Casos de n�o ter filho
            {
                Temp = Raiz;
                Raiz = NULL;
            }
            else //Sen�o, caso tenha 1 filho
             *Raiz = *Temp; //Copia o conte�do do filho n�o vazi para a Raiz

            free(Temp); //Libera o registro (n�) tempor�rio
        }
        else
        {
            //Caso o n� tenha 2 filhos, obter o menor Id da sub-�rvore direita (poderia ser o maior da sub-�rvore esquerda).
            No *Temp = MenorId(Raiz->Direita);

            //Copia o valor de Id de Temp para a Raiz
            Raiz->Id = Temp->Id;

            //E a direita de raiz passar� a apontar para o resultado da fun��o RemoverNo passando como par�metros a direita de Raiz e o Id de Temp
            Raiz->Direita = RemoverNo(Raiz->Direita, Temp->Id);
        }
    }

    if (Raiz == NULL) //Se a �rvore for nula
      return Raiz; //Retorna ela pr�pria

    /* Passo 2 - Atualiza a altura do novo n� (em rela��o ao anterior) */
    Raiz->Altura = Maior(Altura(Raiz->Esquerda), Altura(Raiz->Direita)) + 1;

    /* Passo 3 - Declarada uma v�ri�vel inteira que tem por objetivo obter o fator de balanceamento deste n� em rela��o ao anterior(pai) para saber se a arvore ficou desbalanceada*/
    int fb = Balanceamento(Raiz);

    //Se o novo n� causou desbalanceamento da �rvore, ser� necess�rio obter o balanceamento por meio de uma das 4 formas (dependendo do caso)

    //Rota��o simples � esquerda
    if (fb > 1 && Balanceamento(Raiz->Esquerda) >= 0)
        return RotDir(Raiz);

    //Rota��o dupla � esquerda
    if (fb > 1 && Balanceamento(Raiz->Esquerda) < 0)
    {
        Raiz->Esquerda =  RotEsq(Raiz->Esquerda);
        return RotDir(Raiz);
    }

    //Rota��o simples � direita
    if (fb < -1 && Balanceamento(Raiz->Direita) <= 0)
        return RotEsq(Raiz);

    //Rota��o dupla � direita
    if (fb < -1 && Balanceamento(Raiz->Direita) > 0)
    {
        Raiz->Direita = RotDir(Raiz->Direita);
        return RotEsq(Raiz);
    }

    return Raiz;
}

void inicializarAleatoriamente(int v[], int n){
    int i;
    for(i = 0; i < n; i++)
        v[i] = rand();
}


int main()
{
    srand(time(NULL));
    configtela(); //Define os par�mentros de tela

	No *Raiz = (No*) NULL; //Define uma vari�vel (ponteiro) do tipo registro (No) como Nula

    int Opt; //Vari�vel que recebe o comando do usu�rio (Menu)
    int v[N], i;
    double start, stop, elapsed;

    inicializarAleatoriamente(v,N);

    do
    {
        int Id; //Recebe o valor a ser inserido na �rvore

        limpa_tela(); //Limpa tela

        menu_principal(); //Imprime o menu principal na tela

        printf("                              1 - Inserir\n");
        printf("                              2 - Buscar\n");
        printf("                              3 - Exibir Pr%c-Ordem\n", 130);
        printf("                              4 - Exibir P%cs-Ordem\n", 162);
        printf("                              5 - Exibir Em-Ordem\n");
        printf("                              6 - Remover\n");
        printf("                              0 - Sair\n\n\n");

        printf("   Informe a op%c%co: ", 135, 198);

        scanf("%d", &Opt);

		fflush(stdin);

        if (Opt == 1)
        {
            start = (double) clock() / CLOCKS_PER_SEC;
            for (i=0 ; i<N ; i++)
                Raiz = AdicionarNo(Raiz, v[i]);
            stop = (double) clock() / CLOCKS_PER_SEC;
            elapsed = stop - start;
            printf("Tempo total em segundos: %f\n", elapsed);
            system("pause");


        }

        if (Opt == 2)
        {
			printf("\n   ");
            if(Raiz != (No*) NULL)
            {
                start = (double) clock() / CLOCKS_PER_SEC;
                for (i=0 ; i<N ; i++)
                    BuscarNo(Raiz, v[i]);
                stop = (double) clock() / CLOCKS_PER_SEC;
                elapsed = stop - start;
                printf("Tempo total em segundos: %f\n", elapsed);
            }

            if(Raiz == (No*) NULL)
            {
                printf("\n\n                                A %crvore est%c vazia!\n\n\n\n\n\n   ", 160, 160);
            }
            system("pause");
        }

        else if (Opt == 3)
        {
            printf("\n   ");
            if(Raiz != (No*) NULL)
            {
                PreOrdem(Raiz);

            }

            if(Raiz == (No*) NULL)
            {
                printf("\n\n                                A %crvore est%c vazia!\n\n\n\n\n\n   ", 160, 160);
            }
            printf("\n");
			system("pause");
        }

        else if (Opt == 4)
        {
            printf("\n   ");
            if(Raiz != (No*) NULL)
            {
                PosOrdem(Raiz);
            }

            if(Raiz == (No*) NULL)
            {
            printf("\n\n                                A %crvore est%c vazia!\n\n\n\n\n\n   ", 160, 160);
            }

            printf("\n");
			system("pause");
        }

        else if (Opt == 5)
        {
            printf("\n   ");
            if(Raiz != (No*) NULL)
            {
                EmOrdem(Raiz);
            }

            if(Raiz == (No*) NULL)
            {
            	printf("\n\n                                A %crvore est%c vazia!\n\n\n\n\n\n   ", 160, 160);
            }

            printf("\n");
            system("pause");
        }

        else if (Opt == 6)
        {
            printf("\n   ");
            if(Raiz != (No*) NULL)
            {
                start = (double) clock() / CLOCKS_PER_SEC;
                for (i=0 ; i<N ; i++)
                    Raiz = RemoverNo(Raiz, v[i]);
                stop = (double) clock() / CLOCKS_PER_SEC;
                elapsed = stop - start;
                printf("Tempo total em segundos: %f\n", elapsed);


            }

            if(Raiz == (No*) NULL)
            {
                printf("\n\n                                A %crvore est%c vazia!\n\n\n\n\n\n   ", 160, 160);
            }

            system("pause");
        }

        else if (Opt > 11 || Opt < 0)
        {
            printf("\n\n                                 Op%c%co Inv%clida!\n\n\n\n\n\n\n  ", 135, 198, 160);
            system("pause");
        }

    } while (Opt != 0);

    return 0;
}
