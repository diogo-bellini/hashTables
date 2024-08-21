// Bibliotecas
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Definições
#define SLOTS 43          // Número de slots na tabela hash
#define NUM_INSERT 500    // Número de inserções na tabela hash

// Estrutura para representar um nó na fila
struct Node_fila
{
    int valor;           // Valor armazenado no nó
    struct Node_fila* prox; // Ponteiro para o próximo nó na fila
    struct Node_fila* ante; // Ponteiro para o nó anterior na fila
};

typedef struct Node_fila* ptr_no_fila; // Tipo para ponteiro para nó da fila

// Estrutura para a tabela hash usando listas encadeadas
typedef struct{
    int m;                // Número de slots na tabela hash
    ptr_no_fila* vetor;   // Vetor de ponteiros para as listas encadeadas
} hash_table;

// Protótipos das funções
void inicializa_tabela(hash_table* tabela);
void insere_fila(ptr_no_fila*, int);
void insere_tabela(hash_table* t, int x);
int funcao_hash(int x);
void imprimir_valores_tabela(hash_table* t);
void busca_tabela(hash_table* t, int x);
int jaTem(hash_table* t, int x);
void liberar_memoria(hash_table* t);

// Função Principal
int main(){
    srand(time(NULL)); // Inicializa o gerador de números aleatórios

    hash_table minhaTabela;  // Declaração da tabela hash
    int buscas_com_sucesso = 0; // Contador para buscas bem-sucedidas
    int buscas_sem_sucesso = 0; // Contador para buscas sem sucesso

    inicializa_tabela(&minhaTabela); // Inicializa a tabela hash

    // Inserções na tabela hash
    for (int i = 0; i < NUM_INSERT; i++)
    {   
        insere_tabela(&minhaTabela, (rand() % 2000) + 1); // Insere valores aleatórios na tabela
    }
    
    // Impressão dos valores da tabela hash
    imprimir_valores_tabela(&minhaTabela);

    // Buscas bem-sucedidas
    while (buscas_com_sucesso < 3)
    {
        int valor = (rand() % 2000) + 1;
        if (jaTem(&minhaTabela, valor)) // Verifica se o valor está na tabela
        {
            busca_tabela(&minhaTabela, valor); // Busca o valor na tabela
            buscas_com_sucesso++;
        }    
    }

    // Buscas sem sucesso
    while (buscas_sem_sucesso < 3)
    {
        int valor = (rand() % 2000) + 1;
        if (!jaTem(&minhaTabela, valor)) // Verifica se o valor não está na tabela
        {
            busca_tabela(&minhaTabela, valor); // Busca o valor na tabela
            buscas_sem_sucesso++;
        }    
    }
    
    // Liberação de memória alocada
    liberar_memoria(&minhaTabela);

    return 0;
}

// Função para inicializar a tabela hash
void inicializa_tabela(hash_table* tabela) {
    tabela->m = SLOTS; // Define o número de slots
    tabela->vetor = (ptr_no_fila*)malloc(sizeof(ptr_no_fila) * tabela->m); // Aloca memória para o vetor de listas encadeadas
    if (tabela->vetor == NULL) {
        printf("Erro ao alocar memória\n");
        exit(1);
    }
    for (int i = 0; i < tabela->m; i++) {
        tabela->vetor[i] = NULL; // Inicializa cada lista como NULL
    }
}

// Função para inserir um valor em uma lista encadeada (fila)
void insere_fila(ptr_no_fila* f, int x){
    ptr_no_fila aux = (ptr_no_fila)malloc(sizeof(struct Node_fila)); // Aloca memória para o novo nó
    if (aux == NULL)
    {
        printf("Erro ao alocar memória\n");
        return;
    }
    aux->valor = x; // Define o valor do nó
    aux->prox = NULL; // Inicializa o ponteiro para o próximo nó como NULL
    aux->ante = NULL; // Inicializa o ponteiro para o nó anterior como NULL

    if (*f == NULL)
    {
        *f = aux; // Se a fila estiver vazia, o novo nó é o primeiro
    }
    else
    {
        while ((*f)->prox != NULL)
        {
            *f = (*f)->prox; // Navega até o final da fila
        }
        aux->ante = *f; // Define o nó anterior
        (*f)->prox = aux; // Adiciona o novo nó ao final da fila
    }
}

// Função para inserir um valor na tabela hash
void insere_tabela(hash_table* t, int x){
    if (!jaTem(t, x))
    {
        insere_fila(&(t->vetor[funcao_hash(x)]), x); // Insere o valor na fila apropriada
    }
    //else
        //printf("O valor já %d está na tabela!!!\n", x);
}

// Função de hash usando o método da divisão
int funcao_hash(int x){
    return x % SLOTS; // Retorna o índice do slot para o valor
}

// Função para imprimir os valores e estatísticas de cada fila na tabela hash
void imprimir_valores_tabela(hash_table* t){
    for (int i = 0; i < t->m; i++)
    {
        ptr_no_fila aux = t->vetor[i];
        if (aux != NULL)
        {
            int soma = 0;
            int qtd = 0;

            printf("Fila %d:\n", i); // Imprime o índice da fila
            while (aux != NULL)
            {
                printf("%d ", aux->valor); // Imprime o valor do nó
                soma += aux->valor; // Soma os valores para calcular a média
                qtd++; // Conta o número de elementos
                aux = aux->prox; // Avança para o próximo nó
            }
            printf("\nTamanho da fila: %d\n", qtd); // Imprime o tamanho da fila
            printf("Média da fila: %.2f\n", (float)soma/qtd); // Imprime a média dos valores
            printf("\n");
        }
    }
}

// Função para buscar um valor na tabela hash
void busca_tabela(hash_table* t, int x){
    int index = funcao_hash(x); // Obtém o índice da fila usando a função de hash
    ptr_no_fila aux = t->vetor[index]; // Obtém a fila correspondente
    int acessos = 1; // Conta o número de acessos

    while (aux != NULL)
    {
        if (aux->valor == x)
        {
            printf("\nO valor %d está na tabela!!!\n", x);
            printf("Quantidade de acessos necessários: %d\n", acessos); // Imprime a quantidade de acessos
            return;
        }
        aux = aux->prox; // Avança para o próximo nó
        acessos++; // Incrementa o contador de acessos
    }
    printf("\nO valor %d não está na tabela!!!\n", x);
    printf("Quantidade de acessos necessários: %d\n", acessos); // Imprime a quantidade de acessos
}

// Função para verificar se um valor já está na tabela hash
int jaTem(hash_table* t, int x){
    int index = funcao_hash(x); // Obtém o índice da fila usando a função de hash
    ptr_no_fila aux = t->vetor[index]; // Obtém a fila correspondente

    while (aux != NULL)
    {
        if (aux->valor == x)
            return 1; // O valor está na tabela
        aux = aux->prox; // Avança para o próximo nó
    }
    return 0; // O valor não está na tabela
}

// Função para liberar a memória alocada para a tabela hash
void liberar_memoria(hash_table* t) {
    for (int i = 0; i < t->m; i++) {
        ptr_no_fila aux = t->vetor[i];
        while (aux != NULL) {
            ptr_no_fila temp = aux; // Guarda o nó atual
            aux = aux->prox; // Avança para o próximo nó
            free(temp); // Libera a memória do nó atual
        }
    }
    free(t->vetor); // Libera a memória alocada para o vetor de filas
}
