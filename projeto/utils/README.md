# Programação e Algoritmos - IADE UE <!-- omit in toc -->

# Estruturas de Dados <!-- omit in toc -->

Este repositório contém o código fonte de uma coleção de estruturas de dados implementadas em C.

O código da lista ligada, da qual dependem as restantes estruturas, não está incluído: É necessário implementar o contrato da lista em `src/singly_linked_list.c`.

- [Atualização do repositório](#atualização-do-repositório)
- [Testes unitários](#testes-unitários)

## Atualização do repositório

Para obter as alterações mais recentes ao repositório é necessário:

1. Registar o repositório como referência remota `upstream`:

        git remote add upstream https://github.com/IADE-PA/utils

2. Obter as alterações para a máquina local:

        git fetch upstream

3. Propagar as alterações para o repositório local:

        git checkout upstream/main .

## Testes unitários

Existem testes unitários para a Lista Ligada e para a Tabela de Dispersão Aberta.

A bateria de testes unitários pode ser executada com

        make tests