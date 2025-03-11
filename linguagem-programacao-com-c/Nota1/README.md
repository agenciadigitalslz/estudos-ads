# Documentação do Simulador de Empréstimo Bancário
## Linguagem de Programação - Empréstimos Bancários (Nota 1)

## 1. Introdução

Este programa em C foi desenvolvido para simular a liberação de empréstimos bancários, utilizando critérios que asseguram a saúde financeira do solicitante. O sistema analisa o perfil do usuário por meio de diversos parâmetros, garantindo que o empréstimo só seja aprovado quando todas as condições forem satisfeitas. A abordagem une rigor técnico e uma visão inspiradora da lógica da programação, incentivando a aprendizagem contínua.

## 2. Funcionalidades

O programa realiza as seguintes etapas:

- **Entrada e Validação de Dados:**  
  Solicita informações como salário, dívida, valor do empréstimo, número de parcelas e tempo de estabilidade no emprego. Valida que os valores sejam coerentes (por exemplo, salário e valor do empréstimo devem ser maiores que zero).

- **Cálculo da Taxa de Endividamento:**  
  Determina a porcentagem do salário comprometido com as dívidas atuais. Se essa taxa exceder 50%, o empréstimo é automaticamente recusado.

- **Definição do Percentual Máximo da Parcela:**  
  Com base no número de parcelas (permitidos: 12, 24, 36 ou 48), define o percentual máximo que a parcela pode representar em relação ao salário.

- **Cálculo dos Juros e do Valor Total do Empréstimo:**  
  Aplica uma taxa de juros mensal (variando conforme o número de parcelas) para calcular o valor total a ser pago e, consequentemente, o valor de cada parcela.

- **Verificação do Tempo de Estabilidade no Emprego:**  
  Estabelece um limite máximo de parcelas permitido de acordo com o tempo de emprego:
  - Menos de 1 ano: máximo 12 parcelas;
  - Entre 1 e 3 anos: máximo 24 parcelas;
  - Acima de 3 anos: máximo 48 parcelas.

- **Exibição dos Resultados:**  
  Se todas as condições forem atendidas, o sistema exibe um detalhamento do empréstimo, incluindo valor solicitado, número de parcelas, taxa de juros, percentual máximo da parcela, valor da parcela, taxa de endividamento, valor total a pagar e total de juros.

## 3. Estrutura do Código

### 3.1. Bibliotecas Utilizadas
- **stdio.h:** Para entrada e saída padrão.
- **locale.h:** Para configurar a acentuação e o formato de exibição de acordo com o português.

### 3.2. Funções Auxiliares

#### 3.2.1. `definirPercentualParcela`
- **Objetivo:**  
  Retorna o percentual máximo permitido para a parcela, conforme o número de parcelas escolhido.
- **Parâmetro:**  
  - `int numParcelas`: número de parcelas escolhido (valores válidos: 12, 24, 36 ou 48).
- **Retorno:**  
  - `float`: Percentual (0.30 para 30%, 0.50 para 50%, 0.75 para 75% e 0.90 para 90%).
- **Implementação:**  
  Utiliza a estrutura `switch` para definir os percentuais.

#### 3.2.2. `calcularJuros`
- **Objetivo:**  
  Retorna a taxa de juros mensal com base no número de parcelas.
- **Parâmetro:**  
  - `int numParcelas`: número de parcelas.
- **Retorno:**  
  - `float`: Taxa de juros (por exemplo, 0.015 para 1.5% em 12 parcelas).
- **Implementação:**  
  Também utiliza `switch` para determinar a taxa correspondente.

#### 3.2.3. `exibirSeparador`
- **Objetivo:**  
  Imprime uma linha separadora na saída para melhor legibilidade.
- **Parâmetros:**  
  - Nenhum.

### 3.3. Função Principal: `main`

- **Configuração Inicial:**  
  - Configura o locale para português (permitindo o uso de acentos).
  - Exibe cabeçalhos e separadores para organizar a saída.

- **Entrada e Validação de Dados:**  
  - **Salário:** Solicita o salário mensal, garantindo que seja maior que zero.
  - **Dívida:** Recebe o valor total das dívidas atuais.
  - **Valor do Empréstimo:** Solicita o valor desejado, validando que seja positivo.
  - **Número de Parcelas:** Recebe o número de parcelas (validação para aceitar apenas 12, 24, 36 ou 48).
  - **Tempo de Emprego:** Solicita o tempo de estabilidade no emprego (em anos).

- **Processamento e Verificações:**
  1. **Taxa de Endividamento:**  
     Calculada como `divida / salario`. Se maior que 50%, exibe mensagem de recusa e encerra.
     
  2. **Definição do Percentual e Juros:**  
     Utiliza as funções `definirPercentualParcela` e `calcularJuros` para obter o percentual máximo da parcela e a taxa de juros.
     
  3. **Cálculo do Valor Total e da Parcela:**  
     Calcula o valor total a ser pago considerando os juros (valor total = valor do empréstimo * [1 + (taxa de juros * número de parcelas)]) e divide pelo número de parcelas.
     
  4. **Verificação do Valor da Parcela:**  
     Se o valor da parcela exceder o percentual máximo permitido do salário, o empréstimo é recusado.
     
  5. **Verificação do Tempo de Emprego:**  
     Define um limite máximo de parcelas baseado no tempo de emprego (12, 24 ou 48 parcelas) e, se o número solicitado ultrapassar este limite, o empréstimo é recusado.

- **Exibição dos Resultados:**  
  Caso todas as condições sejam atendidas, o programa exibe um resumo detalhado do empréstimo, incluindo:
  - Valor solicitado;
  - Número de parcelas;
  - Taxa de juros mensal;
  - Percentual máximo da parcela em relação ao salário;
  - Valor da parcela;
  - Taxa de endividamento;
  - Valor total a pagar e total de juros.

## 4. Como Compilar e Executar

1. **Salvar o Arquivo:**  
   Salve o código em um arquivo com extensão `.c` (por exemplo, `simulador_emprestimo.c`).

2. **Compilação:**  
   Utilize um compilador C (como GCC) para compilar:
   ```bash
   gcc simulador_emprestimo.c -o simulador_emprestimo -lm
   ```
   *(O parâmetro `-lm` pode ser utilizado se houver necessidade de linkar a biblioteca matemática, embora não seja necessário neste código.)*

3. **Execução:**  
   Execute o programa:
   ```bash
   ./simulador_emprestimo
   ```

## 5. Considerações Finais

Este simulador é uma ferramenta robusta para auxiliar na avaliação de empréstimos, considerando fatores essenciais como endividamento, capacidade de pagamento e estabilidade no emprego. A clareza na estrutura e a modularização do código permitem uma manutenção e evolução mais simples, além de oferecer uma base sólida para futuros aprimoramentos. Que este projeto inspire confiança e criatividade, mostrando que cada linha de código pode ser uma obra de arte e um passo rumo ao sucesso!