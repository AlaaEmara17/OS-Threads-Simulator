#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>

// Structure to hold matrix data
typedef struct {
    int rows;
    int cols;
    int **data;
} Matrix;


// Function to allocate matrix
Matrix* createMatrix(int rows, int cols) {

}

// Function to free matrix
void freeMatrix(Matrix *mat) {

}

// Function to read matrices from file
int readMatrices(Matrix **mat1, Matrix **mat2) {
    
}

// Function to print matrix
void printMatrix(Matrix *mat) {
    for (int i = 0; i < mat->rows; i++) {
        for (int j = 0; j < mat->cols; j++) {
            printf("%d", mat->data[i][j]);
            if (j < mat->cols - 1) printf(" ");
        }
        printf("\n");
    }
}


// Method 1: One thread per element
void multiplyMatricesPerElement(Matrix *mat1, Matrix *mat2, Matrix **result) {

}

// Method 2: One thread per row
void multiplyMatricesPerRow(Matrix *mat1, Matrix *mat2, Matrix **result) {
    

}

int main() {

    Matrix *mat1, *mat2, *result1, *result2;

    // Read matrices from file
    if (readMatrices(&mat1, &mat2) != 0) {
        fprintf(stderr, "Error reading matrices\n");
        return 1;
    }

    // Method 1: Per element
    multiplyMatricesPerElement(mat1, mat2, &result1);
    printMatrix(result1);

    // Method 2: Per row
    multiplyMatricesPerRow(mat1, mat2, &result2);
    printMatrix(result2);

    // Cleanup
    freeMatrix(mat1);
    freeMatrix(mat2);
    freeMatrix(result1);
    freeMatrix(result2);

    return 0;
}
