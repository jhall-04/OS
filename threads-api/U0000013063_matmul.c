#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "common_threads.h"

#define SIZE 3  // Fixed size of the matrix

typedef struct {
    int (*A)[SIZE][SIZE];
    int (*B)[SIZE][SIZE];
    int row;
} MatrixArgs;

// Function to multiply two 3x3 matrices A and B, storing the result in matrix C
void multiplyMatrices(MatrixArgs *args) {
    int (*A)[SIZE][SIZE] = args->A;
    int (*B)[SIZE][SIZE] = args->B;
    int row = args->row;
    int *C[SIZE][SIZE];
    int i, k, j;
    i = row;
    for (j = 0; j < SIZE; j++) {
        C[i][j] = 0;
        for (k = 0; k < SIZE; k++) {
            C[i][j] += *A[i][k] * *B[k][j];
        }
    }
    return C;
}

// Function to print a 3x3 matrix
void printMatrix(int matrix[SIZE][SIZE]) {
int i, j;
    for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int i,j;

    int A[SIZE][SIZE];  // Matrix A
    int B[SIZE][SIZE];  // Matrix B
    int *C[SIZE][SIZE];  // Result matrix

    // Read matrix A from the user
    printf("Enter the elements of matrix A (3x3):\n");
    for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++) {
            printf("A[%d][%d]: ", i, j);
            scanf("%d", &A[i][j]);
        }
    }

    // Read matrix B from the user
    printf("Enter the elements of matrix B (3x3):\n");
    for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++) {
            printf("B[%d][%d]: ", i, j);
            scanf("%d", &B[i][j]);
        }
    }

    MatrixArgs args[SIZE];
    for (i = 0; i < SIZE; i++) {
        args[i].A = &A;
        args[i].B = &B;
        args[i].row = i;
    }

    // Perform matrix multiplication
    pthread_t row1, row2, row3;
    Pthread_create(&row1, NULL, multiplyMatrices, &args[0]);
    Pthread_create(&row2, NULL, multiplyMatrices, &args[1]);
    Pthread_create(&row3, NULL, multiplyMatrices, &args[2]);
    Pthread_join(row1, &C);
    Pthread_join(row2, &C);
    Pthread_join(row3, &C);

    // Display the result
    printf("Result of matrix multiplication:\n");
    printMatrix(C);

    return 0;
}

