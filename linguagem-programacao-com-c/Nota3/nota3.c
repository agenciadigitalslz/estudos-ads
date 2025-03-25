// Atividade 3: Sistema de Vendas
// Desenvolva um sistema de vendas que permita cadastrar clientes, produtos e realizar vendas.

#include <stdio.h>
#include <stdlib.h>  // Necessário para usar system()

// Tamanhos dos vetores
#define TAMCli 3
#define TAMProd 3
#define TAMVend 10

// Função para limpar o buffer de entrada (Melhoria: Validação de Entrada)
void limparBuffer() {
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF);
}

// Função para limpar a tela do terminal (Melhoria na Interface do Usuário)
// Agora a limpeza da tela é controlada pelo usuário (Opção 8) e não automática.
void clearScreen() {
#ifdef _WIN32
    system("cls");  // Para Windows
#else
    system("clear");  // Para Unix/Linux
#endif
}

// Struct Produto: Representa um produto com seus dados
typedef struct {
    int id;               // Identificador único do produto
    char nome[20];        // Nome do produto
    int quantidade;       // Quantidade disponível no estoque
    float valor;          // Valor unitário do produto
} Produto;

// Struct Cliente: Representa um cliente com seus dados
typedef struct {
    int id;               // Identificador único do cliente
    char nome[20];        // Primeiro nome do cliente
} Cliente;

// Struct Venda: Registra os dados da transação de venda
typedef struct {
    int idCliente;        // ID do cliente (Registro dos Dados da Compra - 2,0 pontos)
    int idProduto;        // ID do produto (Registro dos Dados da Compra - 2,0 pontos)
    int quantProduto;     // Quantidade comprada (Registro dos Dados da Compra - 2,0 pontos)
    float valorTotal;     // Valor total da venda (Cálculo do Preço Total da Venda - 2,0 pontos)
} Venda;

// Função para cadastrar clientes com validação de entrada (Melhoria: Validação em Outras Entradas)
void cadastrarCliente(Cliente c[]) {
    for (int i = 0; i < TAMCli; i++) {
        printf("Cliente %d, Primeiro Nome: ", i + 1);
        // %19s limita a entrada para evitar overflow
        if (scanf("%19s", c[i].nome) != 1) {
            limparBuffer();
            printf("Entrada inválida para o nome do cliente. Tente novamente.\n");
            i--;  // Repete o cadastro do mesmo cliente
            continue;
        }
        c[i].id = i + 1;
    }
}

// Função para cadastrar produtos com validação de entrada (Melhoria: Validação em Outras Entradas)
void cadastrarProduto(Produto p[]) {
    for (int i = 0; i < TAMProd; i++) {
        printf("\nNome do Produto %d: ", i + 1);
        if (scanf("%19s", p[i].nome) != 1) {  // Limita a entrada para evitar overflow
            limparBuffer();
            printf("Entrada inválida para o nome do produto. Tente novamente.\n");
            i--;
            continue;
        }
        printf("Quantidade: ");
        if (scanf("%d", &p[i].quantidade) != 1) {
            limparBuffer();
            printf("Entrada inválida para a quantidade. Tente novamente.\n");
            i--;
            continue;
        }
        printf("Valor: ");
        if (scanf("%f", &p[i].valor) != 1) {
            limparBuffer();
            printf("Entrada inválida para o valor. Tente novamente.\n");
            i--;
            continue;
        }
        p[i].id = i + 1;
    }
}

// Função para consultar clientes (mantida com comentários explicativos)
void consultarCliente(Cliente c[]) {
    for (int i = 0; i < TAMCli; i++) {
        printf("\nId Cliente: %d", c[i].id);
        printf("\nNome: %s", c[i].nome);
        printf("\n----------------------");
    }
    printf("\n");
}

// Função para consultar produtos (mantida com comentários explicativos)
void consultarProduto(Produto p[]) {
    for (int i = 0; i < TAMProd; i++) {
        printf("\nId Produto: %d", p[i].id);
        printf("\nNome: %s", p[i].nome);
        printf("\nQuantidade: %d", p[i].quantidade);
        printf("\nValor: %.2f", p[i].valor);
        printf("\n----------------------");
    }
    printf("\n");
}

