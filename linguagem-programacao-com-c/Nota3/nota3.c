// Disciplina  : [Linguagem de Programação com C]
// Professor   : Pedro Brandão Neto 
// Descrição   : Sistema de Vendas
// Autor(a)    : André Lopes, Andressa Souza e Pedro Aurélio.
// Data atual  : 26/03/2025

/**
 * Sistema de Vendas
 * 
 * Este programa implementa um sistema completo de vendas com gerenciamento de
 * clientes, produtos e vendas. Inclui funcionalidades como cadastro, consulta
 * e exclusão de clientes e produtos, além de realizar vendas, gerar notas fiscais
 * e relatórios de vendas.
 */

#include <stdio.h>   // Fornece funções de entrada e saída como printf(), scanf(), etc.
#include <stdlib.h>  // Fornece funções de alocação de memória, conversão de tipos, etc.
#include <string.h>  // Fornece funções de manipulação de strings.
#include <time.h>    // Fornece funções de manipulação de data e hora.

// (Correção 2) Definição de limites para clientes, produtos e vendas, evitando estouro de vetores
#define TAMCli 5     // Limite máximo de clientes no sistema
#define TAMProd 5    // Limite máximo de produtos no sistema
#define TAMVend 10   // Limite máximo de vendas no sistema

/**
 * Limpa o buffer de entrada para evitar problemas com entradas inválidas
 * (Correção 1) Evita loop com entradas inválidas
 * (Critério de Validação de Entradas).
 */
void limparBuffer() {
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF);
}

/**
 * Limpa a tela do console de forma compatível com diferentes sistemas operacionais
 * (Melhoria 2) Controle manual de limpeza de tela,
 * permitindo ao usuário decidir quando limpar (cross-plataforma).
 */
void clearScreen() {
#ifdef _WIN32
    system("cls"); // (Correção 1) Limpa a tela no Windows
#else
    system("clear"); // (Correção 1) Limpa a tela no Linux/Mac
#endif
}

/**
 * Estrutura para armazenar dados de produtos
 * (1º Critério "Registro dos dados da compra" - 2,0 pts)
 * (Correção 5) Estruturas separadas para cada entidade
 * (Melhoria 9) IDs exibidos em relatórios.
 */
typedef struct {              // Struct para armazenar dados de produtos
    int id;                   // (Melhoria 9) ID único do produto
    char nome[20];            // Nome do produto
    int quantidade;           // Quantidade em estoque
    float valor;              // Preço unitário
} Produto;

/**
 * Estrutura para armazenar dados de clientes
 * Mantém informações básicas de identificação do cliente
 * (Melhoria 9) Uso de ID para facilitar operações e relatórios
 */
typedef struct {
    int id;                   // (Melhoria 9) ID único do cliente
    char nome[20];            // Nome do cliente
} Cliente;

/**
 * Estrutura para armazenar dados de vendas
 * (Melhoria 12) dataHora para armazenar momento da venda.
 * (Critério "Registro dos dados da compra/vendas").
 * Armazena todas as informações necessárias para rastreamento e relatórios de vendas
 */
typedef struct {              // Struct para armazenar dados de vendas
    int idVenda;              // (Melhoria 5) ID interno da venda
    int idCliente;            // ID do cliente
    int idProduto;            // ID do produto
    int quantProduto;         // Quantidade vendida
    float valorTotal;         // Valor total
    char dataHora[30];        // Data/hora da compra
} Venda;

/* (Correção 2) Controladores globais */
int totalClientes = 0;        // Contador global de clientes cadastrados
int totalProdutos = 0;        // Contador global de produtos cadastrados

/* ----------------------- CLIENTES ----------------------- */
/**
 * Cadastra um novo cliente no sistema
 * (Melhoria 4) Cadastro dinâmico (até TAMCli)
 * (Correção 6) Bloqueia cadastro além do limite
 * 
 * Esta função verifica se há espaço disponível, solicita os dados do cliente,      
 * valida as entradas e armazena o novo cliente no array.
 * 
 * @param c Array de clientes onde o novo cliente será armazenado
 */
