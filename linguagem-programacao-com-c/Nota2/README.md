# <p align="center">Documentação do Simulador Salários de Funcionários</p>
<p align="center">Linguagem de Programação - Funcionários (Nota 2)</p>

## 1. Introdução

Este programa em C foi desenvolvido para gerenciar e analisar dados de funcionários, calculando estatísticas específicas baseadas em critérios estabelecidos.

## 2. Critérios Avaliativos Principais

### 2.1. Entrada de Dados (2,0 pontos)
- Coleta de informações dos funcionários:
  - Salário
  - Idade
  - Sexo (1-feminino, 2-masculino)
  - Estado Civil (1-casado, 2-solteiro)
  - Quantidade de Filhos

### 2.2. Média Salarial dos Pais Idosos Solteiros (2,0 pontos)
- Critérios de filtro:
  - Idade >= 50 anos
  - Estado Civil: Solteiro
  - Possui filhos (qtdFilhos >= 1)
- Cálculo da média salarial deste grupo específico

### 2.3. Maior Salário entre Mulheres sem Filhos (3,0 pontos)
- Critérios de filtro:
  - Sexo: Feminino
  - Sem filhos (qtdFilhos = 0)
- Identificação do maior salário neste grupo

### 2.4. Quantidade de Pais Adolescentes (3,0 pontos)
- Critérios de filtro:
  - Idade < 18 anos
  - Não solteiros
  - Salário > R$ 3.000
  - Possui filhos
- Contagem total deste grupo específico

## 3. Melhorias Implementadas

### 3.1. Estruturação do Código
- Implementação de constantes simbólicas
- Funções separadas para cada responsabilidade
- Validação robusta de dados

### 3.2. Validações de Entrada
- Salário: Valores positivos apenas
- Idade: Entre 14 e 90 anos
- Quantidade de Filhos: Entre 0 e 10
- Sexo: Opções válidas (1 ou 2)
- Estado Civil: Opções válidas (1 ou 2)

### 3.3. Estatísticas Adicionais
- Média salarial geral
- Distribuição por gênero
- Média de idade
- Percentual de funcionários com filhos
- Distribuição por estado civil

### 3.4. Interface e Usabilidade
- Mensagens claras de erro
- Formatação visual melhorada
- Limpeza de buffer após entradas
- Feedback para usuário

## 4. Como Executar

1. Compile o programa:
```bash
gcc Nota2.c -o Nota2
```

2. Execute o programa:
```bash
./Nota2
```

## 5. Observações Técnicas
- Linguagem: C
- Total de Funcionários: 10
- Requisitos do Sistema: Compilador C (GCC recomendado)