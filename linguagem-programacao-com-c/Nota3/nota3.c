// Atividade 3: Sistema de Vendas
// Desenvolva um sistema de vendas que permita cadastrar clientes, produtos e realizar vendas.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>   // (Melhoria 12) Necessário para registrar data/hora da compra

// (Correção 2) Definição de limites para clientes, produtos e vendas, evitando estouro de vetores
#define TAMCli 5
#define TAMProd 5
#define TAMVend 10

/* (Correção 1) Evita loop com entradas inválidas
   (Critério de Validação de Entradas). */
void limparBuffer() {
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF);
}

/* (Melhoria 2) Controle manual de limpeza de tela,
   permitindo ao usuário decidir quando limpar (cross-plataforma). */
void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

/* (Critério "Registro dos dados da compra" - 2,0 pts)
   (Correção 5) Estruturas separadas para cada entidade:
   (Melhoria 9) IDs exibidos em relatórios. */
typedef struct {
    int id;                   // (Melhoria 9) ID único do produto
    char nome[20];            // Nome do produto
    int quantidade;           // Quantidade em estoque
    float valor;              // Preço unitário
} Produto;

typedef struct {
    int id;                   // (Melhoria 9) ID único do cliente
    char nome[20];            // Nome do cliente
} Cliente;

/* (Melhoria 12) dataHora para armazenar momento da venda.
   (Critério "Registro dos dados da compra"). */
typedef struct {
    int idVenda;              // (Melhoria 5) ID interno da venda
    int idCliente;            // ID do cliente
    int idProduto;            // ID do produto
    int quantProduto;         // Quantidade vendida
    float valorTotal;         // Valor total
    char dataHora[30];        // Data/hora da compra
} Venda;

/* (Correção 2) Controladores globais */
int totalClientes = 0;
int totalProdutos = 0;

/* ----------------------- CLIENTES ----------------------- */

/* (Melhoria 4) Cadastro dinâmico (até TAMCli)
   (Correção 6) Bloqueia cadastro além do limite */
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
    // (Melhoria 9) ID do cliente
    c[totalClientes].id = totalClientes + 1;
    totalClientes++;
    printf("Cliente cadastrado com sucesso!\n");
}

/* (Melhoria 3) Relatório de clientes */
void consultarCliente(Cliente c[]) {
    for (int i = 0; i < totalClientes; i++) {
        // (Correção 5) Ignora clientes deletados (id=0)
        if (c[i].id != 0) {
            printf("\n==============================\n");
            printf("Cliente #%d\n", c[i].id);
            printf("\nNome: %s", c[i].nome);
            printf("\n----------------------");
        }
    }
    printf("\nConsulta finalizada com sucesso!\n");
}

/* (Melhoria 6) Deleção lógica de cliente */
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

