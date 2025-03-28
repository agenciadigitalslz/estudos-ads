# 📊 Sistema de Vendas em C

<div align="center">
  <img src="https://img.shields.io/badge/Linguagem-C-blue" alt="Linguagem C">
  <img src="https://img.shields.io/badge/Versão-1.0-green" alt="Versão 1.0">
  <img src="https://img.shields.io/badge/Status-Concluído-success" alt="Status: Concluído">
</div>

## 📝 Sumário
- [Introdução](#-introdução)
- [Objetivos do Projeto](#-objetivos-do-projeto)
- [Estrutura do Sistema](#-estrutura-do-sistema)
- [Fluxo do Sistema](#-fluxo-do-sistema)
- [Melhorias Implementadas](#-melhorias-implementadas)
- [Correções Técnicas](#-correções-técnicas-aplicadas)
- [Critérios Avaliativos](#-critérios-avaliativos-atendidos)
- [Compilação e Execução](#-compilação-e-execução)
- [Conclusão](#-conclusão)

## 🚀 Introdução
Este projeto implementa um sistema de vendas em C, no qual o usuário pode cadastrar clientes e produtos, realizar vendas com controle de estoque, cancelar vendas e consultar as transações efetuadas. O sistema foi desenvolvido para consolidar os conhecimentos adquiridos na disciplina, respeitando os critérios avaliativos propostos e agregando melhorias significativas à estrutura original.

> 💡 **Destaque:** As melhorias implementadas, como a validação de entrada, controle manual da tela, registro de data/hora e cancelamento de vendas com retorno de estoque, agregam robustez sem comprometer os requisitos essenciais.

## 🎯 Objetivos do Projeto
### ✨ Funcionalidades Básicas
- **📋 Cadastro de Clientes:** Armazena nome e ID único.
- **📦 Cadastro de Produtos:** Armazena nome, quantidade, valor e ID único.
- **💰 Realização de Vendas:** Solicita ID do cliente, ID do produto e quantidade, valida o estoque, atualiza, calcula o total e registra a venda com data e hora.
- **🔍 Consulta de Dados:** Exibe clientes, produtos e histórico de vendas.
- **❌ Cancelamento de Venda:** Permite deletar uma venda e retorna os produtos ao estoque automaticamente.

### 📊 Critérios Avaliativos Essenciais
- **📝 Registro dos Dados da Compra:** Armazena ID do cliente, ID do produto, quantidade e valor total da venda.
- **🧮 Cálculo Correto do Total:** Multiplicação precisa de quantidade × valor unitário.
- **⚠️ Validação do Estoque:** Bloqueia vendas quando o estoque é insuficiente.
- **📈 Relatório de Vendas:** Lista todas as vendas e exibe o valor total acumulado.

## 🏗️ Estrutura do Sistema
### 📊 Estruturas de Dados
| Estrutura | Campos |
|-----------|--------|
| **Produto** | ID, nome, quantidade, valor |
| **Cliente** | ID, nome |
| **Venda** | ID do cliente, ID do produto, quantidade, valor total, data e hora |

### ⚙️ Funções Principais
| Função | Descrição |
|--------|-----------|
| `limparBuffer()` | Evita travamentos por entradas inválidas |
| `clearScreen()` | Limpa o terminal sob comando do usuário |
| `cadastrarCliente() / cadastrarProduto()` | Cadastro com validação e ID único |
| `consultarCliente() / consultarProduto()` | Exibe os dados com organização |
| `realizarVenda()` | Valida dados, verifica estoque, calcula valor e registra com data/hora |
| `consultarVendas()` | Exibe todas as vendas com detalhes e valor total |
| `cancelarVenda()` | Cancela venda e devolve itens ao estoque |
| `main()` | Gerencia o fluxo do sistema com menus interativos |

## 🔄 Fluxo do Sistema
### 📱 Menu Principal
