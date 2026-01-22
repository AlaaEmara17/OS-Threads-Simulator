#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>

// Structure to hold matrix data
typedef struct {
    int rows;
    int cols;
    int **data; // dynamic 2d array  data points to array of pointers each pointer representing row
} Matrix;


// Function to allocate matrix
Matrix* createMatrix(int rows, int cols) {
     // just for understanding 
     // mat  [ row , col , *data (array of pointers )[ *r1 , *r2 , *r3 ]]
     //      r1[the actual integers  1 , 2 , 3  ]
        Matrix * mat = malloc(sizeof(Matrix));
        mat->rows = rows ;
        mat->cols = cols;
        mat->data = malloc(rows* sizeof(int*));
        for(int i =0 ; i< rows ; i++){
            mat->data[i] = malloc (cols* sizeof(int));
        }
    return mat;
}

// Function to free matrix
void freeMatrix(Matrix *mat) {

for (int i = 0; i < mat->rows; i++) {
        free(mat->data[i]);   // free each row
    }
    free(mat->data);           // free the array of row pointers
    free(mat); 

}

// Function to read matrices from file
int readMatrices(Matrix **mat1, Matrix **mat2) {
    FILE* file = fopen("matrix_input.txt", "r");

    if (!file) {
        printf("Error opening file.\n");
        return 1;
    }

    int r1 , c1;
    fscanf(file, "%d %d", &r1 , &c1);

    *mat1 = createMatrix(r1 , c1);


    for(int i =0 ; i< r1 ; i++){
        for(int j =0 ; j< c1; j++){
          fscanf(file , "%d" , &((*mat1)->data[i][j]));
        }
    }
     int r2 , c2;
    fscanf(file, "%d %d", &r2 , &c2);

    *mat2 = createMatrix(r2, c2);


    for(int i =0 ; i< r2 ; i++){
        for(int j =0 ; j< c2; j++){
          fscanf(file , "%d" , &((*mat2)->data[i][j]));
        }
    }
    return 0;
    
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
// 
typedef struct{
    Matrix * a ;
    Matrix * b ;
    Matrix *res ;
    int row;
    int col;

}Thread_arguments ;

void * multiply( void*args ){
   Thread_arguments * arg = (Thread_arguments *)args;
   int op =0;
    for(int i =0 ; i< arg->a->cols ; i++){
         op+= arg->a->data[arg->row][i] * arg->b->data[i][arg->col];

    }
    arg->res->data[arg->row][arg->col]= op;
    free(arg);
    return NULL;
}
// Method 1: One thread per element
void multiplyMatricesPerElement(Matrix *mat1, Matrix *mat2, Matrix **result) {
    // i will have thread for each ele #ele = rows *cols 
    pthread_t threads[mat1->cols * mat2->rows];
    int count =0 ;
    for(int i =0 ; i< mat1->rows ; i++){
        for(int j =0 ; j< mat2->cols ; j++){
        Thread_arguments * args = malloc(sizeof(Thread_arguments));
        args->a= mat1 ;
        args->b =mat2 ;
      // current row , col in mat1 , mat2 
        args->row= i;
        args->col= j;
        args->res = *(result);
        pthread_create(&threads[count++] , NULL , multiply ,args );
    }
    }
    for(int k = 0 ; k < count ; k++){
        pthread_join(threads[k] , NULL);
    }
}
void *multiply_per_row(void *args){
  Thread_arguments *arg = (Thread_arguments *) args;
  for(int i =0 ; i< arg->b->cols ; i++){
         int op =0 ; 
         for(int j =0 ; j< arg->a->cols ; j++){
             op += arg->a->data[arg->row][j] * arg->b->data[j][i];            
         }
         arg->res->data[arg->row][i] = op ;
  }
   free(arg);
   return NULL;

}
// Method 2: One thread per row
void multiplyMatricesPerRow(Matrix *mat1, Matrix *mat2, Matrix **result) {
    pthread_t thread [(mat1->rows)];
    for(int i =0 ; i<mat1->rows ; i++){
        Thread_arguments *args = malloc(sizeof(Thread_arguments));
        args->a = mat1 ;
        args->b = mat2;
        args->res= *(result) ;
        args->row= i ;
        pthread_create(&thread[i] , NULL , multiply_per_row , args);
    }
    for(int k = 0 ; k < mat1->rows; k++){
        pthread_join(thread[k] , NULL);
    }

}

int main() {

    Matrix *mat1 ,*mat2, *result1 ,*result2 ;
    // Read matrices from file
    if (readMatrices(&mat1, &mat2) != 0) {
        fprintf(stderr, "Error reading matrices\n");
        return 1;
    }
    result1 = createMatrix(mat1->rows , mat2->cols);
    result2 = createMatrix(mat1->rows , mat2->cols);
    //debugging for creating matrix

    // printMatrix(mat1);
    // printMatrix(mat2);

    // Method 1: Per element
    struct timeval start, end;
 //start  = current wall clock 
    gettimeofday(&start, NULL);
    multiplyMatricesPerElement(mat1, mat2, &result1);
    printMatrix(result1);
    gettimeofday(&end, NULL);
    double elapsed = (end.tv_sec - start.tv_sec)  * 1000.0;    // *1000 convert sec to ms 
     elapsed += (end.tv_usec - start.tv_usec) / 1000.0;   
    printf("END 1     %.3f msec \n" , elapsed );
    // // Method 2: Per row
    gettimeofday(&start, NULL);
    multiplyMatricesPerRow(mat1, mat2, &result2);
    printMatrix(result2);
     gettimeofday(&end, NULL);
     elapsed = (end.tv_sec - start.tv_sec)  * 1000.0;    // *1000 convert sec to ms 
      elapsed += (end.tv_usec - start.tv_usec) / 1000.0;   
    printf("END 2        %.3f msec\n" , elapsed );

    // // Cleanup
    freeMatrix(mat1);
    freeMatrix(mat2);
    freeMatrix(result1);
    freeMatrix(result2);

    return 0;
}
