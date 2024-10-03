Desenvolvimento do Sistema

Estruturas de Dados:

O sistema utiliza duas estruturas principais:

Produto: Para armazenar informações sobre produtos, como código, nome, preço e estoque.
ItemCarrinho: Para armazenar itens que o usuário deseja comprar, incluindo o produto e a quantidade.

Funções:

O código é organizado em várias funções, cada uma responsável por uma parte específica do sistema:

menu(): Exibe o menu principal e gerencia as opções do usuário.
cadastrarProduto(): Permite ao usuário cadastrar novos produtos.
listarProdutos(): Exibe todos os produtos cadastrados.
comprarProduto(): Permite ao usuário adicionar produtos ao carrinho de compras.
visualizarCarrinho(): Mostra os itens no carrinho e o total.
fecharPedido(): Finaliza a compra, exibindo o total e esvaziando o carrinho.
temNoCarrinho(): Verifica se um produto já está no carrinho.
pegarProdutoPorCodigo(): Busca um produto específico pelo código.

Fluxo de Execução:

O fluxo começa na função main(), onde as variáveis para produtos e carrinho são inicializadas e a função menu() é chamada.
O menu permite ao usuário navegar pelas opções até decidir sair do sistema.

Funcionalidades Implementadas

Cadastrar Produto:

O usuário pode cadastrar novos produtos, fornecendo nome, preço e quantidade em estoque. Cada produto recebe um código único automaticamente.

Listar Produtos:

Exibe todos os produtos cadastrados com seus detalhes (código, nome, preço, estoque).

Comprar Produto:

Permite que o usuário escolha um produto da lista e defina a quantidade a ser comprada. O sistema verifica se o produto está disponível em estoque antes de adicioná-lo ao carrinho.

Visualizar Carrinho:

Exibe todos os itens no carrinho de compras, mostrando quantidade, preço unitário e subtotal de cada item. O total geral é calculado e exibido.

Fechar Pedido:

Finaliza a compra, mostrando o total a ser pago e esvaziando o carrinho de compras.

Validações:

O sistema inclui várias validações, como verificar se o produto está em estoque, se o carrinho está vazio ao fechar o pedido e se a quantidade solicitada está disponível.



=====Instruções para Compilar e Executar=====

Para compilar e executar o código em um ambiente de desenvolvimento C, siga estas instruções:

Salvar o Código:

Copie o código em um arquivo chamado, por exemplo, supermercado.c.

Compilar:

Abra um terminal e navegue até o diretório onde o arquivo foi salvo.
Use um compilador C, como gcc, para compilar o código.

Executar:

Após a compilação bem-sucedida, execute o programa.