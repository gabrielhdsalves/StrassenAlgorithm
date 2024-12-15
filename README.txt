# Multiplicação de Matrizes de Strassen

## Descrição

Este projeto implementa o algoritmo de multiplicação de matrizes de Strassen, um algoritmo recursivo eficiente para multiplicar duas matrizes quadradas. O algoritmo de Strassen reduz o número de multiplicações necessárias em comparação com o método tradicional de multiplicação de matrizes, melhorando a eficiência de tempo em muitas situações, especialmente para matrizes grandes.

## Como Funciona

O algoritmo de Strassen divide as duas matrizes A e B em quatro submatrizes de tamanho menor e usa sete multiplicações recursivas dessas submatrizes, ao invés de oito multiplicações que seriam necessárias no método convencional. Ele também realiza operações de adição e subtração para combinar os resultados, o que reduz a complexidade computacional.

A complexidade do algoritmo de Strassen é de O(n^log2(7)) ≈ O(n^2.81), enquanto o método tradicional tem complexidade O(n^3).

## Requisitos

- Linguagem de programação: **C** (ou outra linguagem de sua escolha)
- Compilador C (se for utilizar a implementação em C)
  
## Como Usar

1. Clone o repositório:
   ```bash
   git clone https://github.com/gabrielhdsalves/StrassenAlgorithm.git
   cd strassen-matrix-multiplication
