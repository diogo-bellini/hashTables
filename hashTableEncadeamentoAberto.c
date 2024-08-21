//Bibliotecas
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//Definições
#define SLOTS 1019          // Tamanho da tabela para hashing
#define SLOTS_LINHA 1013    // Tamanho da tabela auxiliar para double hashing
#define NUM_INSERT 500      // Número de inserções a serem realizadas
#define NUM_BUSCA 10        // Número de buscas a serem realizadas
#define C1 3                // Coeficiente C1 para probing quadrático
#define C2 5                // Coeficiente C2 para probing quadrático

typedef struct 
{
    int m;                  // Tamanho da tabela hash
    int* vetor;             // Vetor que representa a tabela hash
} hash_table;

//Protótipos
void inicializa_tabela(hash_table*);                    // Função para inicializar a tabela hash
void insere_tabela(hash_table*, int, int);               // Função para inserir um valor na tabela hash
int jaTem(hash_table*, int, int);                        // Função para verificar se um valor está na tabela hash
int linear_probing(int, hash_table*);                    // Função para cálculo do índice com probing linear
int busca_linear(int, hash_table*);                      // Função para busca linear na tabela hash
int quadratic_probing(int, hash_table*);                  // Função para cálculo do índice com probing quadrático
int busca_quadratic(int, hash_table*);                    // Função para busca com probing quadrático na tabela hash
int double_hashing(int, hash_table*);                     // Função para cálculo do índice com double hashing
int busca_double(int, hash_table*);                       // Função para busca com double hashing na tabela hash

//Função Principal
int main(){
    srand(time(NULL));  // Inicializa o gerador de números aleatórios com a hora atual

    hash_table minhaTabela1; //Tabela para Linear Probing
    hash_table minhaTabela2; //Tabela para Quadratic Probing
    hash_table minhaTabela3; //Tabela para Double Hashing

    // Inicializa as tabelas hash
    inicializa_tabela(&minhaTabela1);
    inicializa_tabela(&minhaTabela2);
    inicializa_tabela(&minhaTabela3);

    // Linear Probing
    printf("\nTABELA USANDO LINEAR PROBING\n");
    int buscas_com_sucesso = 0;
    int buscas_sem_sucesso = 0;
    int somaAcessos = 0;

    // Inserção de valores na tabela usando linear probing
    for (int i = 0; i < NUM_INSERT; i++)
    {   
        insere_tabela(&minhaTabela1, 1, (rand() % 2000) + 1);
    }

    // Busca de valores com sucesso na tabela
    while (buscas_com_sucesso < NUM_BUSCA)
    {
        int valor = (rand() % 2000) + 1;
        if (jaTem(&minhaTabela1, 1, valor))
        {
            somaAcessos += busca_linear(valor, &minhaTabela1);
            buscas_com_sucesso++;
        }    
    }
    printf("\nMédia de acessos: %.2f\n", (float)somaAcessos/NUM_BUSCA);
    somaAcessos = 0;

    // Busca de valores sem sucesso na tabela
    while (buscas_sem_sucesso < NUM_BUSCA)
    {
        int valor = (rand() % 2000) + 1;
        if (!jaTem(&minhaTabela1, 1, valor))
        {
            somaAcessos += busca_linear(valor, &minhaTabela1);
            buscas_sem_sucesso++;
        } 
    }
    printf("\nMédia de acessos: %.2f\n", (float)somaAcessos/NUM_BUSCA);

    // Quadratic Probing
    printf("\nTABELA USANDO QUADRATIC PROBING\n");
    buscas_com_sucesso = 0;
    buscas_sem_sucesso = 0;
    somaAcessos = 0;

    // Inserção de valores na tabela usando quadratic probing
    for (int i = 0; i < NUM_INSERT; i++)
    {   
        insere_tabela(&minhaTabela2, 2, (rand() % 2000) + 1);
    }

    // Busca de valores com sucesso na tabela
    while (buscas_com_sucesso < NUM_BUSCA)
    {
        int valor = (rand() % 2000) + 1;
        if (jaTem(&minhaTabela2, 2, valor))
        {
            somaAcessos += busca_quadratic(valor, &minhaTabela2);
            buscas_com_sucesso++;
        }    
    }
    printf("\nMédia de acessos: %.2f\n", (float)somaAcessos/NUM_BUSCA);
    somaAcessos = 0;

    // Busca de valores sem sucesso na tabela
    while (buscas_sem_sucesso < NUM_BUSCA)
    {
        int valor = (rand() % 2000) + 1;
        if (!jaTem(&minhaTabela2, 2, valor))
        {
            somaAcessos += busca_quadratic(valor, &minhaTabela2);
            buscas_sem_sucesso++;
        } 
    }
    printf("\nMédia de acessos: %.2f\n", (float)somaAcessos/NUM_BUSCA);

    // Double Hashing
    printf("\nTABELA USANDO DOUBLE HASHING\n");
    buscas_com_sucesso = 0;
    buscas_sem_sucesso = 0;
    somaAcessos = 0;

    // Inserção de valores na tabela usando double hashing
    for (int i = 0; i < NUM_INSERT; i++)
    {   
        insere_tabela(&minhaTabela3, 3, (rand() % 2000) + 1);
    }

    // Busca de valores com sucesso na tabela
    while (buscas_com_sucesso < NUM_BUSCA)
    {
        int valor = (rand() % 2000) + 1;
        if (jaTem(&minhaTabela3, 3, valor))
        {
            somaAcessos += busca_double(valor, &minhaTabela3);
            buscas_com_sucesso++;
        }    
    }
    printf("\nMédia de acessos: %.2f\n", (float)somaAcessos/NUM_BUSCA);
    somaAcessos = 0;

    // Busca de valores sem sucesso na tabela
    while (buscas_sem_sucesso < NUM_BUSCA)
    {
        int valor = (rand() % 2000) + 1;
        if (!jaTem(&minhaTabela3, 3, valor))
        {
            somaAcessos += busca_double(valor, &minhaTabela3);
            buscas_sem_sucesso++;
        } 
    }
    printf("\nMédia de acessos: %.2f\n", (float)somaAcessos/NUM_BUSCA);

    // Liberação da memória alocada para as tabelas
    free(minhaTabela1.vetor);
    free(minhaTabela2.vetor);
    free(minhaTabela3.vetor);

    return 0;
}