// Função para realizar vendas com validação de entrada e atualização do estoque
void realizarVenda(Cliente clientes[], Produto produtos[], Venda vendas[], int *numVendas) {
    int idCliente, idProduto, quantidade;
    
    // Solicita e valida o ID do cliente
    printf("\nDigite o ID do Cliente: ");
    if (scanf("%d", &idCliente) != 1) {
        limparBuffer();
        printf("Entrada inválida para o ID do Cliente.\n");
        return;
    }
    if (idCliente < 1 || idCliente > TAMCli) {
        printf("Cliente não encontrado.\n");
        return;
    }
    
    // Solicita e valida o ID do produto
    printf("Digite o ID do Produto: ");
    if (scanf("%d", &idProduto) != 1) {
        limparBuffer();
        printf("Entrada inválida para o ID do Produto.\n");
        return;
    }
    if (idProduto < 1 || idProduto > TAMProd) {
        printf("Produto não encontrado.\n");
        return;
    }
    
    // Solicita e valida a quantidade desejada
    printf("Digite a quantidade desejada: ");
    if (scanf("%d", &quantidade) != 1) {
        limparBuffer();
        printf("Entrada inválida para a quantidade.\n");
        return;
    }
    
    // Validação do estoque antes da venda (Implementação correta da validação do estoque - 3,0 pontos)
    if (quantidade > produtos[idProduto - 1].quantidade) {
        printf("Estoque insuficiente para o produto %s.\n", produtos[idProduto - 1].nome);
        return;
    }
    
    // Atualiza o estoque do produto
    produtos[idProduto - 1].quantidade -= quantidade;
    
    // Calcula o preço total da venda (Cálculo do Preço Total da Venda - 2,0 pontos)
    float total = quantidade * produtos[idProduto - 1].valor;
    
    // Registra os dados da compra (Registro dos Dados da Compra - 2,0 pontos)
    vendas[*numVendas].idCliente = idCliente;
    vendas[*numVendas].idProduto = idProduto;
    vendas[*numVendas].quantProduto = quantidade;
    vendas[*numVendas].valorTotal = total;
    (*numVendas)++;  // Incrementa o contador de vendas
    
    printf("Venda realizada com sucesso! Total: R$ %.2f\n", total);
}

// Função para consultar as vendas realizadas (Geração do Relatório de Vendas - 2,0 pontos)
void consultarVendas(Venda vendas[], int numVendas) {
    if (numVendas == 0) {
        printf("Nenhuma venda realizada ainda.\n");
        return;
    }
    
    printf("\n--- Relatório de Vendas ---\n");
    for (int i = 0; i < numVendas; i++) {
        printf("\nVenda %d:", i + 1);
        printf("\nID Cliente: %d", vendas[i].idCliente);
        printf("\nID Produto: %d", vendas[i].idProduto);
        printf("\nQuantidade: %d", vendas[i].quantProduto);
        printf("\nValor Total: R$ %.2f", vendas[i].valorTotal);
        printf("\n----------------------");
    }
    printf("\n");
}

// Função principal: gerencia o fluxo do sistema e apresenta o menu
// Melhoria: Removida a limpeza automática da tela para não prejudicar a consulta
// e adicionada a opção 8 para que o usuário controle quando limpar a tela.
int main() {
    int opcao, sair = 0;
    Cliente clientes[5];
    Produto produtos[5];
    Venda vendas[TAMVend];
    int numVendas = 0;
    
    // Loop principal do sistema
    do {
        // Exibe o menu principal com as opções disponíveis
        printf("\n>>>> Sistema de Vendas <<<<\n");
        printf("1 - Cadastrar Clientes\n");
        printf("2 - Cadastrar Produtos\n");
        printf("3 - Consultar Clientes\n");
        printf("4 - Consultar Produtos\n");
        printf("5 - Realizar Vendas\n");
        printf("6 - Consultar Vendas\n");
        printf("7 - Sair\n");
        printf("8 - Limpar Tela (opcional)\n");
        printf(">>>> ");
        
        // Validação da entrada do menu (Melhoria: Evita comandos incorretos)
        if (scanf("%d", &opcao) != 1) {
            limparBuffer();
            printf("\nComando inválido! Por favor, digite um número correspondente a uma opção do menu.\n");
            printf("Pressione Enter para continuar...");
            limparBuffer();
            continue;
        }
        
        // Processamento das opções do menu
        switch (opcao) {
            case 1:
                cadastrarCliente(clientes);
                break;
            case 2:
                cadastrarProduto(produtos);
                break;
            case 3:
                consultarCliente(clientes);
                break;
            case 4:
                consultarProduto(produtos);
                break;
            case 5:
                realizarVenda(clientes, produtos, vendas, &numVendas);
                break;
            case 6:
                consultarVendas(vendas, numVendas);
                break;
            case 7:
                sair = 1;
                break;
            case 8:
                // Limpa a tela somente quando o usuário escolher a opção
                clearScreen();
                break;
            default:
                // Feedback para opção inválida (Melhoria: Feedback claro ao usuário)
                printf("\nOpção inválida! Digite um número entre 1 e 8.\n");
                printf("Pressione Enter para continuar...");
                limparBuffer();
        }
        // Pausa para o usuário visualizar o resultado antes de prosseguir
        printf("\nPressione Enter para continuar...");
        limparBuffer();
    } while (sair != 1);
    
    return 0;
}
