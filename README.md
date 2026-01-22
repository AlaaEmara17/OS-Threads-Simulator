# Pthread Parallel Algorithms

This project implements multi-threaded versions of **Matrix Multiplication** and **Merge Sort** using the POSIX threads (Pthreads) library. It was developed to demonstrate concurrency concepts, thread synchronization, and how different threading granularities affect performance in an Operating Systems context.

---

## Matrix Multiplication

The matrix multiplication program calculates the product of two matrices read from `matrix_input.txt`. It compares two different threading strategies to measure execution time.

### 1. One Thread Per Element
In this approach, a unique thread is spawned for every single cell in the resulting matrix.

- **Logic:** If the result is a $10 \times 10$ matrix, 100 threads are created.
- **Behavior:** Each thread calculates a single value and then terminates.

### 2. One Thread Per Row
In this approach, one thread is responsible for calculating an entire row of the resulting matrix.

- **Logic:** If the result is a $10 \times 10$ matrix, only 10 threads are created.
- **Behavior:** This typically reduces the overhead of thread creation compared to the "per element" method.

---

## Merge Sort

The merge sort implementation uses a recursive multi-threading approach to sort an array of integers provided in `sample_input.txt`.

### Parallel Divide and Conquer
- **Thread Creation:** For every split in the array, two new threads are created to sort the left and right subarrays.
- **Synchronization:** The parent thread uses `pthread_join` to ensure both children have finished their work before merging the results back together.

---

## Setup and Compilation

A `Makefile` is included to handle the compilation process and set permissions.

### 1. Build the Project
Compile both the Matrix Multiplication and Merge Sort programs:
```bash
make all
```

### 2. Run Matrix Multiplication
The default run command executes the matrix multiplication binary:
```bash
make run_mult
```

### 3. Run Merge Sort
To run the merge sort program independently:
```bash
make run_mergesort
```

### 4. Clean Up
Remove the compiled binaries:
```bash
make clean 
```

---

## Input File Formats

### `matrix_input.txt`
The file should contain dimensions followed by matrix data:
```plaintext
3 5              # Matrix A: Rows Cols
1 -2 3 4 5       # Row data...
...
5 4              # Matrix B: Rows Cols
-1 2 3 4         # Row data...
```

### `sample_input.txt`
The file should contain the number of elements followed by the array:
```plaintext
10               # Number of elements
100 20 15 3 4 ... # Array elements
```

---

## Performance Monitoring

The Matrix Multiplication program uses `gettimeofday` to provide high-resolution timing for both methods. The results are printed in milliseconds (msec) to help you analyze which threading strategy is more efficient for your specific hardware.