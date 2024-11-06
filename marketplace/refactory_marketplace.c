#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_PRODUTOS 100
#define MAX_CARRINHO 50

// Estrutura para armazenar os produtos
typedef struct {
    int codigo;
    char nome[50];
    float preco;
    int estoque;
} Produto;

// Estrutura para armazenar o carrinho de compras
typedef struct {
    Produto produto;
    int quantidade;
} ItemCarrinho;

// Funções
void exibirMenu();
void cadastrarProduto(Produto produtos[], int *numProdutos);
void listarProdutos(const Produto produtos[], int numProdutos);
void comprarProduto(ItemCarrinho carrinho[], int *numCarrinho, Produto produtos[], int numProdutos);
void visualizarCarrinho(const ItemCarrinho carrinho[], int numCarrinho);
void fecharPedido(ItemCarrinho carrinho[], int *numCarrinho);
int temNoCarrinho(const ItemCarrinho carrinho[], int numCarrinho, int codigo);
Produto* pegarProdutoPorCodigo(Produto produtos[], int numProdutos, int codigo);
float calcularTotalCarrinho(const ItemCarrinho carrinho[], int numCarrinho);
void capturarEntrada(char *buffer, size_t tamanho);
int validarNumero(const char *str);

int main() {
    Produto produtos[MAX_PRODUTOS];
    ItemCarrinho carrinho[MAX_CARRINHO];
    int numProdutos = 0;
    int numCarrinho = 0;
    int opcao;

    do {
        exibirMenu();
        printf("Escolha uma opcao: ");
        char buffer[10];
        capturarEntrada(buffer, sizeof(buffer));
        opcao = validarNumero(buffer) ? atoi(buffer) : -1;

        switch (opcao) {
            case 1:
                cadastrarProduto(produtos, &numProdutos);
                break;
            case 2:
                listarProdutos(produtos, numProdutos);
                break;
            case 3:
                comprarProduto(carrinho, &numCarrinho, produtos, numProdutos);
                break;
            case 4:
                visualizarCarrinho(carrinho, numCarrinho);
                break;
            case 5:
                fecharPedido(carrinho, &numCarrinho);
                break;
            case 0:
                printf("Saindo...\n");
                break;
            default:
                printf("Opcao invalida!\n");
                break;
        }
    } while (opcao != 0);

    return 0;
}

void exibirMenu() {
    printf("\n===== Sistema de Supermercado =====\n");
    printf("1. Cadastrar Produto\n");
    printf("2. Listar Produtos\n");
    printf("3. Comprar Produto\n");
    printf("4. Visualizar Carrinho\n");
    printf("5. Fechar Pedido\n");
    printf("0. Sair\n");
}

// Função para capturar a entrada do usuário de forma segura
void capturarEntrada(char *buffer, size_t tamanho) {
    fgets(buffer, tamanho, stdin);
    buffer[strcspn(buffer, "\n")] = '\0';
}

// Função para validar se a entrada é um número válido
int validarNumero(const char *str) {
    while (*str) {
        if (!isdigit(*str)) return 0;
        str++;
    }
    return 1;
}

// Função para cadastrar um produto
void cadastrarProduto(Produto produtos[], int *numProdutos) {
    if (*numProdutos >= MAX_PRODUTOS) {
        printf("Limite de produtos atingido.\n");
        return;
    }

    Produto novoProduto;
    novoProduto.codigo = *numProdutos + 1;

    printf("Nome do produto: ");
    capturarEntrada(novoProduto.nome, sizeof(novoProduto.nome));

    char buffer[10];
    printf("Preco do produto: ");
    capturarEntrada(buffer, sizeof(buffer));
    novoProduto.preco = validarNumero(buffer) ? atof(buffer) : 0.0;

    printf("Quantidade em estoque: ");
    capturarEntrada(buffer, sizeof(buffer));
    novoProduto.estoque = validarNumero(buffer) ? atoi(buffer) : 0;

    produtos[*numProdutos] = novoProduto;
    (*numProdutos)++;
    printf("Produto cadastrado com sucesso!\n");
}

