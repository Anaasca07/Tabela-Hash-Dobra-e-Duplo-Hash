# Tabela-Hash-Dobra-e-Duplo-Hash 

## Descrição
O código em C implementa um sistema que vai gerenciar os contatos utilizando tabela hash e o método de dobra. O código tem como objetivo principal fazer o usuário inserir, buscar e remover contatos. O objetivo do código é criar um sistema responsável por gerenciar contatos, usando uma tabela para armazenar contatos de forma eficaz, que permite operações básicas no gerenciamento.

# Funções utilizades

## Função de mapeamento: Método de dobra

O método de dobramento é uma técnica usada para criar uma função hash para itens baseados em caracteres, como strings. Envolve tratar a string como uma sequência de valores ordinais, somando-os e usando o método restante para obter um valor hash. O método de dobramento pode ser melhorado usando a posição do personagem como peso, o que pode ajudar a reduzir colisões.

## Tratamento de colisão: Duplo hash (endereçamento aberto)

A ideia por trás do hash duplo é usar duas funções hash para calcular dois valores hash diferentes para uma determinada chave. A primeira função hash é usada para calcular o valor hash inicial e a segunda função hash é usada para calcular o tamanho do passo para a sequência de sondagem.

Quando ocorre uma colisão, a sequência de teste é calculada adicionando o tamanho do passo ao valor de hash inicial e a sequência de teste é seguida até que um slot vazio seja encontrado.

