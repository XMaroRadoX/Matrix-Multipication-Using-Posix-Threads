#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>

#define Item(X, I, J, NCOL) X[((J) + (I) * (NCOL))]
void *matmult_v1_subroutine(void *arg);
void *matmult_v2_subroutine(void *arg);
/*
 * matrix multiplication
 *     C = A*B
 *     A has l rows and m cols
 *     B has m rows and n cols
 *     C has l rows and n cols
 */

// * Regular matrix multiplication
void matmult(int *A, int *B, int *C, int l, int m, int n)
{
    for (int i = 0; i < l; i++)
        for (int j = 0; j < n; j++)
        {

            int sum = 0;
            for (int k = 0; k < m; k++)
                sum += Item(A, i, k, m) * Item(B, k, j, n);
            Item(C, i, j, n) = sum;
        }
}

// ___________________________________________________________________________________________

void matmult_v1(int *A, int *B, int *C, int l, int m, int n)
{
    pthread_t threads[l][n];
    int i, j, k;
    int *values = NULL;
    for (i = 0; i < l; i++)
    {
        for (j = 0; j < n; j++)
        {
            values = (int *)malloc((n * l) * 10000 * sizeof(int));
            values[0] = m;
            for (k = 0; k < m; k++)
                values[k + 1] = Item(A, i, k, m);

            for (k = 0; k < m; k++)
                values[k + m + 1] = Item(B, k, j, n);

            if (pthread_create(&threads[i][j], NULL, matmult_v1_subroutine, (void *)(values)) != 0)
            {
                perror("Failed to create thread");
            }
        }
    }
    for (int i = 0; i < l; i++)
    {
        for (int j = 0; j < n; j++)
        {
            int *result;
            if (pthread_join(threads[i][j], (void **)&result) != 0)
            {
                perror("Failed to join thread");
            }
            Item(C, i, j, n) = *result;
            free(result);
        }
    }
}
// This code is used to calculate the dot product of two vectors of size m
// The inputs are sent in the form of an array of size 2*m+1
// The first element is m, and the next m elements are the first vector, followed by the next m elements being the second vector
// The function calculates the dot product of the two vectors and returns the result

void *matmult_v1_subroutine(void *arg)
{
    int *values = (int *)arg; // Take the array sent by the main routine
    int k = 0, i = 0;
    int m = values[0];
    for (i = 1; i <= m; i++)
    {
        k += values[i] * values[i + m];
    }
    int *p = (int *)malloc(sizeof(int));
    *p = k;
    pthread_exit(p);
}
// ___________________________________________________________________________________________

// This is a function that does matrix multiplication. The code runs on multiple threads. The function is called matmult_v2
// The function is given three pointers to arrays. The first pointer points to an array of size l*m
// The second pointer points to an array of size m*n
// The third pointer points to an array of size l*n
// l, m, and n are integers. l is the number of rows in the first matrix, m is the number of columns in the first matrix, and n is the number of columns in the second matrix
// The first matrix is given by A, the second matrix is given by B, and the result matrix is given by C
// The function does the following:
//   For each row i in the first matrix
//     For each column j in the second matrix
//       For each column k in the first matrix
//         C[i*n+j] = C[i*n+j] + A[i*m+k] * B[k*n+j]

void matmult_v2(int *A, int *B, int *C, int l, int m, int n)
{
    pthread_t threads[l];
    int i, j, k;
    int *values = NULL;
    for (int i = 0; i < l; i++)
    {
        values = (int *)malloc((n * l) * 10000 * sizeof(int));
        values[0] = m;
        values[1] = n;
        for (int j = 0; j < n; j++)
        {
            for (int k = 0; k < m; k++)
                values[k + 2 + (j * m * 2)] = Item(A, i, k, m);

            for (int k = 0; k < m; k++)
                values[k + m + 2 + (j * m * 2)] = Item(B, k, j, n);
        }
        pthread_create(&threads[i], NULL, matmult_v2_subroutine, (void *)values);
    }

    for (int i = 0; i < l; i++)
    {
        void *result;
        pthread_join(threads[i], &result);
        int *res = (int *)result;
        for (int j = 0; j < n; j++)
        {
            Item(C, i, j, n) = res[j];
        }
        free(result);
    }
}
/*
This code is a subroutine for the pthread_create() function. It takes in an argument that is a pointer to an array of integers. The first two values of the array are the row and column dimensions for the matrix. The next m values are the first row of the matrix. The next m values are the second row of the matrix, and so on. The code creates a new array of integers, and then calculates the dot product of each row of the matrix with the next row, and stores the result in the new array. The code then returns a pointer to the new array.
*/

void *matmult_v2_subroutine(void *arg)
{
    int *values = (int *)arg;
    int sum = 0;
    int i = 0, j = 0;
    int m = values[0];
    int n = values[1];
    int *p = (int *)malloc(sizeof(int) * n);
    for (int i = 0; i < n; i++)
    {
        for (j = 2; j <= m + 1; j++)
        {
            sum += values[j + (2 * i * m)] * values[j + m + (2 * i * m)];
        }
        p[i] = sum;
        sum = 0;
    }
    pthread_exit(p);
}
// ___________________________________________________________________________________________
// END OF CODE