// Função para listar todos os produtos
void listarProdutos(const Produto produtos[], int numProdutos) {
    if (numProdutos == 0) {
        printf("Nenhum produto cadastrado.\n");
        return;
    }

    printf("\n===== Lista de Produtos =====\n");
    for (int i = 0; i < numProdutos; i++) {
        printf("Codigo: %d | Nome: %s | Preco: %.2f | Estoque: %d\n",
               produtos[i].codigo, produtos[i].nome, produtos[i].preco, produtos[i].estoque);
    }
}

// Função para comprar um produto (adicionar ao carrinho)
void comprarProduto(ItemCarrinho carrinho[], int *numCarrinho, Produto produtos[], int numProdutos) {
    int codigoProduto, quantidade;
    Produto *produtoEscolhido;

    listarProdutos(produtos, numProdutos);

    char buffer[10];
    printf("Digite o codigo do produto para comprar: ");
    capturarEntrada(buffer, sizeof(buffer));
    codigoProduto = validarNumero(buffer) ? atoi(buffer) : -1;

    produtoEscolhido = pegarProdutoPorCodigo(produtos, numProdutos, codigoProduto);

    if (produtoEscolhido == NULL) {
        printf("Produto nao encontrado!\n");
        return;
    }

    printf("Digite a quantidade: ");
    capturarEntrada(buffer, sizeof(buffer));
    quantidade = validarNumero(buffer) ? atoi(buffer) : 0;

    if (quantidade > produtoEscolhido->estoque || quantidade <= 0) {
        printf("Quantidade invalida!\n");
        return;
    }

    int pos = temNoCarrinho(carrinho, *numCarrinho, codigoProduto);

    if (pos == -1) {
        carrinho[*numCarrinho].produto = *produtoEscolhido;
        carrinho[*numCarrinho].quantidade = quantidade;
        (*numCarrinho)++;
    } else {
        carrinho[pos].quantidade += quantidade;
    }

    produtoEscolhido->estoque -= quantidade;
    printf("Produto adicionado ao carrinho!\n");
}

// Função para visualizar o carrinho
void visualizarCarrinho(const ItemCarrinho carrinho[], int numCarrinho) {
    if (numCarrinho == 0) {
        printf("Carrinho vazio.\n");
        return;
    }

    float total = calcularTotalCarrinho(carrinho, numCarrinho);

    printf("\n===== Carrinho de Compras =====\n");
    for (int i = 0; i < numCarrinho; i++) {
        printf("Produto: %s | Quantidade: %d | Preco Unitario: %.2f | Subtotal: %.2f\n",
               carrinho[i].produto.nome, carrinho[i].quantidade, carrinho[i].produto.preco,
               carrinho[i].quantidade * carrinho[i].produto.preco);
    }
    printf("Total do carrinho: %.2f\n", total);
}

// Função para fechar o pedido e esvaziar o carrinho
void fecharPedido(ItemCarrinho carrinho[], int *numCarrinho) {
    if (*numCarrinho == 0) {
        printf("Carrinho vazio. Nenhum pedido a ser fechado.\n");
        return;
    }

    float total = calcularTotalCarrinho(carrinho, *numCarrinho);
    printf("Valor total a ser pago: %.2f\n", total);
    printf("Pedido fechado com sucesso!\n");

    *numCarrinho = 0;
}

// Função para verificar se o produto já está no carrinho
int temNoCarrinho(const ItemCarrinho carrinho[], int numCarrinho, int codigo) {
    for (int i = 0; i < numCarrinho; i++) {
        if (carrinho[i].produto.codigo == codigo) {
            return i;
        }
    }
    return -1;
}

// Função para buscar um produto pelo código
Produto* pegarProdutoPorCodigo(Produto produtos[], int numProdutos, int codigo) {
    for (int i = 0; i < numProdutos; i++) {
        if (produtos[i].codigo == codigo) {
            return &produtos[i];
        }
    }
    return NULL;
}

// Função para calcular o total do carrinho
float calcularTotalCarrinho(const ItemCarrinho carrinho[], int numCarrinho) {
    float total = 0.0;
    for (int i = 0; i < numCarrinho; i++) {
        total += carrinho[i].quantidade * carrinho[i].produto.preco;
    }
    return total;
}
