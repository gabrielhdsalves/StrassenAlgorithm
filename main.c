#include <stdio.h>
#include <stdlib.h>

// Gabriel Henrique dos Santos Alves - 2023010208
// Davi Dias Monsores dos Santos - 2023001272

typedef struct rgb {
    int r;
    int g;
    int b;  
} rgb;

rgb **alocaMatriz(int qtdLinha) {
    rgb **matriz = (rgb **) malloc(qtdLinha * sizeof(rgb *));
    for (int i = 0; i < qtdLinha; i++) {
        matriz[i] = (rgb *) calloc(qtdLinha, sizeof(rgb));
    }
    return matriz;
}

void liberaMatriz(rgb **matriz, int qtdLinha) {
    for (int i = 0; i < qtdLinha; i++) {
        free(matriz[i]);
    }
    free(matriz);
}

// Operação de soma das matrizes
rgb **somaMatriz(rgb **matrizA, rgb **matrizB, int tamanho) {
    rgb **resultado = alocaMatriz(tamanho);
    for (int i = 0; i < tamanho; i++) {
        for (int j = 0; j < tamanho; j++) {
            resultado[i][j].r = matrizA[i][j].r + matrizB[i][j].r;
            resultado[i][j].g = matrizA[i][j].g + matrizB[i][j].g;
            resultado[i][j].b = matrizA[i][j].b + matrizB[i][j].b;
        }
    }
    return resultado;
}

// Operação de subtração das matrizes
rgb **subtraiMatriz(rgb **matrizA, rgb **matrizB, int tamanho) {
    rgb **resultado = alocaMatriz(tamanho);
    for (int i = 0; i < tamanho; i++) {
        for (int j = 0; j < tamanho; j++) {
            resultado[i][j].r = matrizA[i][j].r - matrizB[i][j].r;
            resultado[i][j].g = matrizA[i][j].g - matrizB[i][j].g;
            resultado[i][j].b = matrizA[i][j].b - matrizB[i][j].b;
        }
    }
    return resultado;
}

// Função para copiar submatrizes sem precisar alocar memória
void copiaMatriz(rgb **origem, rgb **destino, int linhaInicio, int colunaInicio, int tamanho) {
    for (int i = 0; i < tamanho; i++) {
        for (int j = 0; j < tamanho; j++) {
            destino[linhaInicio + i][colunaInicio + j] = origem[i][j];
        }
    }
}

// Função para salvar submatriz em uma nova matriz alocando memória
rgb **salvaMatriz(rgb **matriz, int linha, int coluna, int tamanho) {
    rgb **resultado = alocaMatriz(tamanho);  // Aloca uma matriz para armazenar a submatriz
    for (int i = 0; i < tamanho; i++) {
        for (int j = 0; j < tamanho; j++) {
            resultado[i][j] = matriz[linha + i][coluna + j];  // Copia os elementos da matriz original
        }
    }
    return resultado;
}

