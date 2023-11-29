#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define SIZE 3 // Assuming square matrices of size SIZE x SIZE
#define NUM_THREADS SIZE * SIZE

int matrixA[SIZE][SIZE];
int matrixB[SIZE][SIZE];
int resultMatrix[SIZE][SIZE];

pthread_t threads[NUM_THREADS];

// Structure to pass data to each thread
struct ThreadData {
    int row;
    int col;
};

// Function to perform matrix multiplication for a specific element
void *multiply(void *arg) {
    struct ThreadData *data = (struct ThreadData *)arg;

    int i = data->row;
    int j = data->col;

    resultMatrix[i][j] = 0;
    for (int k = 0; k < SIZE; ++k) {
        resultMatrix[i][j] += matrixA[i][k] * matrixB[k][j];
    }

    pthread_exit(NULL);
}

// Function to initialize matrices with random values
void initializeMatrices() {
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            matrixA[i][j] = rand() % 10;
            matrixB[i][j] = rand() % 10;
        }
    }
}

// Function to print a matrix
void printMatrix(int matrix[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            printf("%d\t", matrix[i][j]);
        }
        printf("\n");
    }
}

int main() {
    // Initialize matrices
    initializeMatrices();

    // Print input matrices
    printf("Matrix A:\n");
    printMatrix(matrixA);

    printf("\nMatrix B:\n");
    printMatrix(matrixB);

    // Create threads for each element of the result matrix
    struct ThreadData threadData[NUM_THREADS];

    int thread_count = 0;
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            threadData[thread_count].row = i;
            threadData[thread_count].col = j;

            pthread_create(&threads[thread_count], NULL, multiply, (void *)&threadData[thread_count]);
            thread_count++;
        }
    }

    // Wait for threads to finish
    for (int i = 0; i < NUM_THREADS; ++i) {
        pthread_join(threads[i], NULL);
    }

    // Print result matrix
    printf("\nResult Matrix:\n");
    printMatrix(resultMatrix);

    return 0;
}
