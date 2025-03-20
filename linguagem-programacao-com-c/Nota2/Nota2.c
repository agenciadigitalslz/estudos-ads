#include <stdio.h>
#include <stdlib.h>

// Definição de constantes
#define IDADE_IDOSO 50
#define IDADE_ADOLESCENTE 18
#define SALARIO_MINIMO 3000.0
#define TOTAL_FUNCIONARIOS 10

// Função para limpar o buffer do teclado
void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Função para validar entrada numérica
float lerSalario() {
    float valor;
    do {
        printf("Digite o salario (maior que 0): ");
        scanf("%f", &valor);
        limparBuffer();
        if (valor <= 0) {
            printf("Erro: Salario deve ser maior que 0!\n");
        }
    } while (valor <= 0);
    return valor;
}

int lerIdade() {
    int idade;
    do {
        printf("Digite a idade (entre 14 e 90): ");
        scanf("%d", &idade);
        limparBuffer();
        if (idade < 14 || idade > 90) {
            printf("Erro: Idade deve estar entre 14 e 90 anos!\n");
        }
    } while (idade < 14 || idade > 90);
    return idade;
}

int main() {
    // Abertura do programa
    printf("=======================\n");
    printf("Cadastro de Funcionários\n");
    printf("=======================\n");
    printf("Seja bem vindo, informe os funcionarios abaixo\n\n");
    
    // Variáveis para dados da atividade base
    float salario, somaSalariosIdososSolteiros = 0.0;
    int idade, sexo, estadoCivil, qtdFilhos;
    int contIdososSolteiros = 0, contPaisAdolescentes = 0;
    float maxSalarioMulherSemFilhos = -1.0;
    
    // Variáveis para estatísticas extras
    float totalSalario = 0.0;
    float minSalario, maxSalario;
    int totalFuncionarios = 10;
    int somaIdade = 0;
    int countFemale = 0, countMale = 0;
    float somaSalarioFemale = 0.0, somaSalarioMale = 0.0;
    int contPais = 0;
    int somaFilhosPais = 0;
    int contCasado = 0, contSolteiro = 0;
    
    // Leitura dos dados para 10 funcionários
    for (int i = 0; i < TOTAL_FUNCIONARIOS; i++) {
        printf("\n=== Funcionario %d ===\n", i + 1);
        
        salario = lerSalario();
        idade = lerIdade();
        
        do {
            printf("Digite o sexo (1-feminino, 2-masculino): ");
            scanf("%d", &sexo);
            limparBuffer();
            if (sexo != 1 && sexo != 2) {
                printf("Erro: Digite 1 para feminino ou 2 para masculino!\n");
            }
        } while (sexo != 1 && sexo != 2);
        
        do {
            printf("Digite o estado civil (1-casado, 2-solteiro): ");
            scanf("%d", &estadoCivil);
            limparBuffer();
            if (estadoCivil != 1 && estadoCivil != 2) {
                printf("Erro: Digite 1 para casado ou 2 para solteiro!\n");
            }
        } while (estadoCivil != 1 && estadoCivil != 2);
        
        do {
            printf("Digite a quantidade de filhos (0-10): ");
            scanf("%d", &qtdFilhos);
            limparBuffer();
            if (qtdFilhos < 0 || qtdFilhos > 10) {
                printf("Erro: Quantidade de filhos deve estar entre 0 e 10!\n");
            }
        } while (qtdFilhos < 0 || qtdFilhos > 10);

        // Estatísticas extras: Atualizações
        totalSalario += salario;
        somaIdade += idade;
        
        if (i == 0) {
            minSalario = salario;
            maxSalario = salario;
        } else {
            if (salario < minSalario)
                minSalario = salario;
            if (salario > maxSalario)
                maxSalario = salario;
        }
        
        if (sexo == 1) {
            countFemale++;
            somaSalarioFemale += salario;
        } else if (sexo == 2) {
            countMale++;
            somaSalarioMale += salario;
        }
        
        if (qtdFilhos >= 1) {
            contPais++;
            somaFilhosPais += qtdFilhos;
        }
        
        if (estadoCivil == 1) {
            contCasado++;
        } else if (estadoCivil == 2) {
            contSolteiro++;
        }
        
        // Atividade base
        // a) Média salarial dos pais idosos solteiros (idade >= 50, solteiro e com filhos)
        if (qtdFilhos >= 1 && idade >= 50 && estadoCivil == 2) {
            somaSalariosIdososSolteiros += salario;
            contIdososSolteiros++;
        }
        
        // b) Maior salário entre mulheres sem filhos
        if (sexo == 1 && qtdFilhos == 0) {
            if (salario > maxSalarioMulherSemFilhos) {
                maxSalarioMulherSemFilhos = salario;
            }
        }
        
        // c) Quantidade de pais adolescentes: idade < 18, nao solteiros e salario > 3000
        if (qtdFilhos >= 1 && idade < 18 && estadoCivil != 2 && salario > 3000) {
            contPaisAdolescentes++;
        }
    }
    
    // Exibição dos resultados da atividade base
    printf("================================\n");
    if (contIdososSolteiros > 0)
        printf("Media salarial dos pais idosos solteiros: %.2f\n", somaSalariosIdososSolteiros / contIdososSolteiros);
    else
        printf("Media salarial dos pais idosos solteiros: N/A\n");
    
    if (maxSalarioMulherSemFilhos >= 0)
        printf("Maior salario entre as mulheres sem filhos: %.2f\n", maxSalarioMulherSemFilhos);
    else
        printf("Maior salario entre as mulheres sem filhos: N/A\n");
    
    printf("Quantidade de pais adolescentes (idade < 18, nao solteiros e salario > 3000): %d\n", contPaisAdolescentes);
    printf("================================\n");
    
    // Estatísticas extras enriquecidas
    printf("Media salarial geral: %.2f\n", totalSalario / totalFuncionarios);
    printf("Salario minimo: %.2f | Salario maximo: %.2f\n", minSalario, maxSalario);
    printf("Media de idade dos funcionarios: %.2f\n", somaIdade / (float)totalFuncionarios);
    printf("Distribuicao por genero: Feminino = %d (%.2f%%), Masculino = %d (%.2f%%)\n", 
           countFemale, (countFemale * 100.0 / totalFuncionarios), 
           countMale, (countMale * 100.0 / totalFuncionarios));
    printf("Media salarial por genero: Feminino = %.2f, Masculino = %.2f\n", 
           (countFemale > 0 ? somaSalarioFemale / countFemale : 0.0), 
           (countMale > 0 ? somaSalarioMale / countMale : 0.0));
    printf("Percentual de funcionarios pais: %.2f%%\n", contPais * 100.0 / totalFuncionarios);
    printf("Media de filhos entre os pais: %.2f\n", (contPais > 0 ? somaFilhosPais / (float)contPais : 0.0));
    printf("Distribuicao por estado civil: Casados = %d (%.2f%%), Solteiros = %d (%.2f%%)\n", 
           contCasado, contCasado * 100.0 / totalFuncionarios, 
           contSolteiro, contSolteiro * 100.0 / totalFuncionarios);
    printf("================================\n");
    
    return 0;
}
