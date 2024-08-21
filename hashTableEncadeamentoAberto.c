//Bibliotecas
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//Definições
#define SLOTS 1019

typedef struct 
{
    int m;
    int* vetor;
}hash_table;

//Protótipos
void inicializa_tabela(hash_table*);
int linear_probing(int, hash_table*);

//Função Principal
int main(){
    srand(time(NULL));

    hash_table minhaTabela;

    inicializa_tabela(&minhaTabela);

    free(minhaTabela.vetor);

    return 0;
}

//Implementação das Funções
void inicializa_tabela(hash_table* t){
    t->m = SLOTS;
    t->vetor = (int*)calloc(t->m, sizeof(int)); //todos os índices inicializados com zero
}

int linear_probing(int x, hash_table* t){
    int index;
    for (int i = 0; i < t->m; i++)
    {
        index = ((x % t->m) + i);
        if (t->vetor[i] == 0)
        {
            t->vetor[i] = x;
            break;
        }
    }  
}