void cadastrarCliente(Cliente c[]) {
    if (totalClientes >= TAMCli) {                           // Verifica se o limite de clientes foi atingido
        printf("\nLimite de clientes atingido.\n");          // Exibe mensagem de erro
        return;                                              // Encerra a função
    }
    printf("Cliente %d, Primeiro Nome: ", totalClientes + 1); // Solicita o nome do cliente
    if (scanf("%19s", c[totalClientes].nome) != 1) {         // Lê o nome com limite de 19 caracteres e verifica se a leitura foi bem-sucedida
        limparBuffer();                                       // Limpa o buffer de entrada
        printf("Entrada inválida para o nome do cliente. Tente novamente.\n"); // Exibe mensagem de erro
        return;                                              // Encerra a função
    }
    // (Melhoria 9) ID do cliente
    c[totalClientes].id = totalClientes + 1;                 // Atribui um ID sequencial ao cliente
    totalClientes++;                                         // Incrementa o contador de clientes
    printf("Cliente cadastrado com sucesso!\n");             // Exibe mensagem de sucesso
}

/**
 * Exibe a lista de todos os clientes cadastrados
 * (Melhoria 3) Relatório de clientes
 * 
 * Percorre o array de clientes e exibe os dados de cada cliente ativo.
 * Ignora clientes que foram logicamente excluídos (ID = 0).
 * 
 * @param c Array de clientes a serem consultados
 */
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

/**
 * Remove logicamente um cliente do sistema por ID
 * (Melhoria 6) Deleção lógica de cliente
 * 
 * Ao invés de remover fisicamente o cliente do array, marca-o como excluído
 * definindo seu ID como 0 e limpando seus dados. Isso evita problemas com
 * referências em vendas existentes.
 * 
 * @param c Array de clientes onde a exclusão será realizada
 */
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

/**
 * Submenu para gerenciamento de clientes
 * (Melhoria 3, Correção 7)
 * 
 * Apresenta um menu interativo para operações relacionadas a clientes.
 * Implementa um loop que continua até o usuário escolher sair.
 * 
 * @param clientes Array de clientes a ser gerenciado
 */
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

/**
 * Cadastra um novo produto no sistema
 * 
 * Verifica se há espaço disponível, solicita os dados do produto (nome, quantidade, valor),
 * valida as entradas e armazena o novo produto no array com um ID único.
 * 
 * @param p Array de produtos onde o novo produto será armazenado
 */
void cadastrarProduto(Produto p[]) {
    // Verifica se o limite de produtos foi atingido
    if (totalProdutos >= TAMProd) {
        printf("\nLimite de produtos atingido.\n");
        return;
    }
    // Solicita o nome do produto
    printf("\nNome do Produto %d: ", totalProdutos + 1);
    // Verifica se a entrada do nome é válida
    if (scanf("%19s", p[totalProdutos].nome) != 1) {
        limparBuffer();
        printf("Entrada inválida para o nome do produto. Tente novamente.\n");
        return;
    }
    // Solicita a quantidade do produto
    printf("Quantidade: ");
    // Verifica se a entrada da quantidade é válida
    if (scanf("%d", &p[totalProdutos].quantidade) != 1) {
        limparBuffer();
        printf("Entrada inválida para a quantidade. Tente novamente.\n");
        return;
    }
    // Solicita o valor do produto
    printf("Valor: ");
    // Verifica se a entrada do valor é válida
    if (scanf("%f", &p[totalProdutos].valor) != 1) {
        limparBuffer();
        printf("Entrada inválida para o valor. Tente novamente.\n");
        return;
    }
    // Atribui um ID único ao produto
    p[totalProdutos].id = totalProdutos + 1;
    // Incrementa o contador de produtos
    totalProdutos++;
    // Informa que o cadastro foi bem-sucedido
    printf("Produto cadastrado com sucesso!\n");
}

/**
 * Exibe a lista de todos os produtos cadastrados
 * 
 * Percorre o array de produtos e exibe os dados de cada produto ativo,
 * incluindo ID, nome, quantidade em estoque e valor unitário.
 * Ignora produtos que foram logicamente excluídos (ID = 0).
 * 
 * @param p Array de produtos a serem consultados
 */
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

