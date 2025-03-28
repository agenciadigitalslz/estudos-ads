# Documentação do Projeto: Sistema de Vendas em C

## Menu de Navegação

- [1. Introdução](#1-introdução)
- [2. Objetivos do Projeto](#2-objetivos-do-projeto)
  - [Funcionalidades Básicas](#funcionalidades-básicas)
  - [Critérios Avaliativos Essenciais](#critérios-avaliativos-essenciais)
- [3. Estrutura do Sistema](#3-estrutura-do-sistema)
  - [3.1 Estruturas de Dados](#31-estruturas-de-dados)
  - [3.2 Funções Principais](#32-funções-principais)
- [4. Fluxo do Sistema](#4-fluxo-do-sistema)

## 1. Introdução
Este projeto implementa um sistema de vendas em C, no qual o usuário pode cadastrar clientes e produtos, realizar vendas com controle de estoque, cancelar vendas e consultar as transações efetuadas. O sistema foi desenvolvido para consolidar os conhecimentos adquiridos na disciplina, respeitando os critérios avaliativos propostos e agregando melhorias significativas à estrutura original.

> 💡 As melhorias implementadas, como a validação de entrada, controle manual da tela, registro de data/hora e cancelamento de vendas com retorno de estoque, agregam robustez sem comprometer os requisitos essenciais.

## 2. Objetivos do Projeto
### Funcionalidades Básicas
- **Cadastro de Clientes:** Armazena nome e ID único.
- **Cadastro de Produtos:** Armazena nome, quantidade, valor e ID único.
- **Realização de Vendas:** Solicita ID do cliente, ID do produto e quantidade, valida o estoque, atualiza, calcula o total e registra a venda com data e hora.
- **Consulta de Dados:** Exibe clientes, produtos e histórico de vendas.
- **Cancelamento de Venda:** Permite deletar uma venda e retorna os produtos ao estoque automaticamente.

### Critérios Avaliativos Essenciais
- **Registro dos Dados da Compra:** Armazena ID do cliente, ID do produto, quantidade e valor total da venda.
- **Cálculo Correto do Total:** Multiplicação precisa de quantidade × valor unitário.
- **Validação do Estoque:** Bloqueia vendas quando o estoque é insuficiente.
- **Relatório de Vendas:** Lista todas as vendas e exibe o valor total acumulado.

## 3. Estrutura do Sistema
### 3.1 Estruturas de Dados
- **Produto:** ID, nome, quantidade, valor
- **Cliente:** ID, nome
- **Venda:** ID do cliente, ID do produto, quantidade, valor total, data e hora

### 3.2 Funções Principais
- `limparBuffer()`: Evita travamentos por entradas inválidas.
- `clearScreen()`: Limpa o terminal sob comando do usuário.
- `cadastrarCliente() / cadastrarProduto()`: Cadastro com validação e ID único.
- `consultarCliente() / consultarProduto()`: Exibe os dados com organização.
- `realizarVenda()`: Valida dados, verifica estoque, calcula valor e registra com data/hora.
- `consultarVendas()`: Exibe todas as vendas com detalhes e valor total.
- `cancelarVenda()`: Cancela venda e devolve itens ao estoque.
- `main()`: Gerencia o fluxo do sistema com menus interativos.

## 4. Fluxo do Sistema
### Menu Principal
```
1 - Gerenciar Clientes
2 - Gerenciar Produtos
3 - Gerenciar Vendas
0 - Limpar Tela
9 - Sair
```

### Validação de Entrada
Todos os campos exigem entrada válida (numérica ou textual, conforme necessário). Entradas inválidas são interceptadas e tratadas.

### Processamento
- Os submenus organizam as ações.
- Vendas incluem validação, registro e cálculo automático.
- Relatórios exibem os dados com clareza e soma geral das vendas.
- Cancelamentos são registrados e revertidos no estoque.

## 5. Melhorias Implementadas

### Interface e Usabilidade
✅ **Controle Manual da Tela:** Permite ao usuário limpar a tela quando necessário
✅ **Submenus Interativos:** Navegação intuitiva entre diferentes funcionalidades
✅ **Organização Visual Aprimorada:** Layout mais claro e informativo
✅ **Mensagens Personalizadas de Encerramento:** Feedback amigável ao sair do sistema

### Funcionalidades Avançadas
✅ **Cadastro Dinâmico com Limite:** Gerenciamento eficiente da memória
✅ **Remoção Lógica por ID:** Exclusão segura sem comprometer a integridade dos dados
✅ **Cancelamento de Venda com Retorno ao Estoque:** Reversão automática de transações
✅ **Emissão de Nota Fiscal:** Simulação de comprovante para o cliente

### Exibição e Registro de Dados
✅ **Exibição de IDs nos Relatórios:** Facilita rastreamento e referência
✅ **Atualização de Estoque Após Venda:** Controle em tempo real do inventário
✅ **Registro e Exibição de Data e Hora:** Timestamp preciso para cada transação
✅ **Validação Robusta de Entradas:** Previne erros de digitação e dados inválidos

### Compatibilidade
✅ **ClearScreen Multiplataforma:** Funciona em Windows, Linux e macOS

## 6. Correções Técnicas Aplicadas

### Segurança e Validação
🛠️ **Validação de Entradas:** Previne crashes por dados incorretos
🛠️ **Verificação de IDs Válidos:** Garante referências a registros existentes
🛠️ **Bloqueio de Vendas sem Estoque:** Impede operações impossíveis
🛠️ **Mensagens Claras de Erro:** Orienta o usuário sobre problemas encontrados

### Integridade de Dados
🛠️ **Controle de Limites de Vetores:** Previne acessos inválidos à memória
🛠️ **Ignora Itens Excluídos:** Mantém consistência nos relatórios e operações

### Otimizações de Código
🛠️ **Remoção de Itens Repetidos no Menu:** Interface mais limpa e eficiente
🛠️ **Compatibilidade com Compiladores Windows:** Suporte ao MinGW
🛠️ **Declaração Antecipada de Funções:** Estrutura de código mais organizada

## 7. Critérios Avaliativos Atendidos
🎯 **1ª Etapa – Postagem da Implementação (4,0 pts)**
- ✅ Registro dos dados da compra
- ✅ Cálculo do valor total corretamente

🎯 **2ª Etapa – Socialização e Apresentação (6,0 pts)**
- ✅ Validação correta do estoque
- ✅ Geração clara e funcional do relatório de vendas
- ✅ Apresentação clara e recursos bem utilizados

## 8. Compilação e Execução
**Pré-requisitos:** Compilador C (GCC recomendado).

### Compilar:
```bash
gcc sistema_vendas.c -o sistema_vendas
```

### Executar:
```bash
./sistema_vendas
```

## 9. Conclusão
Este projeto consolida conceitos fundamentais de programação em C, incluindo validação de entradas, uso de estruturas, controle de fluxo e operações com arrays. A implementação vai além dos critérios avaliativos básicos, incorporando melhorias significativas como registro de data/hora, controle de estoque, cancelamento de vendas e interface mais intuitiva. 

A documentação e o código estão organizados e preparados para futuras expansões como persistência de dados ou interface gráfica. Esse projeto demonstra boas práticas e reflete atenção aos detalhes e à experiência do usuário final.

---

> "Projetar sistemas é como contar uma história: cada função revela um capítulo de lógica, cada variável carrega um significado, e cada estrutura dá vida à ideia."

---

**Autor:** André Lopes  
**Disciplina:** Linguagem de Programação com C  
**Curso:** Análise e Desenvolvimento de Sistemas
**Instituição:** Universidade Estatual do Maranhão