// Implementação recursiva do algoritmo de Strassen
void strassen(rgb **matrizA, rgb **matrizB, rgb **matrizC, int qtdLinha) {
    int tamanho;
    rgb **p1, **p2, **p3, **p4, **p5, **p6, **p7, **a, **e, **b, **f, **c, **g, **d, **h, **c11, **c12, **c21, **c22;

    if (qtdLinha <= 32) {
        // Caso base: multiplicação direta para matrizes 2x2
        for(int i = 0; i < qtdLinha; i++) {
            for(int j = 0; j < qtdLinha; j++) {
                for(int k = 0; k < qtdLinha; k++) {
                    matrizC[i][j].r += matrizA[i][k].r * matrizB[k][j].r;
                    matrizC[i][j].g += matrizA[i][k].g * matrizB[k][j].g;
                    matrizC[i][j].b += matrizA[i][k].b * matrizB[k][j].b;
                }
            }
        }
        return;
    }

    tamanho = qtdLinha / 2;

    // Dividir as matrizes A e B em submatrizes
    a = salvaMatriz(matrizA, 0, 0, tamanho);
    b = salvaMatriz(matrizA, 0, tamanho, tamanho);
    c = salvaMatriz(matrizA, tamanho, 0, tamanho);
    d = salvaMatriz(matrizA, tamanho, tamanho, tamanho);
    
    e = salvaMatriz(matrizB, 0, 0, tamanho);
    f = salvaMatriz(matrizB, 0, tamanho, tamanho);
    g = salvaMatriz(matrizB, tamanho, 0, tamanho);
    h = salvaMatriz(matrizB, tamanho, tamanho, tamanho); 

    // Cálculo de P1 a P7 utilizando chamadas recursivas a Strassen
    p1 = alocaMatriz(tamanho);
    strassen(a, subtraiMatriz(f, h, tamanho), p1, tamanho);

    p2 = alocaMatriz(tamanho);
    strassen(somaMatriz(a, b, tamanho), h, p2, tamanho);

    p3 = alocaMatriz(tamanho);
    strassen(somaMatriz(c, d, tamanho), e, p3, tamanho);

    p4 = alocaMatriz(tamanho);
    strassen(d, subtraiMatriz(g, e, tamanho), p4, tamanho);

    p5 = alocaMatriz(tamanho);
    strassen(somaMatriz(a, d, tamanho), somaMatriz(e, h, tamanho), p5, tamanho);

    p6 = alocaMatriz(tamanho);
    strassen(subtraiMatriz(b, d, tamanho), somaMatriz(g, h, tamanho), p6, tamanho);

    p7 = alocaMatriz(tamanho);
    strassen(subtraiMatriz(a, c, tamanho), somaMatriz(e, f, tamanho), p7, tamanho);

    // Construir matrizC com base nos resultados
    c11 = somaMatriz(subtraiMatriz(somaMatriz(p5, p4, tamanho), p2, tamanho), p6, tamanho);
    c12 = somaMatriz(p1, p2, tamanho);
    c21 = somaMatriz(p3, p4, tamanho);
    c22 = somaMatriz(subtraiMatriz(p5, p3, tamanho), subtraiMatriz(p1, p7, tamanho), tamanho);

    // Copiar os resultados para matrizC
    copiaMatriz(c11, matrizC, 0, 0, tamanho);
    copiaMatriz(c12, matrizC, 0, tamanho, tamanho);
    copiaMatriz(c21, matrizC, tamanho, 0, tamanho);
    copiaMatriz(c22, matrizC, tamanho, tamanho, tamanho);

    // Liberar memória
    liberaMatriz(a, tamanho);
    liberaMatriz(b, tamanho);
    liberaMatriz(c, tamanho);
    liberaMatriz(d, tamanho);
    liberaMatriz(e, tamanho);
    liberaMatriz(f, tamanho);
    liberaMatriz(g, tamanho);
    liberaMatriz(h, tamanho);
    liberaMatriz(p1, tamanho);
    liberaMatriz(p2, tamanho);
    liberaMatriz(p3, tamanho);
    liberaMatriz(p4, tamanho);
    liberaMatriz(p5, tamanho);
    liberaMatriz(p6, tamanho);
    liberaMatriz(p7, tamanho);
    liberaMatriz(c11, tamanho);
    liberaMatriz(c12, tamanho);
    liberaMatriz(c21, tamanho);
    liberaMatriz(c22, tamanho);
}

void printarMatriz(rgb **matriz, int qtdLinha) {
    for (int i = 0; i < qtdLinha; i++) {
        for (int j = 0; j < qtdLinha; j++) {
            printf("%d %d %d ", matriz[i][j].r, matriz[i][j].g, matriz[i][j].b);
        }
        printf("\n");
    }
}

int main() {
    rgb **matrizA, **matrizB, **matrizC;
    int i, j, qtdLinha;
    char extensao[3];
    int bits;

    scanf(" %s", extensao);
    scanf(" %d", &qtdLinha);
    scanf(" %d", &qtdLinha);
    scanf(" %d", &bits);

    // Alocação das matrizes
    matrizA = alocaMatriz(qtdLinha);
    matrizB = alocaMatriz(qtdLinha);
    matrizC = alocaMatriz(qtdLinha);

    // Verificar se houve erro de alocação
    if (!matrizA || !matrizB || !matrizC) {
        printf("Erro ao alocar memoria\n");
        return 1;
    }

    for (i = 0; i < qtdLinha; i++) {
        for (j = 0; j < qtdLinha; j++) {
            scanf(" %d %d %d", &matrizA[i][j].r, &matrizA[i][j].g, &matrizA[i][j].b);
        }
    }

    for (i = 0; i < qtdLinha; i++) {
        for (j = 0; j < qtdLinha; j++) {
            scanf(" %d %d %d", &matrizB[i][j].r, &matrizB[i][j].g, &matrizB[i][j].b);
        }
    }

    strassen(matrizA, matrizB, matrizC, qtdLinha);
    printf("%s\n", extensao);
    printf("%d %d\n", qtdLinha, qtdLinha);
    printf("%d\n", bits);
    printarMatriz(matrizC, qtdLinha);

    // Liberar memória
    liberaMatriz(matrizA, qtdLinha);
    liberaMatriz(matrizB, qtdLinha);
    liberaMatriz(matrizC, qtdLinha);

    return 0;
}