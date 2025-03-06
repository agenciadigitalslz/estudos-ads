#include <stdio.h>
#include <locale.h>  // Biblioteca para suporte a acentuação

// Funções auxiliares
float definirPercentualParcela(int numParcelas) {
    switch(numParcelas) {
        case 12: return 0.30; // 30%
        case 24: return 0.50; // 50%
        case 36: return 0.75; // 75%
        case 48: return 0.90; // 90%
        default: return 0;
    }
}

float calcularJuros(int numParcelas) {
    switch(numParcelas) {
        case 12: return 0.015; // 1.5%
        case 24: return 0.020; // 2.0%
        case 36: return 0.025; // 2.5%
        case 48: return 0.030; // 3.0%
        default: return 0;
    }
}

void exibirSeparador() {
    printf("\n============================================\n");
}

int main() {
    setlocale(LC_ALL, "Portuguese_Brazil.1252");  // Configura o locale para português
    
    // Declaração de variáveis
    float salario, divida, valorEmprestimo;
    int numParcelas, tempoEmprego;
    
    exibirSeparador();
    printf("SIMULADOR DE EMPRÉSTIMO\n");
    exibirSeparador();

    // Entrada de Dados com validação
    do {
        printf("Digite o salario mensal (maior que 0): R$ ");
        scanf("%f", &salario);
    } while (salario <= 0);

    printf("Digite o valor total das dividas atuais: R$ ");
    scanf("%f", &divida);

    do {
        printf("Digite o valor solicitado para emprestimo (maior que 0): R$ ");
        scanf("%f", &valorEmprestimo);
    } while (valorEmprestimo <= 0);

    printf("Digite o numero de parcelas (12, 24, 36 ou 48): ");
    scanf("%d", &numParcelas);
    
    if (numParcelas != 12 && numParcelas != 24 && numParcelas != 36 && numParcelas != 48) {
        printf("\nERRO: Número de parcelas inválido. Use 12, 24, 36 ou 48 parcelas.\n");
        return 1;
    }

    printf("Digite o tempo de estabilidade no emprego (em anos): ");
    scanf("%d", &tempoEmprego);

    exibirSeparador();
    printf("ANÁLISE DO EMPRÉSTIMO\n");
    exibirSeparador();

    // Cálculo da Taxa de Endividamento
    float taxaEndividamento = divida / salario;
    if (taxaEndividamento > 0.5) {
        printf("Empréstimo RECUSADO\n");
        printf("Taxa de endividamento: %.2f%% (superior a 50%%)\n", taxaEndividamento * 100);
        return 0;
    }

    // Definição do percentual da parcela baseado no número de parcelas
    float percentualMax = definirPercentualParcela(numParcelas);
    float taxaJuros = calcularJuros(numParcelas);
    
    // Cálculo do valor total com juros
    float valorTotal = valorEmprestimo * (1 + (taxaJuros * numParcelas));
    float valorParcela = valorTotal / numParcelas;

    if (valorParcela > salario * percentualMax) {
        printf("Empréstimo RECUSADO\n");
        printf("Valor da parcela (R$ %.2f) ultrapassa %.0f%% do salário\n", 
               valorParcela, percentualMax * 100);
        return 0;
    }

    // Verificação do tempo de emprego
    int maxParcelas;
    if (tempoEmprego < 1) {
        maxParcelas = 12;
    } else if (tempoEmprego >= 1 && tempoEmprego <= 3) {
        maxParcelas = 24;
    } else {
        maxParcelas = 48;
    }

    if (numParcelas > maxParcelas) {
        printf("Empréstimo RECUSADO\n");
        printf("Limite máximo de parcelas para seu tempo de emprego: %d\n", maxParcelas);
        return 0;
    }

    // Aprovação e detalhamento
    exibirSeparador();
    printf("EMPRÉSTIMO APROVADO!\n");
    exibirSeparador();
    printf("Detalhamento do empréstimo:\n\n");
    printf("Valor solicitado: R$ %.2f\n", valorEmprestimo);
    printf("Número de parcelas: %d\n", numParcelas);
    printf("Taxa de juros mensal: %.1f%%\n", taxaJuros * 100);
    printf("Percentual máximo da parcela: %.0f%% do salário\n", percentualMax * 100);
    printf("Valor da parcela: R$ %.2f\n", valorParcela);
    printf("Taxa de endividamento: %.2f%%\n", taxaEndividamento * 100);
    printf("Valor total a pagar: R$ %.2f\n", valorTotal);
    printf("Total de juros: R$ %.2f\n", valorTotal - valorEmprestimo);
    exibirSeparador();

    return 0;
}