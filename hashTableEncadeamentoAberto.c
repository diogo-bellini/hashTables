//Bibliotecas
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//Definições
#define SLOTS 1019
#define SLOTS_LINHA 1013
#define NUM_INSERT 500
#define NUM_BUSCA 10
#define C1 3
#define C2 5

typedef struct 
{
    int m;
    int* vetor;
}hash_table;

//Protótipos
void inicializa_tabela(hash_table*);
void insere_tabela(hash_table*, int, int);
int jaTem(hash_table*, int, int);
int linear_probing(int, hash_table*);
int busca_linear(int, hash_table*);
int quadratic_probing(int, hash_table*);
int busca_quadratic(int, hash_table*);
int double_hashing(int, hash_table*);
int busca_double(int, hash_table*);

//Função Principal
int main(){
    srand(time(NULL));

    hash_table minhaTabela1; //Linear
    hash_table minhaTabela2; //Quadratic
    hash_table minhaTabela3; //Double

    inicializa_tabela(&minhaTabela1);
    inicializa_tabela(&minhaTabela2);
    inicializa_tabela(&minhaTabela3);

    //Linear Probing
    printf("\nTABELA USANDO LINEAR PROBING\n");
    int buscas_com_sucesso = 0;
    int buscas_sem_sucesso = 0;
    int somaAcessos = 0;

    //Inserção
    for (int i = 0; i < NUM_INSERT; i++)
    {   
        insere_tabela(&minhaTabela1, 1, (rand() % 2000) + 1);
    }

    //Buscas
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

    //Quadratic Probing
    printf("\nTABELA USANDO QUADRATIC PROBING\n");
    buscas_com_sucesso = 0;
    buscas_sem_sucesso = 0;
    somaAcessos = 0;

    //Inserção
    for (int i = 0; i < NUM_INSERT; i++)
    {   
        insere_tabela(&minhaTabela2, 2, (rand() % 2000) + 1);
    }

    //Buscas
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

    //Double Hashing
    printf("\nTABELA USANDO DOUBLE HASHING\n");
    buscas_com_sucesso = 0;
    buscas_sem_sucesso = 0;
    somaAcessos = 0;

    //Inserção
    for (int i = 0; i < NUM_INSERT; i++)
    {   
        insere_tabela(&minhaTabela3, 3, (rand() % 2000) + 1);
    }

    //Buscas
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

    free(minhaTabela1.vetor);
    free(minhaTabela2.vetor);
    free(minhaTabela3.vetor);

    return 0;
}

//Implementação das Funções
void inicializa_tabela(hash_table* t){
    t->m = SLOTS;
    t->vetor = (int*)calloc(t->m, sizeof(int)); //todos os índices inicializados com zero
}

void insere_tabela(hash_table* t, int tipo, int x){
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
        printf("\nTipo de inserção inválida\n");
}

int jaTem(hash_table* t, int tipo, int x) {
    int index;
    int original_index = x % t->m;

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
        index = ((x % t->m) + i) % t->m;
        if (t->vetor[index] == 0)
        {
            return index;
        }
    }
    return -1; //Tabela cheia
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
            return acessos;
        }
        index = (index + 1) % t->m;
        acessos++;
        if (acessos > t->m)
        {
            break;
        }
    }
    printf("\nO valor %d não está na tabela!!!\n", x);
    printf("Quantidade de acessos necessários: %d\n", acessos);
    return acessos;
}

int quadratic_probing(int x, hash_table* t){
    int index;
    for (int i = 0; i < t->m; i++)
    {
        index = (x % t->m + C1 * i + C2 * i * i) % t->m;
        if (t->vetor[index] == 0)
        {
            return index;
        }
    }
    return -1; // Tabela cheia
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
            return acessos;
        }
        index = (index + C1 * i + C2 * i * i) % t->m;
        acessos++;
        if (acessos > t->m)
        {
            break;
        }
    }
    printf("\nO valor %d não está na tabela!!!\n", x);
    printf("Quantidade de acessos necessários: %d\n", acessos);
    return acessos;
}

int double_hashing(int x, hash_table* t){
    int h1 = x % t->m;
    int h2 = 1 + (x % SLOTS_LINHA);
    int index;

    for (int i = 0; i < t->m; i++)
    {
        index = (h1 + i * h2) % t->m;
        if (t->vetor[index] == 0)
        {
            return index;
        }
    }
    return -1; // Tabela cheia
}

int busca_double(int x, hash_table* t){
    int acessos = 1;
    int h1 = x % t->m;
    int h2 = 1 + (x % SLOTS_LINHA);
    int index;

    for (int i = 0; i < t->m; i++)
    {
        index = (h1 + i * h2) % t->m;
        if (t->vetor[index] == 0) {
            break;  // Se encontrar um slot vazio, o valor não está na tabela
        }
        if (t->vetor[index] == x) {
            printf("\nO valor %d está na tabela!!!\n", x);
            printf("Quantidade de acessos necessários: %d\n", acessos);
            return acessos;
        }
        acessos++;
    }
    printf("\nO valor %d não está na tabela!!!\n", x);
    printf("Quantidade de acessos necessários: %d\n", acessos);
    return acessos;
}