//Implementação das Funções
void inicializa_tabela(hash_table* t){
    t->m = SLOTS;                   // Define o tamanho da tabela
    t->vetor = (int*)calloc(t->m, sizeof(int)); // Inicializa todos os índices com zero
}

void insere_tabela(hash_table* t, int tipo, int x){
    // Insere o valor na tabela de acordo com o tipo de hashing
    if (tipo == 1)
    {
        if(!jaTem(t, tipo, x))
            t->vetor[linear_probing(x, t)] = x;
    }
    else if(tipo == 2)
    {
        if (!jaTem(t, tipo, x))
            t->vetor[quadratic_probing(x, t)] = x;
    }
    else if(tipo == 3)
    {
        if (!jaTem(t, tipo, x))
            t->vetor[double_hashing(x, t)] = x;
    }
    else
        printf("\nTipo de inserção inválida\n");  // Caso o tipo de hashing seja inválido
}

int jaTem(hash_table* t, int tipo, int x) {
    int index;
    int original_index = x % t->m;  // Índice original com base no valor do hash

    // Verifica se o valor está na tabela com base no tipo de hashing
    for (int i = 0; i < t->m; i++) {
        if (tipo == 1) {
            index = (original_index + i) % t->m; // Linear probing
        } else if (tipo == 2) {
            index = (original_index + C1 * i + C2 * i * i) % t->m; // Quadratic probing
        } else if (tipo == 3) {
            int h2 = 1 + (x % SLOTS_LINHA);
            index = (original_index + i * h2) % t->m; // Double hashing
        }

        // Se encontramos um slot vazio, o valor não está na tabela
        if (t->vetor[index] == 0) {
            return 0; // Não encontrado
        }

        // Se encontramos o valor, ele está na tabela
        if (t->vetor[index] == x) {
            return 1; // Encontrado
        }
    }

    return 0; // Não encontrado
}

