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
// imprimir lista(10º questão)
void imprimir(No* tabela[]){
    for(int i = 0; i < TAM; i++){
        printf("%d: ", i);
        No* aux = tabela[i];
        while(aux != NULL){
            printf("%d ", aux -> valor);
            aux = aux -> prox;
        }
        printf("\n");
    }
}
// verificar chave(11º questão)
int chave_existe(No* tabela[], int valor){
    int indice = valor % TAM;
    No* aux = tabela[indice];
    while(aux != NULL){
        if(aux -> valor == valor){
            return 1;
        }
        aux = aux -> prox;
    }
    return 0;
}
// taxa de ocupação(12º questão)
float taxa_ocupacao(No* tabela[]){
    int oucupadas = 0;
    for(int i = 0; i < TAM; i++){
        No* aux = tabela[i];
        while(aux != NULL){
            oucupadas++;
            aux = aux -> prox;
        }
    }
    return (float) oucupadas / TAM;
}
// oucupadasar colisões (13º questão)
int contar_colisoes(No* tabela[]){
    int colisoes = 0;
    for(int i = 0; i < TAM; i++){
        No* aux = tabela[i];
        while(aux != NULL){
            if(aux -> prox != NULL){
                colisoes++;
            }
            aux = aux -> prox;
        }
    }
    return colisoes;
}
// contar total de elementos(14º questão)
int contar_elementos(No* tabela[]){
    int elementos = 0;
    for(int i = 0; i < TAM; i++){
        No* aux = tabela[i];
        while(aux != NULL){
            elementos++;
            aux = aux -> prox;
        }
    }
    return elementos;
}