/**
 * Remove logicamente um produto do sistema por ID
 * 
 * Similar à exclusão de clientes, marca o produto como excluído
 * definindo seu ID como 0 e limpando seus dados. Isso preserva
 * a integridade referencial com vendas existentes.
 * 
 * @param p Array de produtos onde a exclusão será realizada
 */
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

/**
 * Submenu para gerenciamento de produtos
 * (Melhoria 3)
 * 
 * Apresenta um menu interativo para operações relacionadas a produtos.
 * Implementa um loop que continua até o usuário escolher sair.
 * Inclui opções para cadastrar, consultar e deletar produtos.
 * 
 * @param produtos Array de produtos a ser gerenciado
 */
void submenuProdutos(Produto produtos[]) {
    int opcao;
    do {
        // Exibe o menu de opções para gerenciamento de produtos
        printf("\n===== MENU PRODUTOS =====\n");
        printf("1 - Cadastrar Produto\n");
        printf("2 - Consultar Produtos\n");
        printf("3 - Deletar Produto por ID\n");
        printf("0 - Voltar\n>>>> ");

        // Verifica se a entrada do usuário é válida
        if (scanf("%d", &opcao) != 1) {
            limparBuffer();
            printf("Opção inválida!\n");
            continue;
        }
        limparBuffer(); // Limpa o buffer de entrada

        // Processa a opção escolhida pelo usuário
        switch (opcao) {
            case 1:
                cadastrarProduto(produtos); // Chama a função para cadastrar um novo produto
                break;
            case 2:
                consultarProduto(produtos); // Chama a função para consultar produtos existentes
                break;
            case 3:
                deletarProduto(produtos); // Chama a função para deletar um produto por ID
                break;
            case 0:
                break; // Retorna ao menu principal
            default:
                printf("Opção inválida!\n"); // Mensagem para opções fora do intervalo válido
        }
    } while (opcao != 0); // Continua no submenu até que o usuário escolha sair
}

/* ----------------------- VENDAS ----------------------- */

/**
 * Exibe a nota fiscal formatada de uma venda
 * 
 * Formata e apresenta todos os detalhes da venda em formato de nota fiscal,
 * incluindo data/hora, identificação da venda, dados do cliente, produto,
 * quantidade, valores unitário e total.
 * 
 * @param venda Dados da venda a ser exibida
 * @param cliente Dados do cliente da venda
 * @param produto Dados do produto vendido
 */
void exibirNotaFiscal(Venda venda, Cliente cliente, Produto produto) {
    printf("\n==================================\n");
    printf("           NOTA FISCAL           \n");
    printf("==================================\n");
    printf("Data/Hora: %s\n", venda.dataHora);
    printf("Venda #%d\n\n", venda.idVenda);
    printf("Cliente: %s (ID: %d)\n", cliente.nome, cliente.id);
    printf("----------------------------------\n");
    printf("PRODUTO:      %s\n", produto.nome);
    printf("Quantidade:   %d\n", venda.quantProduto);
    printf("Valor Unit.:  R$ %.2f\n", produto.valor);
    printf("----------------------------------\n");
    printf("VALOR TOTAL:  R$ %.2f\n", venda.valorTotal);
    printf("==================================\n");
    printf("       OBRIGADO PELA COMPRA      \n");
    printf("==================================\n");
}

/**
 * Realiza uma nova venda no sistema
 * (Critério "Registro dos dados da compra" - 2,0 pts)
 * (Correção 3, 4) Validamos cliente e produto antes
 * (Critério "Validação do estoque" - 3,0 pts)
 * 
 * Solicita e valida os dados da venda (cliente, produto, quantidade),
 * verifica disponibilidade em estoque, atualiza o estoque, calcula o valor total,
 * registra a data/hora da transação e armazena a venda no sistema.
 * Oferece a opção de emitir nota fiscal.
 * 
 * @param clientes Array de clientes disponíveis
 * @param produtos Array de produtos disponíveis
 * @param vendas Array onde a nova venda será armazenada
 * @param numVendas Ponteiro para o contador de vendas
 */
