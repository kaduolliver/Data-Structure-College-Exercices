#include <stdio.h>
#include <string.h>

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
void menu();
void cadastrarProduto(Produto produtos[], int *numProdutos);
void listarProdutos(Produto produtos[], int numProdutos);
void comprarProduto(ItemCarrinho carrinho[], int *numCarrinho, Produto produtos[], int numProdutos);
void visualizarCarrinho(ItemCarrinho carrinho[], int numCarrinho);
void fecharPedido(ItemCarrinho carrinho[], int *numCarrinho);
int temNoCarrinho(ItemCarrinho carrinho[], int numCarrinho, int codigo);
Produto* pegarProdutoPorCodigo(Produto produtos[], int numProdutos, int codigo);

int main() {
    Produto produtos[MAX_PRODUTOS];
    ItemCarrinho carrinho[MAX_CARRINHO];
    int numProdutos = 0;
    int numCarrinho = 0;

    menu(produtos, &numProdutos, carrinho, &numCarrinho);

    return 0;
}

// Função que exibe o menu e gerencia o fluxo do programa
void menu(Produto produtos[], int *numProdutos, ItemCarrinho carrinho[], int *numCarrinho) {
    int opcao;

    do {
        printf("\n===== Sistema de Supermercado =====\n");
        printf("1. Cadastrar Produto\n");
        printf("2. Listar Produtos\n");
        printf("3. Comprar Produto\n");
        printf("4. Visualizar Carrinho\n");
        printf("5. Fechar Pedido\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                cadastrarProduto(produtos, numProdutos);
                break;
            case 2:
                listarProdutos(produtos, *numProdutos);
                break;
            case 3:
                comprarProduto(carrinho, numCarrinho, produtos, *numProdutos);
                break;
            case 4:
                visualizarCarrinho(carrinho, *numCarrinho);
                break;
            case 5:
                fecharPedido(carrinho, numCarrinho);
                break;
            case 0:
                printf("Saindo...\n");
                break;
            default:
                printf("Opcao invalida!\n");
                break;
        }
    } while (opcao != 0);
}

// Função para cadastrar um produto
void cadastrarProduto(Produto produtos[], int *numProdutos) {
    Produto novoProduto;
    novoProduto.codigo = *numProdutos + 1;

    printf("Nome do produto: ");
    scanf("%s", novoProduto.nome);

    printf("Preco do produto: ");
    scanf("%f", &novoProduto.preco);

    printf("Quantidade em estoque: ");
    scanf("%d", &novoProduto.estoque);

    produtos[*numProdutos] = novoProduto;
    (*numProdutos)++;

    printf("Produto cadastrado com sucesso!\n");
}

// Função para listar todos os produtos
void listarProdutos(Produto produtos[], int numProdutos) {
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

    printf("Digite o codigo do produto para comprar: ");
    scanf("%d", &codigoProduto);

    produtoEscolhido = pegarProdutoPorCodigo(produtos, numProdutos, codigoProduto);

    if (produtoEscolhido == NULL) {
        printf("Produto nao encontrado!\n");
        return;
    }

    if (produtoEscolhido->estoque == 0) {
        printf("Produto fora de estoque!\n");
        return;
    }

    printf("Digite a quantidade: ");
    scanf("%d", &quantidade);

    if (quantidade > produtoEscolhido->estoque) {
        printf("Quantidade indisponivel em estoque!\n");
        return;
    }

    int pos = temNoCarrinho(carrinho, *numCarrinho, codigoProduto);

    if (pos == -1) {  // Produto ainda não está no carrinho
        carrinho[*numCarrinho].produto = *produtoEscolhido;
        carrinho[*numCarrinho].quantidade = quantidade;
        (*numCarrinho)++;
    } else {  // Produto já está no carrinho, só aumentar a quantidade
        carrinho[pos].quantidade += quantidade;
    }

    produtoEscolhido->estoque -= quantidade;
    printf("Produto adicionado ao carrinho!\n");
}

// Função para visualizar o carrinho
void visualizarCarrinho(ItemCarrinho carrinho[], int numCarrinho) {
    if (numCarrinho == 0) {
        printf("Carrinho vazio.\n");
        return;
    }

    float total = 0;

    printf("\n===== Carrinho de Compras =====\n");
    for (int i = 0; i < numCarrinho; i++) {
        printf("Produto: %s | Quantidade: %d | Preco Unitario: %.2f | Subtotal: %.2f\n",
               carrinho[i].produto.nome, carrinho[i].quantidade, carrinho[i].produto.preco,
               carrinho[i].quantidade * carrinho[i].produto.preco);
        total += carrinho[i].quantidade * carrinho[i].produto.preco;
    }

    printf("Total do carrinho: %.2f\n", total);
}

// Função para fechar o pedido e esvaziar o carrinho
void fecharPedido(ItemCarrinho carrinho[], int *numCarrinho) {
    if (*numCarrinho == 0) {
        printf("Carrinho vazio. Nenhum pedido a ser fechado.\n");
        return;
    }

    float total = 0;

    printf("\n===== Fechamento do Pedido =====\n");
    for (int i = 0; i < *numCarrinho; i++) {
        total += carrinho[i].quantidade * carrinho[i].produto.preco;
    }

    printf("Valor total a ser pago: %.2f\n", total);
    printf("Pedido fechado com sucesso!\n");

    // Esvaziando o carrinho
    *numCarrinho = 0;
}

// Função para verificar se o produto já está no carrinho
int temNoCarrinho(ItemCarrinho carrinho[], int numCarrinho, int codigo) {
    for (int i = 0; i < numCarrinho; i++) {
        if (carrinho[i].produto.codigo == codigo) {
            return i;
        }
    }
    return -1;
}

// Função para pegar um produto pelo código
Produto* pegarProdutoPorCodigo(Produto produtos[], int numProdutos, int codigo) {
    for (int i = 0; i < numProdutos; i++) {
        if (produtos[i].codigo == codigo) {
            return &produtos[i];
        }
    }
    return NULL;
}
