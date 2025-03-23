#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>   // Para capturar data/hora do sistema

#define TAMCli 5
#define TAMProd 5
#define TAMVend 10

void limparBuffer() {
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF);
}

void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

// Struct Produto
typedef struct {
    int id;
    char nome[20];
    int quantidade;
    float valor;
} Produto;

// Struct Cliente
typedef struct {
    int id;
    char nome[20];
} Cliente;

// Struct Venda com data/hora da compra
typedef struct {
    int idCliente;
    int idProduto;
    int quantProduto;
    float valorTotal;
    char dataHora[30];   // Data/hora no formato dd/mm/aaaa HH:MM:SS
} Venda;

int totalClientes = 0;
int totalProdutos = 0;

// ----------------------- CLIENTES -----------------------
void cadastrarCliente(Cliente c[]) {
    if (totalClientes >= TAMCli) {
        printf("\nLimite de clientes atingido.\n");
        return;
    }
    printf("Cliente %d, Primeiro Nome: ", totalClientes + 1);
    if (scanf("%19s", c[totalClientes].nome) != 1) {
        limparBuffer();
        printf("Entrada inválida para o nome do cliente. Tente novamente.\n");
        return;
    }
    c[totalClientes].id = totalClientes + 1;
    totalClientes++;
    printf("Cliente cadastrado com sucesso!\n");
}

void consultarCliente(Cliente c[]) {
    for (int i = 0; i < totalClientes; i++) {
        if (c[i].id != 0) {
            printf("\n==============================\n");
            printf("Cliente #%d\n", c[i].id);
            printf("\nNome: %s", c[i].nome);
            printf("\n----------------------");
        }
    }
    printf("\nConsulta finalizada com sucesso!\n");
}

void deletarCliente(Cliente c[]) {
    int id;
    printf("\nDigite o ID do cliente a ser deletado: ");
    if (scanf("%d", &id) != 1 || id < 1 || id > totalClientes || c[id - 1].id == 0) {
        limparBuffer();
        printf("ID inválido ou cliente inexistente.\n");
        return;
    }
    c[id - 1].id = 0;
    strcpy(c[id - 1].nome, "");
    printf("Cliente removido com sucesso.\n");
}

// Submenu de clientes
void submenuClientes(Cliente clientes[]) {
    int opcao;
    do {
        printf("\n===== MENU CLIENTES =====\n");
        printf("1 - Cadastrar Cliente\n");
        printf("2 - Consultar Clientes\n");
        printf("3 - Deletar Cliente por ID\n");
        printf("0 - Voltar\n>>>> ");

        if (scanf("%d", &opcao) != 1) {
            limparBuffer();
            printf("Opção inválida!\n");
            continue;
        }
        limparBuffer();

        switch (opcao) {
            case 1:
                cadastrarCliente(clientes);
                break;
            case 2:
                consultarCliente(clientes);
                break;
            case 3:
                deletarCliente(clientes);
                break;
            case 0:
                break;
            default:
                printf("Opção inválida!\n");
        }
    } while (opcao != 0);
}

// ----------------------- PRODUTOS -----------------------
void cadastrarProduto(Produto p[]) {
    if (totalProdutos >= TAMProd) {
        printf("\nLimite de produtos atingido.\n");
        return;
    }
    printf("\nNome do Produto %d: ", totalProdutos + 1);
    if (scanf("%19s", p[totalProdutos].nome) != 1) {
        limparBuffer();
        printf("Entrada inválida para o nome do produto. Tente novamente.\n");
        return;
    }
    printf("Quantidade: ");
    if (scanf("%d", &p[totalProdutos].quantidade) != 1) {
        limparBuffer();
        printf("Entrada inválida para a quantidade. Tente novamente.\n");
        return;
    }
    printf("Valor: ");
    if (scanf("%f", &p[totalProdutos].valor) != 1) {
        limparBuffer();
        printf("Entrada inválida para o valor. Tente novamente.\n");
        return;
    }
    p[totalProdutos].id = totalProdutos + 1;
    totalProdutos++;
    printf("Produto cadastrado com sucesso!\n");
}

void consultarProduto(Produto p[]) {
    for (int i = 0; i < totalProdutos; i++) {
        if (p[i].id != 0) {
            printf("\n==============================\n");
            printf("Produto #%d\n", p[i].id);
            printf("\nNome: %s", p[i].nome);
            printf("\nQuantidade: %d", p[i].quantidade);
            printf("\nValor: %.2f", p[i].valor);
            printf("\n----------------------");
        }
    }
    printf("\nConsulta finalizada com sucesso!\n");
}

void deletarProduto(Produto p[]) {
    int id;
    printf("\nDigite o ID do produto a ser deletado: ");
    if (scanf("%d", &id) != 1 || id < 1 || id > totalProdutos || p[id - 1].id == 0) {
        limparBuffer();
        printf("ID inválido ou produto inexistente.\n");
        return;
    }
    p[id - 1].id = 0;
    strcpy(p[id - 1].nome, "");
    p[id - 1].quantidade = 0;
    p[id - 1].valor = 0.0;
    printf("Produto removido com sucesso.\n");
}

// Submenu de produtos
void submenuProdutos(Produto produtos[]) {
    int opcao;
    do {
        printf("\n===== MENU PRODUTOS =====\n");
        printf("1 - Cadastrar Produto\n");
        printf("2 - Consultar Produtos\n");
        printf("3 - Deletar Produto por ID\n");
        printf("0 - Voltar\n>>>> ");

        if (scanf("%d", &opcao) != 1) {
            limparBuffer();
            printf("Opção inválida!\n");
            continue;
        }
        limparBuffer();

        switch (opcao) {
            case 1:
                cadastrarProduto(produtos);
                break;
            case 2:
                consultarProduto(produtos);
                break;
            case 3:
                deletarProduto(produtos);
                break;
            case 0:
                break;
            default:
                printf("Opção inválida!\n");
        }
    } while (opcao != 0);
}

