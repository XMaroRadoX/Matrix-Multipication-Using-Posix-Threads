#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>
#include <time.h>
/*
This file is used to test and compare the performance of the different versions of the matrix multiplication function.
using posix threads to parallelize the matrix multiplication function.
there are three versions of the function:
    matmult - the original function
    matmult_v1 - the function that uses pthreads to parallelize the elements
    matmult_v2 - the function that uses pthreads to parallelize the rows

their implementations are in matmult.c
feel free to change the values of l, m, and n to change the size of the matrices.
performance is measured by the time it takes to run the function and is returned in seconds at the end of the program.
*/


/*
*To run this program run : "make"
*/


/* This code is used to determine the value of an item in a 2D matrix.
 *Inputs:
 *    X - a 2D matrix of doubles
 *    I - the row index
 *    J - the column index
 *    NCOL - the number of columns in the matrix
 *Output:
 *    The value of the item at the given row and column indices.
 */
#define Item(X, I, J, NCOL) X[((J) + (I) * (NCOL))]

/*
 * Function: matmult
 * -----------------
 * This function computes the matrix product of the
 * l x m matrix matrixA and the m x n matrix matrixB, storing the
 * result in the l x n matrix matrixC.  The matrix elements
 * are represented as 32-bit integers.  The matrix
 * elements are stored in row-major order, i.e., the
 * element matrixA[i][j] is stored at matrixA[i*m + j].
 *
 * matrixA: pointer to the first element of the l x m matrix matrixA
 * matrixB: pointer to the first element of the m x n matrix matrixB
 * matrixC: pointer to the first element of the l x n matrix matrixC
 * l: number of rows in matrixA and matrixC
 * m: number of columns in matrixA and rows in matrixB
 * n: number of columns in matrixB and matrixC
 */
void matmult(int *matrixA, int *matrixB, int *matrixC, int l, int m, int n);
void matmult_v1(int *matrixA, int *matrixB, int *matrixC, int l, int m, int n);
void matmult_v2(int *matrixA, int *matrixB, int *matrixC, int l, int m, int n);
void populateMatrix(int *X, int nrow, int ncol);
void printMatrix(int *X, int nrow, int ncol);
int main()
{
    // change values to control size of matrices
    int l = 3, m = 3, n = 3; 
    int *matrixA = (int *)malloc(l * m * sizeof(int));
    int *matrixB = (int *)malloc(m * n * sizeof(int));
    int *matrixC = (int *)malloc(l * n * sizeof(int));
    if (matrixA == NULL || matrixB == NULL || matrixC == NULL)
    {
        perror("Error allocating memory");
    }

    populateMatrix(matrixA, l, m);
    populateMatrix(matrixB, m, n);

    clock_t start_process = clock();
    matmult(matrixA, matrixB, matrixC, l, m, n);
    clock_t end_process = clock();

    printf("Matrix A:\n");
    printMatrix(matrixA, l, m);
    printf("Matrix B:\n");
    printMatrix(matrixB, m, n);
    printf("Matrix C (single process):\n");
    printMatrix(matrixC, l, n);

    clock_t start_t1 = clock();
    matmult_v1(matrixA, matrixB, matrixC, l, m, n);
    clock_t end_t1 = clock();
    printf("Matrix C (each element by a thread):\n");
    printMatrix(matrixC, l, n);

    clock_t start_t2 = clock();
    matmult_v2(matrixA, matrixB, matrixC, l, m, n);
    clock_t end_t2 = clock();
    printf("Matrix C (each row by a thread):\n");
    printMatrix(matrixC, l, n);


    printf("Time taken by a single process: %f\n", (double)(end_process - start_process) / CLOCKS_PER_SEC);
    printf("Time taken by a thread per element: %f\n", (double)(end_t1 - start_t1) / CLOCKS_PER_SEC);
    printf("Time taken by a thread per row: %f\n", (double)(end_t2 - start_t2) / CLOCKS_PER_SEC);

    free(matrixA);
    free(matrixB);
    free(matrixC);

    return 0;
}

/*
 * fill in a matrix with random numbers
 */
void populateMatrix(int *X, int nrow, int ncol)
{
    for (int i = 0; i < nrow; i++)
        for (int j = 0; j < ncol; j++)
            Item(X, i, j, ncol) = (((long)X) + ((long)&nrow) + ((long)&nrow) - (~(i * ncol + nrow) + (j * nrow + ncol))) % 29311 % 10;
}

/*
 * Description: prints the matrix X
 * Input: X, the matrix to be printed
 *        nrow, the number of rows in X
 *        ncol, the number of columns in X
 * Output: Printed matrix
 */

void printMatrix(int *X, int nrow, int ncol)
{
    for (int i = 0; i < nrow; i++)
    {
        for (int j = 0; j < ncol; j++)
            printf("%d\t", Item(X, i, j, ncol));
        printf("\n");
    }
    printf("\n");
    printf("\n");
}
