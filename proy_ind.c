#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int filas;
    int columnas;
    int *datos;
} MATRIZ;

MATRIZ armarMatriz(int filas, int columnas) {
    MATRIZ matriz;
    matriz.filas = filas;
    matriz.columnas = columnas;
    matriz.datos = (int *)malloc(filas * columnas * sizeof(int));
    return matriz;
}

void liberar(MATRIZ *matriz) {
    free(matriz->datos);
}

void imprimir(MATRIZ *matriz) {
    for (int i = 0; i < matriz->filas; i++) {
        for (int j = 0; j < matriz->columnas; j++) {
            printf("%d ", *(matriz->datos + i * matriz->columnas + j));
        }
        printf("\n");
    }
}

MATRIZ suma(MATRIZ *matrizA, MATRIZ *matrizB) {
    MATRIZ suma = armarMatriz(matrizA->filas, matrizA->columnas);
    for (int i = 0; i < matrizA->filas; i++) {
        for (int j = 0; j < matrizA->columnas; j++) {
            *(suma.datos + i * matrizA->columnas + j) = *(matrizA->datos + i * matrizA->columnas + j) +
                                                        *(matrizB->datos + i * matrizA->columnas + j);
        }
    }
    return suma;
}

MATRIZ resta(MATRIZ *matrizA, MATRIZ *matrizB) {
    MATRIZ resta = armarMatriz(matrizA->filas, matrizA->columnas);
    for (int i = 0; i < matrizA->filas; i++) {
        for (int j = 0; j < matrizA->columnas; j++) {
            *(resta.datos + i * matrizA->columnas + j) = *(matrizA->datos + i * matrizA->columnas + j) -
                                                         *(matrizB->datos + i * matrizA->columnas + j);
        }
    }
    return resta;
}

MATRIZ multiplicacion(MATRIZ *matrizA, MATRIZ *matrizB) {
    MATRIZ mult = armarMatriz(matrizA->filas, matrizB->columnas);
    for (int i = 0; i < matrizA->filas; i++) {
        for (int j = 0; j < matrizB->columnas; j++) {
            *(mult.datos + i * mult.columnas + j) = 0; // Inicializar el elemento de la matriz producto
            for (int k = 0; k < matrizA->columnas; k++) {
                *(mult.datos + i * mult.columnas + j) +=
                    *(matrizA->datos + i * matrizA->columnas + k) *
                    *(matrizB->datos + k * matrizB->columnas + j);
            }
        }
    }
    return mult;
}

int main() {
    MATRIZ matrizA = armarMatriz(3, 3);
    MATRIZ matrizB = armarMatriz(3, 3);

    // Inicialización de matrizA con valores predefinidos
    int valoresA[3][3] = {
        {0, 2, 3},
        {90, 9, 6},
        {7, 3, 8}
    };
    
    // Inicialización de matrizB con valores predefinidos
    int valoresB[3][3] = {
        {5, 40, 7},
        {6, 5, 4},
        {30, 6, 1}
    };

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            *(matrizA.datos + i * matrizA.columnas + j) = valoresA[i][j];
            *(matrizB.datos + i * matrizB.columnas + j) = valoresB[i][j];
        }
    }

    printf("Matriz A:\n");
    imprimir(&matrizA);

    printf("\nMatriz B:\n");
    imprimir(&matrizB);

    MATRIZ suma2 = suma(&matrizA, &matrizB);
    printf("\nLa suma de las matrices es:\n");
    imprimir(&suma2);
    liberar(&suma2);

    MATRIZ resta2 = resta(&matrizA, &matrizB);
    printf("\nLa resta de las matrices es:\n");
    imprimir(&resta2);
    liberar(&resta2);

    MATRIZ mult = multiplicacion(&matrizA, &matrizB);
    printf("\nEl producto de las matrices es:\n");
    imprimir(&mult);
    liberar(&mult);

    liberar(&matrizA);
    liberar(&matrizB);

    return 0;
}