void realizarVenda(Cliente clientes[], Produto produtos[], Venda vendas[], int *numVendas) {
    int idCliente, idProduto, quantidade;

    printf("\nDigite o ID do Cliente: ");
    // Verifica se o ID do cliente é válido, está dentro dos limites e se o cliente não foi excluído
    if (scanf("%d", &idCliente) != 1 || idCliente < 1 || idCliente > totalClientes || clientes[idCliente - 1].id == 0) {
        limparBuffer();
        printf("ID de cliente inválido.\n");
        return;
    }

    printf("Digite o ID do Produto: ");
    // Verifica se o ID do produto é válido, está dentro dos limites e se o produto não foi excluído
    if (scanf("%d", &idProduto) != 1 || idProduto < 1 || idProduto > totalProdutos || produtos[idProduto - 1].id == 0) {
        limparBuffer();
        printf("ID de produto inválido.\n");
        return;
    }

    printf("Digite a quantidade desejada: ");
    // Verifica se a quantidade é válida e positiva
    if (scanf("%d", &quantidade) != 1 || quantidade <= 0) {
        limparBuffer();
        printf("Quantidade inválida.\n");
        return;
    }

    // Verifica se há estoque suficiente para realizar a venda
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

    // Realizar a incrementação do numVendas antes de perguntar sobre a nota
    (*numVendas)++;

    // Perguntar sobre emissão da nota fiscal
    char resposta;
    printf("\nEmitir via do cliente? (S/N): ");
    scanf(" %c", &resposta);  // Espaço antes do %c para ignorar whitespace
    limparBuffer();
    
    if (resposta == 'S' || resposta == 's') {
        // Emitir nota fiscal
        exibirNotaFiscal(vendas[(*numVendas) - 1], clientes[idCliente-1], produtos[idProduto-1]);
    }

    printf("\nVenda #%d realizada com sucesso! Total: R$ %.2f\n",
           (*numVendas), total);
}

/**
 * Cancela uma venda existente e restaura o estoque
 * (Melhoria 5) Função para cancelar uma venda por ID
 * Retorna a quantidade cancelada para o estoque do produto
 * e realoca as vendas subsequentes.
 * 
 * Solicita o ID da venda a ser cancelada, valida a existência da venda,
 * restaura a quantidade vendida ao estoque do produto correspondente,
 * e reorganiza o array de vendas para remover a venda cancelada.
 * 
 * @param vendas Array de vendas
 * @param numVendas Ponteiro para o contador de vendas
 * @param produtos Array de produtos para restaurar estoque
 */
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

/**
 * Exibe o relatório de todas as vendas realizadas
 * (Critério "Geração do relatório de vendas" - 2,0 pts)
 * 
 * Percorre o array de vendas e exibe os detalhes de cada venda,
 * incluindo cliente, produto, quantidade, valor e data/hora.
 * Calcula e exibe o valor total de todas as vendas ao final.
 * 
 * @param vendas Array de vendas a serem consultadas
 * @param numVendas Número total de vendas
 * @param clientes Array de clientes para exibir nomes
 * @param produtos Array de produtos para exibir detalhes
 */
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

/**
 * Submenu para gerenciamento de vendas
 * (Melhoria 3, Correção 7)
 * Agora com opção 3 de Cancelar Venda.
 * 
 * Apresenta um menu interativo para operações relacionadas a vendas.
 * Implementa um loop que continua até o usuário escolher sair.
 * Inclui opções para realizar vendas, consultar histórico e cancelar vendas.
 * 
 * @param clientes Array de clientes disponíveis
 * @param produtos Array de produtos disponíveis
 * @param vendas Array de vendas a ser gerenciado
 * @param numVendas Ponteiro para o contador de vendas
 */
