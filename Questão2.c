#include <stdio.h>
#include <string.h>

#define PRODUTOS 40

typedef struct {
    int codigo;
    char descricao[50];
    float valorUnitario;
    int quantidade;
} Produto;

void cadastrarProduto(Produto produtos[], int *quantidadeAtual) {
    if (*quantidadeAtual >= PRODUTOS) {
        printf("Limite de produtos atingido.\n");
        return;
    }
    printf("Digite o código do produto: ");
    scanf("%d", &produtos[*quantidadeAtual].codigo);
    printf("Digite a descrição do produto: ");
    scanf(" %[^\n]s", produtos[*quantidadeAtual].descricao);
    printf("Digite o valor unitário: ");
    scanf("%f", &produtos[*quantidadeAtual].valorUnitario);
    printf("Digite a quantidade em estoque: ");
    scanf("%d", &produtos[*quantidadeAtual].quantidade);
    (*quantidadeAtual)++;
}

void alterarValorProduto(Produto produtos[], int quantidade) {
    int codigo, encontrado = 0;
    float novoValor;
    printf("Digite o código do produto para alterar o valor: ");
    scanf("%d", &codigo);
    for (int i = 0; i < quantidade; i++) {
        if (produtos[i].codigo == codigo) {
            printf("Digite o novo valor unitário: ");
            scanf("%f", &novoValor);
            produtos[i].valorUnitario = novoValor;
            encontrado = 1;
            break;
        }
    }
    if (!encontrado) {
        printf("Produto não encontrado.\n");
    }
}

float consultarValorProduto(Produto produtos[], int quantidade) {
    int codigo;
    printf("Digite o código do produto para consultar o valor: ");
    scanf("%d", &codigo);
    for (int i = 0; i < quantidade; i++) {
        if (produtos[i].codigo == codigo) {
            return produtos[i].valorUnitario;
        }
    }
    printf("Produto não encontrado.\n");
    return 0.0;
}

int consultarEstoqueProduto(Produto produtos[], int quantidade) {
    int codigo;
    printf("Digite o código do produto para consultar a quantidade em estoque: ");
    scanf("%d", &codigo);
    for (int i = 0; i < quantidade; i++) {
        if (produtos[i].codigo == codigo) {
            return produtos[i].quantidade;
        }
    }
    printf("Produto não encontrado.\n");
    return -1;
}

void venderProduto(Produto produtos[], int quantidade) {
    int codigo, quantidadeDesejada, encontrado = 0;
    printf("Digite o código do produto para venda: ");
    scanf("%d", &codigo);
    for (int i = 0; i < quantidade; i++) {
        if (produtos[i].codigo == codigo) {
            printf("Digite a quantidade desejada: ");
            scanf("%d", &quantidadeDesejada);
            if (produtos[i].quantidade >= quantidadeDesejada) {
                produtos[i].quantidade -= quantidadeDesejada;
                printf("Venda realizada. Total a pagar: %.2f\n", quantidadeDesejada * produtos[i].valorUnitario);
            } else {
                printf("Quantidade insuficiente em estoque. Deseja comprar %d unidades e zerar o estoque? (1-Sim / 0-Não): ", produtos[i].quantidade);
                int opcao;
                scanf("%d", &opcao);
                if (opcao == 1) {
                    printf("Venda realizada. Total a pagar: %.2f\n", produtos[i].quantidade * produtos[i].valorUnitario);
                    produtos[i].quantidade = 0;
                } else {
                    printf("Venda não realizada.\n");
                }
            }
            encontrado = 1;
            break;
        }
    }
    if (!encontrado) {
        printf("Produto não encontrado.\n");
    }
}

void atualizarEstoqueProduto(Produto produtos[], int quantidade) {
    int codigo, novaQuantidade, encontrado = 0;
    printf("Digite o código do produto para atualizar o estoque: ");
    scanf("%d", &codigo);
    for (int i = 0; i < quantidade; i++) {
        if (produtos[i].codigo == codigo) {
            printf("Digite a nova quantidade em estoque: ");
            scanf("%d", &novaQuantidade);
            produtos[i].quantidade = novaQuantidade;
            encontrado = 1;
            break;
        }
    }
    if (!encontrado) {
        printf("Produto não encontrado.\n");
    }
}

void exibirTodosProdutos(Produto produtos[], int quantidade) {
    printf("Lista de todos os produtos:\n");
    for (int i = 0; i < quantidade; i++) {
        printf("Código: %d, Descrição: %s\n", produtos[i].codigo, produtos[i].descricao);
    }
}

void exibirProdutosEstoqueZero(Produto produtos[], int quantidade) {
    printf("Produtos com estoque zerado:\n");
    for (int i = 0; i < quantidade; i++) {
        if (produtos[i].quantidade == 0) {
            printf("Código: %d, Descrição: %s\n", produtos[i].codigo, produtos[i].descricao);
        }
    }
}

int main() {
    Produto produtos[PRODUTOS];
    int quantidadeAtual = 0;

    cadastrarProduto(produtos, &quantidadeAtual);
    alterarValorProduto(produtos, quantidadeAtual);
    printf("Valor consultado: %.2f\n", consultarValorProduto(produtos, quantidadeAtual));
    printf("Estoque consultado: %d\n", consultarEstoqueProduto(produtos, quantidadeAtual));
    venderProduto(produtos, quantidadeAtual);
    atualizarEstoqueProduto(produtos, quantidadeAtual);
    exibirTodosProdutos(produtos, quantidadeAtual);
    exibirProdutosEstoqueZero(produtos, quantidadeAtual);

    return 0;
}
