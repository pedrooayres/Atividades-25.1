#include <stdio.h>
#include <stdlib.h>

#define TAM 10

// Estrutura do nó
typedef struct No {
    int valor;
    struct No* prox;
} No;

// Inserir no início (questão 8)
void inserir(No* tabela[], int valor) {
    int indice = valor % TAM;
    No* novo = (No*) malloc(sizeof(No));
    if (novo == NULL) {
        printf("Erro de alocação de memória.\n");
        return;
    }
    novo->valor = valor;
    novo->prox = tabela[indice];
    tabela[indice] = novo;
}

// Inserir no final (questão 9)
void inserir_final(No* tabela[], int valor) {
    int indice = valor % TAM;
    No* novo = (No*) malloc(sizeof(No));
    if (novo == NULL) {
        printf("Erro de alocação de memória.\n");
        return;
    }
    novo->valor = valor;
    novo->prox = NULL;

    if (tabela[indice] == NULL) {
        tabela[indice] = novo;
    } else {
        No* aux = tabela[indice];
        while (aux->prox != NULL) {
            aux = aux->prox;
        }
        aux->prox = novo;
    }
}

// Imprimir tabela hash (questão 10)
void imprimir(No* tabela[]) {
    for (int i = 0; i < TAM; i++) {
        printf("[%d]: ", i);
        No* aux = tabela[i];
        while (aux != NULL) {
            printf("%d -> ", aux->valor);
            aux = aux->prox;
        }
        printf("NULL\n");
    }
}

// Verificar se chave existe (questão 11)
int chave_existe(No* tabela[], int valor) {
    int indice = valor % TAM;
    No* aux = tabela[indice];
    while (aux != NULL) {
        if (aux->valor == valor)
            return 1;
        aux = aux->prox;
    }
    return 0;
}

// Calcular taxa de ocupação (questão 12)
float taxa_ocupacao(No* tabela[]) {
    int ocupadas = 0;
    for (int i = 0; i < TAM; i++) {
        if (tabela[i] != NULL)
            ocupadas++;
    }
    return (float)ocupadas / TAM;
}

// Contar colisões (questão 13)
int contar_colisoes(No* tabela[]) {
    int colisoes = 0;
    for (int i = 0; i < TAM; i++) {
        No* aux = tabela[i];
        int count = 0;
        while (aux != NULL) {
            count++;
            aux = aux->prox;
        }
        if (count > 1)
            colisoes += (count - 1);
    }
    return colisoes;
}

// Contar total de elementos (questão 14)
int contar_elementos(No* tabela[]) {
    int total = 0;
    for (int i = 0; i < TAM; i++) {
        No* aux = tabela[i];
        while (aux != NULL) {
            total++;
            aux = aux->prox;
        }
    }
    return total;
}

// Função principal para testar tudo
int main() {
    // Inicializa a tabela com NULL
    No* tabela[TAM];
    for (int i = 0; i < TAM; i++) {
        tabela[i] = NULL;
    }

    // Teste de inserções
    inserir(tabela, 15);
    inserir(tabela, 25);
    inserir(tabela, 35);
    inserir(tabela, 5);
    inserir(tabela, 22);
    inserir_final(tabela, 32);
    inserir_final(tabela, 42);

    // Impressão da tabela
    printf("\nTabela Hash:\n");
    imprimir(tabela);

    // Testes de funções auxiliares
    printf("\nChave 25 existe? %s\n", chave_existe(tabela, 25) ? "Sim" : "Não");
    printf("Chave 99 existe? %s\n", chave_existe(tabela, 99) ? "Sim" : "Não");

    printf("\nTaxa de ocupação: %.2f\n", taxa_ocupacao(tabela));
    printf("Total de colisões: %d\n", contar_colisoes(tabela));
    printf("Total de elementos: %d\n", contar_elementos(tabela));

    // Liberação de memória
    for (int i = 0; i < TAM; i++) {
        No* atual = tabela[i];
        while (atual != NULL) {
            No* temp = atual;
            atual = atual->prox;
            free(temp);
        }
    }

    return 0;
}