// ----------------------- VENDAS -----------------------
void realizarVenda(Cliente clientes[], Produto produtos[], Venda vendas[], int *numVendas) {
    int idCliente, idProduto, quantidade;

    printf("\nDigite o ID do Cliente: ");
    if (scanf("%d", &idCliente) != 1 || idCliente < 1 || idCliente > totalClientes || clientes[idCliente - 1].id == 0) {
        limparBuffer();
        printf("ID de cliente inválido.\n");
        return;
    }

    printf("Digite o ID do Produto: ");
    if (scanf("%d", &idProduto) != 1 || idProduto < 1 || idProduto > totalProdutos || produtos[idProduto - 1].id == 0) {
        limparBuffer();
        printf("ID de produto inválido.\n");
        return;
    }

    printf("Digite a quantidade desejada: ");
    if (scanf("%d", &quantidade) != 1 || quantidade <= 0) {
        limparBuffer();
        printf("Quantidade inválida.\n");
        return;
    }

    if (quantidade > produtos[idProduto - 1].quantidade) {
        printf("Estoque insuficiente.\n");
        return;
    }

    produtos[idProduto - 1].quantidade -= quantidade;

    float total = quantidade * produtos[idProduto - 1].valor;

    // Captura Data/Hora
    time_t t = time(NULL);
    struct tm tm_struct = *localtime(&t);
    char buffer[30];
    sprintf(buffer, "%02d/%02d/%04d %02d:%02d:%02d",
            tm_struct.tm_mday,
            tm_struct.tm_mon + 1,
            tm_struct.tm_year + 1900,
            tm_struct.tm_hour,
            tm_struct.tm_min,
            tm_struct.tm_sec);

    // Grava os dados da venda
    vendas[*numVendas].idCliente   = idCliente;
    vendas[*numVendas].idProduto   = idProduto;
    vendas[*numVendas].quantProduto= quantidade;
    vendas[*numVendas].valorTotal  = total;
    // Guarda a data/hora no campo dataHora
    strcpy(vendas[*numVendas].dataHora, buffer);

    (*numVendas)++;

    printf("Venda realizada com sucesso! Total: R$ %.2f\n", total);
    printf("Data/Hora da compra: %s\n", buffer);
}

void consultarVendas(Venda vendas[], int numVendas, Cliente clientes[], Produto produtos[]) {
    if (numVendas == 0) {
        printf("Nenhuma venda registrada.\n");
        return;
    }

    float totalGeral = 0;
    for (int i = 0; i < numVendas; i++) {
        int idCli  = vendas[i].idCliente;
        int idProd = vendas[i].idProduto;
        printf("\n==============================\n");
        printf("Venda %d\n", i + 1);
        printf("Cliente: %s\n",  clientes[idCli - 1].nome);
        printf("Produto: %s\n",  produtos[idProd - 1].nome);
        printf("Quantidade: %d\n",     vendas[i].quantProduto);
        printf("Total: R$ %.2f\n",    vendas[i].valorTotal);
        // Exibe a data/hora
        printf("Data/Hora da compra: %s\n", vendas[i].dataHora);

        totalGeral += vendas[i].valorTotal;
    }
    printf("\nTotal Geral de Vendas: R$ %.2f\n", totalGeral);
}

// Submenu de vendas
void submenuVendas(Cliente clientes[], Produto produtos[], Venda vendas[], int *numVendas) {
    int opcao;
    do {
        printf("\n===== MENU VENDAS =====\n");
        printf("1 - Realizar Venda\n");
        printf("2 - Consultar Vendas\n");
        printf("0 - Voltar\n>>>> ");

        if (scanf("%d", &opcao) != 1) {
            limparBuffer();
            printf("Opção inválida!\n");
            continue;
        }
        limparBuffer();

        switch (opcao) {
            case 1:
                realizarVenda(clientes, produtos, vendas, numVendas);
                break;
            case 2:
                consultarVendas(vendas, *numVendas, clientes, produtos);
                break;
            case 0:
                break;
            default:
                printf("Opção inválida!\n");
        }
    } while (opcao != 0);
}

// --------------------- MAIN ---------------------
int main() {
    int opcao, sair = 0;
    Cliente clientes[TAMCli];
    Produto produtos[TAMProd];
    // Adicionamos dataHora à estrutura de Venda
    // Precisamos aumentar o struct: char dataHora[30];
    Venda vendas[TAMVend];
    int numVendas = 0;

    do {
        printf("\n==============================\n");
        printf("     SISTEMA DE VENDAS     \n");
        printf("==============================\n");
        printf("1 - Gerenciar Clientes\n");
        printf("2 - Gerenciar Produtos\n");
        printf("3 - Gerenciar Vendas\n");
        printf("0 - Limpar Tela\n");
        printf("9 - Sair\n>>>> ");

        if (scanf("%d", &opcao) != 1) {
            limparBuffer();
            printf("\nComando inválido!\n");
            continue;
        }
        limparBuffer();

        switch (opcao) {
            case 1:
                submenuClientes(clientes);
                break;
            case 2:
                submenuProdutos(produtos);
                break;
            case 3:
                submenuVendas(clientes, produtos, vendas, &numVendas);
                break;
            case 0:
                clearScreen();
                break;
            case 9:
                sair = 1;
                printf("\nEncerrando o programa. Obrigado por utilizar o sistema!\n");
                break;
            default:
                printf("\nOpção inválida!\n");
        }

        if (!sair) {
            printf("\nPressione Enter para continuar...");
            limparBuffer();
        }
    } while (!sair);

    return 0;
}
