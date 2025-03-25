# Sistema de Vendas em C

Este projeto implementa um sistema de vendas desenvolvido em linguagem C. O objetivo principal é permitir o cadastro de clientes e produtos, a realização de vendas com controle de estoque, e a consulta de transações efetuadas. O sistema foi criado para consolidar conhecimentos práticos em programação estruturada, além de atender a critérios de avaliação em um contexto acadêmico.

## 🎓 Objetivos do Projeto

### Funcionalidades Principais
- Cadastro de clientes
- Cadastro de produtos
- Realização de vendas (com controle de estoque)
- Consulta de clientes, produtos e vendas
- Cancelamento de vendas
- Registro da data e hora de cada venda
- Relatório de vendas com valor total acumulado

### Critérios Avaliativos Atendidos
- Registro completo da venda (ID cliente, ID produto, quantidade e valor total)
- Cálculo correto do valor da venda
- Validação de estoque antes da venda
- Geração de relatório de vendas com dados organizados
- Uso adequado de recursos de apresentação (menus, separadores e feedback ao usuário)

---

## 📊 Estrutura do Sistema

### Estruturas de Dados
- `Cliente`: ID e nome
- `Produto`: ID, nome, quantidade e valor
- `Venda`: ID do cliente, ID do produto, quantidade, valor total, data e hora da compra

### Fluxo do Sistema

O programa é controlado pelo `main()` e exibe um menu principal com opções de gerenciamento de:

1. Clientes
2. Produtos
3. Vendas
0. Limpar Tela
9. Sair do Sistema

Cada módulo possui submenu próprio com opções específicas.

---

## ✨ Melhorias Implementadas

- **Validação robusta de entradas** com `scanf` e `limparBuffer()`
- **Controle manual da limpeza da tela** (`clearScreen()` multiplataforma)
- **Submenus interativos** por categoria (Clientes, Produtos, Vendas)
- **Cadastro dinâmico limitado a 5 registros por categoria**
- **Remoção lógica** de clientes e produtos por ID
- **Cancelamento de venda por ID**, com retorno do estoque
- **Exibição dos IDs nos relatórios** (Cliente e Produto)
- **Data e hora da venda** registradas no relatório
- **Mensagens claras e intuitivas** ao usuário final
- **Organização visual aprimorada** com espaçamento e separadores

---

## 🚀 Correções Aplicadas

- Prevenção de loops infinitos com entradas inválidas
- Verificação de IDs antes de operações
- Bloqueio de vendas com estoque insuficiente
- Verificação se cliente/produto foi removido antes de usar
- Limitação de cadastros após atingir capacidade
- Padronização de mensagens de erro e confirmação
- Compatibilidade com compilação no Windows (GCC MinGW)
- Declaração antecipada de funções para evitar warnings

---

## ⚙️ Compilação e Execução

### Requisitos
- GCC ou outro compilador C compatível

### Compilar
```bash
gcc sistema_vendas.c -o sistema_vendas
```

### Executar
```bash
./sistema_vendas
```

No Windows, utilize `sistema_vendas.exe` após compilar.

---

## 🌟 Conclusão

Este sistema demonstra a prática de conceitos fundamentais de programação estruturada em C, com foco em organização modular, clareza de código, validação robusta de entradas e experiência intuitiva para o usuário.

A documentação, os menus interativos, os relatórios bem formatados e a funcionalidade de cancelamento de venda com ajuste de estoque conferem à aplicação um padrão profissional e confiável para fins acadêmicos ou projetos iniciais.

> "Projetar sistemas é como contar uma história: cada função revela um capítulo de lógica, cada variável carrega um significado, e cada estrutura dá vida à ideia."

---

**Autor:** André Lopes  
**Disciplina:** Linguagem de Programação com C  
**Curso:** Análise e Desenvolvimento de Sistemas