int linear_probing(int x, hash_table* t){
    int index;
    for (int i = 0; i < t->m; i++)
    {
        index = ((x % t->m) + i) % t->m;  // Calcula o índice com linear probing
        if (t->vetor[index] == 0)
        {
            return index;  // Retorna o índice disponível
        }
    }
    return -1; // Retorna -1 se a tabela estiver cheia
}

int busca_linear(int x, hash_table* t){
    int acessos = 1;
    int index = x % t->m;

    while (t->vetor[index] != 0)
    {
        if (t->vetor[index] == x)
        {
            printf("\nO valor %d está na tabela!!!\n", x);
            printf("Quantidade de acessos necessários: %d\n", acessos);
            return acessos;  // Retorna a quantidade de acessos se o valor for encontrado
        }
        index = (index + 1) % t->m;  // Avança para o próximo índice
        acessos++;
        if (acessos > t->m)
        {
            break;  // Sai do loop se a tabela estiver cheia
        }
    }
    printf("\nO valor %d não está na tabela!!!\n", x);
    printf("Quantidade de acessos necessários: %d\n", acessos);
    return acessos;  // Retorna a quantidade de acessos mesmo se o valor não for encontrado
}

int quadratic_probing(int x, hash_table* t){
    int index;
    for (int i = 0; i < t->m; i++)
    {
        index = (x % t->m + C1 * i + C2 * i * i) % t->m;  // Calcula o índice com quadratic probing
        if (t->vetor[index] == 0)
        {
            return index;  // Retorna o índice disponível
        }
    }
    return -1; // Retorna -1 se a tabela estiver cheia
}

int busca_quadratic(int x, hash_table* t){
    int acessos = 1;
    int index = x % t->m;

    for (int i = 0; i < t->m; i++)
    {
        if (t->vetor[index] == 0) {
            break;  // Se encontrar um slot vazio, o valor não está na tabela
        }

        if (t->vetor[index] == x)
        {
            printf("\nO valor %d está na tabela!!!\n", x);
            printf("Quantidade de acessos necessários: %d\n", acessos);
            return acessos;  // Retorna a quantidade de acessos se o valor for encontrado
        }
        index = (index + C1 * i + C2 * i * i) % t->m;  // Avança para o próximo índice com quadratic probing
        acessos++;
        if (acessos > t->m)
        {
            break;  // Sai do loop se a tabela estiver cheia
        }
    }
    printf("\nO valor %d não está na tabela!!!\n", x);
    printf("Quantidade de acessos necessários: %d\n", acessos);
    return acessos;  // Retorna a quantidade de acessos mesmo se o valor não for encontrado
}

int double_hashing(int x, hash_table* t){
    int h1 = x % t->m;
    int h2 = 1 + (x % SLOTS_LINHA);  // Calcula o segundo hash para double hashing
    int index;

    for (int i = 0; i < t->m; i++)
    {
        index = (h1 + i * h2) % t->m;  // Calcula o índice com double hashing
        if (t->vetor[index] == 0)
        {
            return index;  // Retorna o índice disponível
        }
    }
    return -1; // Retorna -1 se a tabela estiver cheia
}

int busca_double(int x, hash_table* t){
    int acessos = 1;
    int h1 = x % t->m;
    int h2 = 1 + (x % SLOTS_LINHA);  // Calcula o segundo hash para double hashing
    int index;

    for (int i = 0; i < t->m; i++)
    {
        index = (h1 + i * h2) % t->m;  // Calcula o índice com double hashing
        if (t->vetor[index] == 0) {
            break;  // Se encontrar um slot vazio, o valor não está na tabela
        }
        if (t->vetor[index] == x) {
            printf("\nO valor %d está na tabela!!!\n", x);
            printf("Quantidade de acessos necessários: %d\n", acessos);
            return acessos;  // Retorna a quantidade de acessos se o valor for encontrado
        }
        acessos++;
    }
    printf("\nO valor %d não está na tabela!!!\n", x);
    printf("Quantidade de acessos necessários: %d\n", acessos);
    return acessos;  // Retorna a quantidade de acessos mesmo se o valor não for encontrado
}
