#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define MAX 10000 

// Struct for thread arguments
typedef struct {
    int left;
    int right;
    int *arr;
} ThreadArgs;

// Merge function (same as your original)
void merge(int arr[], int left, int mid, int right) {
    int i, j, k;
    int n1 = mid - left + 1;
    int n2 = right - mid;

    int *L = malloc(n1 * sizeof(int));
    int *R = malloc(n2 * sizeof(int));

    for (i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    i = 0;
    j = 0;
    k = left;

    while (i < n1 && j < n2) {
        if (L[i] <= R[j])
            arr[k++] = L[i++];
        else
            arr[k++] = R[j++];
    }

    while (i < n1)
        arr[k++] = L[i++];

    while (j < n2)
        arr[k++] = R[j++];

    free(L);
    free(R);
}

void* threaded_merge_sort(void* arg) {
    ThreadArgs *data = (ThreadArgs *)arg;
    if( (data->right - data ->left ) +1 < 2){
        return data->arr ;
    }
    else{
        pthread_t l , r ;
        ThreadArgs *argsL = malloc(sizeof(ThreadArgs));
        ThreadArgs *argsR = malloc(sizeof(ThreadArgs));
        argsL->left= data->left; 
        int mid = (data->right + data->left)/2 ;
        argsL->right = mid ;
        argsR->left = mid + 1 ;
        argsR->right = data->right ;
        argsR->arr = data->arr ; argsL->arr = data->arr;
      
        pthread_create(&l , NULL , threaded_merge_sort , argsL );
        pthread_create(&r , NULL , threaded_merge_sort , argsR);
        pthread_join (l , NULL);
        pthread_join (r , NULL);
        merge(data->arr , argsL->left , mid , argsR->right);
        free(argsR);
        free(argsL);
    }
    
    return NULL ;

    // you have to Implement the full function to be using the merge function
    // and to call it in the main

}

int main() {
    FILE* file = fopen("sample_input.txt", "r");
    if (!file) {
        printf("Error opening file.\n");
        return 1;
    }

    int n;
    fscanf(file, "%d", &n);
    int arr[MAX];
    for (int i = 0; i < n; i++) {
        fscanf(file, "%d", &arr[i]); 
    }
    fclose(file);

    // Make the required changes inorder to be able to call the Thread fn
    if(n > 1 ){
        // main thread 
         pthread_t thread ;
            ThreadArgs* t1 = malloc(sizeof(ThreadArgs));
              int mid =( (n -1)/2 );
            t1->left = 0 ; t1->right = n-1;
            t1->arr = arr;
            pthread_create(&thread , NULL , threaded_merge_sort , t1);
            pthread_join(thread , NULL );
            merge(arr , t1->left , mid , t1->right);
            free(t1);
         
    }
    /*You code*/

    printf("Sorted array:\n");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}
