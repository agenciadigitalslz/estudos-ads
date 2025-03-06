#include <stdio.h>

int main() {
    // Declaração de variáveis
    float salario, divida, valorEmprestimo, percentualMax;
    int numParcelas, tempoEmprego; // tempo de estabilidade no emprego em anos

    // Entrada de Dados
    printf("Digite o salario mensal: ");
    scanf("%f", &salario);

    printf("Digite o valor total das dividas atuais: ");
    scanf("%f", &divida);

    printf("Digite o valor solicitado para emprestimo: ");
    scanf("%f", &valorEmprestimo);

    printf("Digite o numero desejado de parcelas: ");
    scanf("%d", &numParcelas);

    printf("Digite o tempo de estabilidade no emprego (em anos): ");
    scanf("%d", &tempoEmprego);

    printf("Digite o percentual maximo permitido da parcela em relacao ao salario (ex: 0.3 para 30%%): ");
    scanf("%f", &percentualMax);

    // Cálculo da Taxa de Endividamento
    float taxaEndividamento = divida / salario;
    if (taxaEndividamento > 0.5) {
        printf("Emprestimo recusado: taxa de endividamento (%.2f) superior a 50%%.\n", taxaEndividamento);
        return 0;
    }

    // Cálculo do valor de cada parcela
    float valorParcela = valorEmprestimo / numParcelas;
    if (valorParcela > salario * percentualMax) {
        printf("Emprestimo recusado: valor da parcela (%.2f) ultrapassa o percentual maximo permitido (%.2f do salario).\n", valorParcela, salario * percentualMax);
        return 0;
    }

    // Verificação do tempo de estabilidade no emprego e limite maximo de parcelas
    int maxParcelas;
    if (tempoEmprego < 1) {
        maxParcelas = 12;
    } else if (tempoEmprego >= 1 && tempoEmprego <= 3) {
        maxParcelas = 24;
    } else { // tempoEmprego > 3
        maxParcelas = 60;
    }

    if (numParcelas > maxParcelas) {
        printf("Emprestimo recusado: numero de parcelas (%d) excede o limite permitido (%d) para %d ano(s) de emprego.\n", numParcelas, maxParcelas, tempoEmprego);
        return 0;
    }

    // Se todas as condições forem atendidas, empréstimo aprovado
    printf("Emprestimo aprovado.\n");
    return 0;
}