
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int codigo;
    char nome[50];
    float preco;
    int quantidade;
    int ativo; // 1 = ativo, 0 = removido
} Produto;


void cadastrar_produto(FILE* f) {
    Produto p;

    printf("Codigo: ");
    scanf("%d", &p.codigo);
    getchar(); // Limpar buffer
    printf("Nome: ");
    fgets(p.nome, 50, stdin);
    p.nome[strcspn(p.nome, "\n")] = '\0';
    printf("Preco: ");
    scanf("%f", &p.preco);
    printf("Quantidade: ");
    scanf("%d", &p.quantidade);
    p.ativo = 1;

    // Grava no arquivo binário
    f = fopen("produtos.dat", "ab");
    if (!f) {
        perror("Erro ao abrir o arquivo binario");
        return;
    }
    fwrite(&p, sizeof(Produto), 1, f);
    fclose(f);

    // Grava também no arquivo de texto
    FILE* txt = fopen("produtos.txt", "a");
    if (!txt) {
        perror("Erro ao abrir o arquivo de texto");
        return;
    }
    fprintf(txt, "Codigo: %d\nNome: %s\nPreco: %.2f\nQuantidade: %d\n\n",
            p.codigo, p.nome, p.preco, p.quantidade);
    fclose(txt);

    printf("Produto cadastrado com sucesso.\n");
}



void listar_produtos(FILE* f) {
    Produto p;
    f = fopen("produtos.dat", "rb");
    if (!f) {
        perror("Erro ao abrir o arquivo");
        return;
    }

    printf("\n--- Lista de Produtos Ativos ---\n");
    while (fread(&p, sizeof(Produto), 1, f)) {
        if (p.ativo) {
            printf("Codigo: %d\nNome: %s\nPreco: %.2f\nQuantidade: %d\n\n",
                   p.codigo, p.nome, p.preco, p.quantidade);
        }
    }
    fclose(f);
}


void buscar_produto(FILE* f) {
    int codigo;
    Produto p;

    printf("Digite o codigo do produto: ");
    scanf("%d", &codigo);
    f = fopen("produtos.dat", "rb");
    if (!f) {
        perror("Erro ao abrir o arquivo");
        return;
    }


    int encontrado = 0;
    while (fread(&p, sizeof(Produto), 1, f)) {
        if (p.ativo && p.codigo == codigo) {
            printf("Produto encontrado:\n");
            printf("Nome: %s\nPreco: %.2f\nQuantidade: %d\n", p.nome, p.preco, p.quantidade);
            encontrado = 1;
            break;
        }
    }
    if (!encontrado) {
        printf("Produto não encontrado.\n");
    }
    fclose(f);

}
    void atualizar_produto(FILE* f) {
    int codigo;
    Produto p;
    int encontrado = 0;

    printf("Digite o codigo do produto a atualizar: ");
    scanf("%d", &codigo);

    f = fopen("produtos.dat", "r+b");
    if (!f) {
        perror("Erro ao abrir o arquivo");
        return;
    }

    while (fread(&p, sizeof(Produto), 1, f)) {
        if (p.ativo && p.codigo == codigo) {
            printf("Produto encontrado. Digite os novos dados:\n");

            getchar();
            printf("Novo nome: ");
            fgets(p.nome, 50, stdin);
            p.nome[strcspn(p.nome, "\n")] = '\0';

            printf("Novo preco: ");
            scanf("%f", &p.preco);
            printf("Nova quantidade: ");
            scanf("%d", &p.quantidade);

            fseek(f, -sizeof(Produto), SEEK_CUR);
            fwrite(&p, sizeof(Produto), 1, f);

            printf("Produto atualizado com sucesso.\n");
            encontrado = 1;
            break;
        }
    }

    if (!encontrado) {
        printf("Produto com o codigo %d nao encontrado.\n", codigo);
    }

    fclose(f);
}void remover_produto(FILE* f) {
    int codigo;
    Produto p;
    int encontrado = 0;

    printf("Digite o codigo do produto a remover: ");
    scanf("%d", &codigo);

    f = fopen("produtos.dat", "r+b");
    if (!f) {
        perror("Erro ao abrir o arquivo");
        return;
    }

    while (fread(&p, sizeof(Produto), 1, f)) {
        if (p.ativo && p.codigo == codigo) {
            p.ativo = 0;
            fseek(f, -sizeof(Produto), SEEK_CUR);
            fwrite(&p, sizeof(Produto), 1, f);

            printf("Produto removido com sucesso.\n");
            encontrado = 1;
            break;
        }
    }

    if (!encontrado) {
        printf("Produto com o codigo %d nao encontrado.\n", codigo);
    }

    fclose(f);
}

int main() {
    FILE* f = NULL;
    int opcao;

    do {
        printf("\n--- Menu ---\n");
        printf("1. Cadastrar produto\n");
        printf("2. Listar produtos\n");
        printf("3. Buscar produto por codigo\n");
        printf("4. Atualizar produto\n");
        printf("5. Remover produto\n");
        printf("6. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        switch (opcao) {
            case 1: cadastrar_produto(f); break;
            case 2: listar_produtos(f); break;
            case 3: buscar_produto(f); break;
            case 4: atualizar_produto(f); break;
            case 5: remover_produto(f); break;
            case 6: printf("Saindo...\n"); break;
            default: printf("Opcao invalida!\n");
        }
    } while (opcao != 6);

    return 0;
}
