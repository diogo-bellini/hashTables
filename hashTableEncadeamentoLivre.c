//Bibliotecas
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//Definições
#define SLOTS 43
#define NUM_INSERT 500

struct Node_fila
{
    int valor;
    struct Node_fila* prox;
    struct Node_fila* ante;
};

typedef struct Node_fila* ptr_no_fila;

typedef struct{
    int m;
    ptr_no_fila* vetor;
} hash_table;

//Protótipos
void inicializa_tabela(hash_table* tabela);
void insere_fila(ptr_no_fila*, int);
void insere_tabela(hash_table* t,int x);
int funcao_hash(int x);
void imprimir_valores_tabela(hash_table* t);
void busca_tabela(hash_table* t, int x);
int jaTem(hash_table* t, int x);
void liberar_memoria(hash_table* t);

//Função Principal
int main(){
    srand(time(NULL));

    hash_table minhaTabela;
    int buscas_com_sucesso = 0;
    int buscas_sem_sucesso = 0;


    inicializa_tabela(&minhaTabela);

    //Inserções
    for (int i = 0; i < NUM_INSERT; i++)
    {   
        insere_tabela(&minhaTabela, (rand() % 2000) + 1);
    }
    
    //Impressão
    imprimir_valores_tabela(&minhaTabela);

    //Buscas
    while (buscas_com_sucesso < 3)
    {
        int valor = (rand() % 2000) + 1;
        if (jaTem(&minhaTabela, valor))
        {
            busca_tabela(&minhaTabela, valor);
            buscas_com_sucesso++;
        }    
    }

    while (buscas_sem_sucesso < 3)
    {
        int valor = (rand() % 2000) + 1;
        if (!jaTem(&minhaTabela, valor))
        {
            busca_tabela(&minhaTabela, valor);
            buscas_sem_sucesso++;
        }    
    }
    
    //Liberação de memória
    liberar_memoria(&minhaTabela);

    return 0;
}

//Implementação das Funções
void inicializa_tabela(hash_table* tabela) {
    tabela->m = SLOTS;
    tabela->vetor = (ptr_no_fila*)malloc(sizeof(ptr_no_fila) * tabela->m);
    if (tabela->vetor == NULL) {
        printf("Erro ao alocar memória\n");
        exit(1);
    }
    for (int i = 0; i < tabela->m; i++) {
        tabela->vetor[i] = NULL;
    }
}

void insere_fila(ptr_no_fila* f, int x){
    ptr_no_fila aux = (ptr_no_fila)malloc(sizeof(struct Node_fila));
    if (aux == NULL)
    {
        printf("Erro ao alocar memória\n");
        return;
    }
    aux->valor = x;
    aux->prox = NULL;
    aux->ante = NULL;

    if (*f == NULL)
    {
        *f = aux;
    }
    else
    {
        while ((*f)->prox != NULL)
        {
            *f = (*f)->prox;
        }
        aux->ante = *f;
        (*f)->prox = aux;
    }
}

void insere_tabela(hash_table* t,int x){
    if (!jaTem(t, x))
    {
        insere_fila(&(t->vetor[funcao_hash(x)]), x);
    }
    else
        printf("O valor já %d está na tabela!!!\n", x);
}

//Método da divisão
int funcao_hash(int x){
    return x % SLOTS;
}

void imprimir_valores_tabela(hash_table* t){
    for (int i = 0; i < t->m; i++)
    {
        ptr_no_fila aux = t->vetor[i];
        if (aux != NULL)
        {
            int soma = 0;
            int qtd = 0;

            printf("Fila %d:\n", i);
            while (aux != NULL)
            {
                printf("%d ", aux->valor);
                soma += aux->valor;
                qtd++;
                aux = aux->prox;
            }
            printf("\nTamanho da fila: %d\n", qtd);
            printf("Média da fila: %d\n", soma/qtd);
            printf("\n");
        }
    }
}

void busca_tabela(hash_table* t, int x){
    int index = funcao_hash(x);
    ptr_no_fila aux = t->vetor[index];
    int acessos = 1;

    while (aux != NULL)
    {
        if (aux->valor == x)
        {
            printf("\nO valor %d está na tabela!!!\n", x);
            printf("Quantidade de acessos necessários: %d\n", acessos);
            return;
        }
        aux = aux->prox;
        acessos++;
    }
    printf("\nO valor %d não está na tabela!!!\n", x);
    printf("Quantidade de acessos necessários: %d\n", acessos);
}

int jaTem(hash_table* t, int x){
    int index = funcao_hash(x);
    ptr_no_fila aux = t->vetor[index];

    while (aux != NULL)
    {
        if (aux->valor == x)
            return 1;
        aux = aux->prox;
    }
    return 0;
}

void liberar_memoria(hash_table* t) {
    for (int i = 0; i < t->m; i++) {
        ptr_no_fila aux = t->vetor[i];
        while (aux != NULL) {
            ptr_no_fila temp = aux;
            aux = aux->prox;
            free(temp);
        }
    }
    free(t->vetor);
}