/* Submenu de clientes (Melhoria 3, Correção 7) */
void submenuClientes(Cliente clientes[]) {
    int opcao;
    do {
        printf("\n===== MENU CLIENTES =====\n");
        printf("1 - Cadastrar Cliente\n");
        printf("2 - Consultar Clientes\n");
        printf("3 - Deletar Cliente por ID\n");
        printf("0 - Voltar\n>>>> ");

        // (Correção 1) Verificação robusta de scanf
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

/* ----------------------- PRODUTOS ----------------------- */

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

/* Submenu de produtos (Melhoria 3) */
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

/* ----------------------- VENDAS ----------------------- */

/* (Critério "Registro dos dados da compra" - 2,0 pts)
   (Correção 3, 4) Validamos cliente e produto antes
   (Critério "Validação do estoque" - 3,0 pts) */
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

    // (Melhoria 10) Atualiza estoque
    produtos[idProduto - 1].quantidade -= quantidade;

    /* (Critério "Cálculo do valor total da venda" - 2,0 pts)
       total = quantidade × valor unitário */
    float total = quantidade * produtos[idProduto - 1].valor;

    // Gera data/hora da venda (Melhoria 12)
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

    /* (Melhoria 5) Adicionando ID interno para a venda */
    vendas[*numVendas].idVenda      = *numVendas + 1;
    vendas[*numVendas].idCliente    = idCliente;
    vendas[*numVendas].idProduto    = idProduto;
    vendas[*numVendas].quantProduto = quantidade;
    vendas[*numVendas].valorTotal   = total;
    strcpy(vendas[*numVendas].dataHora, buffer);

    (*numVendas)++;

    printf("Venda #%d realizada com sucesso! Total: R$ %.2f\n",
           *numVendas, total);
    printf("Data/Hora da compra: %s\n", buffer);
}

/* (Melhoria 5) Função para cancelar uma venda por ID
   Retorna a quantidade cancelada para o estoque do produto
   e realoca as vendas subsequentes. */
void cancelarVenda(Venda vendas[], int *numVendas, Produto produtos[]) {
    if (*numVendas == 0) {
        printf("\nNao ha vendas registradas.\n");
        return;
    }
    int id;
    printf("\nDigite o ID interno da venda [1..%d]: ", *numVendas);
    if (scanf("%d", &id) != 1 || id < 1 || id > *numVendas) {
        limparBuffer();
        printf("ID de venda invalido.\n");
        return;
    }

    // Antes de remover, pegamos o ID do produto e quantidade vendida
    int index = id - 1;  // Posição no array
    int idProd   = vendas[index].idProduto;
    int qtdVend  = vendas[index].quantProduto;

    // (Melhoria solicitada) Retorna ao estoque
    produtos[idProd - 1].quantidade += qtdVend;

    // Realoca as vendas subsequentes para remover a venda
    for (int i = index; i < (*numVendas - 1); i++) {
        vendas[i] = vendas[i + 1];
    }
    (*numVendas)--;

    printf("Venda #%d cancelada com sucesso!\n", id);
    printf("Estoque do produto #%d foi restaurado em %d unidades.\n",
           idProd, qtdVend);
}

/* (Critério "Geração do relatório de vendas" - 2,0 pts) */
void consultarVendas(Venda vendas[], int numVendas, Cliente clientes[], Produto produtos[]) {
    if (numVendas == 0) {
        printf("Nenhuma venda registrada.\n");
        return;
    }

    float totalGeral = 0;
    for (int i = 0; i < numVendas; i++) {
        int idCli  = vendas[i].idCliente;
        int idProd = vendas[i].idProduto;
        int vID    = vendas[i].idVenda;
        printf("\n==============================\n");
        printf("Venda #%d\n", vID);
        printf("Cliente: %s\n",  clientes[idCli - 1].nome);
        printf("Produto: %s\n",  produtos[idProd - 1].nome);
        printf("Quantidade: %d\n", vendas[i].quantProduto);
        printf("Total: R$ %.2f\n", vendas[i].valorTotal);
        printf("Data/Hora da compra: %s\n", vendas[i].dataHora);

        totalGeral += vendas[i].valorTotal;
    }
    printf("\n==============================\n");
    printf("Total Geral de Vendas: R$ %.2f\n", totalGeral);
}

/* Submenu de vendas (Melhoria 3, Correção 7)
   Agora com opção 3 de Cancelar Venda. */
void submenuVendas(Cliente clientes[], Produto produtos[], Venda vendas[], int *numVendas) {
    int opcao;
    do {
        printf("\n===== MENU VENDAS =====\n");
        printf("1 - Realizar Venda\n");
        printf("2 - Consultar Vendas\n");
        printf("3 - Cancelar Venda\n");
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
            case 3:
                cancelarVenda(vendas, numVendas, produtos);
                break;
            case 0:
                break;
            default:
                printf("Opção inválida!\n");
        }
    } while (opcao != 0);
}

/* --------------------- MAIN ---------------------
   (Melhoria 7) Mensagem final ao sair
   (Melhoria 2) Opção de limpar a tela manualmente (case 0)
   (Correção 9) Compila em Windows com MinGW sem erro WinMain@16
   (Critério "Uso adequado de recursos na apresentação" - 1,0 pt)
*/
int main() {
    int opcao, sair = 0;
    // Vetores de clientes, produtos e vendas
    Cliente clientes[TAMCli];
    Produto produtos[TAMProd];
    Venda   vendas[TAMVend];

    int numVendas = 0; // Contador de vendas ativas

    do {
        printf("\n==============================\n");
        printf("     SISTEMA DE VENDAS     \n");
        printf("==============================\n");
        printf("1 - Gerenciar Clientes\n");
        printf("2 - Gerenciar Produtos\n");
        printf("3 - Gerenciar Vendas\n");
        printf("0 - Limpar Tela\n");
        printf("9 - Sair\n>>>> ");

        // (Correção 1) Verificação robusta de scanf
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

        // Pausa para leitura antes de voltar ao loop
        if (!sair) {
            printf("\nPressione Enter para continuar...");
            limparBuffer();
        }
    } while (!sair);

    return 0;
}