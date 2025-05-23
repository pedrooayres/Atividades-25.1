// estrurura basica do no
# define TAM 10
# include <stdio.h>
# include <stdlib.h>

typedef struct No{
    int valor;
    struct No* prox;
}No;

// inserir no incio da lista(8º questão)
void inserir(No* tabela[],int valor){
    int indice = valor % TAM;
    No* novo = (No*) malloc(sizeof(No));
    novo -> valor = valor;
    novo -> prox = tabela[indice];
    tabela[indice] = novo;
}
// inserir no final da lista(9º questão)
void inserirFinal(No* tabela[], int valor){
    int indice = valor % TAM;
    No* novo = (No*) malloc(sizeof(No));
    novo -> valor = valor;
    novo -> prox = NULL;
    if(tabela[indice] == NULL){
        tabela[indice] = novo;
    }else{
        No* aux = tabela[indice];
        while(aux -> prox != NULL){
            aux = aux -> prox;
        }
        aux -> prox = novo;
    }
}