void submenuVendas(Cliente clientes[], Produto produtos[], Venda vendas[], int *numVendas) {
    int opcao;
    do {
        // Exibe o menu de vendas com as opções disponíveis
        printf("\n===== MENU VENDAS =====\n");
        printf("1 - Realizar Venda\n");
        printf("2 - Consultar Vendas\n");
        printf("3 - Cancelar Venda\n");
        printf("0 - Voltar\n>>>> ");

        // Verifica se a entrada do usuário é válida
        if (scanf("%d", &opcao) != 1) {
            limparBuffer();
            printf("Opção inválida!\n");
            continue;
        }
        limparBuffer(); // Limpa o buffer de entrada

        // Processa a opção escolhida pelo usuário
        switch (opcao) {
            case 1:
                // Chama a função para realizar uma nova venda
                realizarVenda(clientes, produtos, vendas, numVendas);
                break;
            case 2:
                // Chama a função para consultar o histórico de vendas
                consultarVendas(vendas, *numVendas, clientes, produtos);
                break;
            case 3:
                // Chama a função para cancelar uma venda existente
                cancelarVenda(vendas, numVendas, produtos);
                break;
            case 0:
                // Retorna ao menu principal
                break;
            default:
                // Mensagem para opções fora do intervalo válido
                printf("Opção inválida!\n");
        }
    } while (opcao != 0); // Continua no menu até o usuário escolher sair
}

/**
 * Função principal do programa
 * (Melhoria 7) Mensagem final ao sair
 * (Melhoria 2) Opção de limpar a tela manualmente (case 0)
 * (Correção 9) Compila em Windows com MinGW sem erro WinMain@16
 * (Critério "Uso adequado de recursos na apresentação" - 1,0 pt)
 * 
 * Inicializa as estruturas de dados, apresenta o menu principal
 * e gerencia o fluxo do programa. Implementa um loop que continua
 * até o usuário escolher sair. Chama os submenus apropriados
 * com base na escolha do usuário.
 * 
 * @return 0 quando o programa é encerrado com sucesso
 */
int main() {
    int opcao, sair = 0;
    // Vetores de clientes, produtos e vendas
    Cliente clientes[TAMCli];      // Array para armazenar os clientes cadastrados
    Produto produtos[TAMProd];     // Array para armazenar os produtos cadastrados
    Venda   vendas[TAMVend];       // Array para armazenar as vendas realizadas

    int numVendas = 0;             // Contador de vendas ativas

    do {
        // Exibe o cabeçalho do menu principal
        printf("\n==============================\n");
        printf("     SISTEMA DE VENDAS     \n");
        printf("==============================\n");
        // Exibe as opções disponíveis para o usuário
        printf("1 - Gerenciar Clientes\n");
        printf("2 - Gerenciar Produtos\n");
        printf("3 - Gerenciar Vendas\n");
        printf("0 - Limpar Tela\n");
        printf("9 - Sair\n>>>> ");

        // (Correção 1) Verificação robusta de scanf
        if (scanf("%d", &opcao) != 1) {
            limparBuffer();        // Limpa o buffer de entrada em caso de erro
            printf("\nComando inválido!\n");
            continue;              // Volta ao início do loop
        }
        limparBuffer();            // Limpa o buffer após leitura bem-sucedida

        // Processa a opção escolhida pelo usuário
        switch (opcao) {
            case 1:
                submenuClientes(clientes);    // Acessa o submenu de gerenciamento de clientes
                break;
            case 2:
                submenuProdutos(produtos);    // Acessa o submenu de gerenciamento de produtos
                break;
            case 3:
                submenuVendas(clientes, produtos, vendas, &numVendas);  // Acessa o submenu de vendas
                break;
            case 0:
                clearScreen();                 // Limpa a tela do console
                break;
            case 9:
                sair = 1;                      // Define a flag para sair do programa
                printf("\nEncerrando o programa. Obrigado por utilizar o sistema!\n");
                break;
            default:
                printf("\nOpção inválida!\n");  // Mensagem para opções fora do intervalo válido
        }

        // Pausa para leitura antes de voltar ao loop
        if (!sair) {
            printf("\nPressione Enter para continuar...");
            limparBuffer();        // Aguarda que o usuário pressione Enter
        }
    } while (!sair);               // Continua no loop até que o usuário escolha sair

    return 0;                      // Encerra o programa com código de sucesso
}