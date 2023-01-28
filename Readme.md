# Matrix multipication using Posix threads :chains:

This Project is used to illustrate the performance and benefits of using threading programming. :smiley:

## Explaination 📖

#### How are matricies are multiplied

Matrix multiplication is a binary operation that takes a pair of matrices, and produces another matrix. In a single thread, the operation is performed by taking the dot product of each row of the first matrix with each column of the second matrix, and summing the results. The result is then placed in the corresponding position in the resulting matrix.

For example, if we have two matrices A and B, where A is a 2x2 matrix and B is a 2x2 matrix, the resulting matrix C would be a 2x2 matrix. Each element in C, c(i,j), would be the dot product of the i-th row of A and the j-th column of B.

<p align="center" width="100%">
<img src="https://i1.faceprep.in/Companies-1/matrix-multiplication-in-python.png" width="600" height="400">
</p>

### Single Process Solution

If a single process is used to perform matrix multiplication, the
process will sequentially perform the multiplication and addition
operations required to compute each element of the resulting
matrix.

### Thread per element Solution

A "thread per element" matrix multiplication approach would involve creating a separate thread for each element in the resulting matrix. Each thread would be responsible for computing the value of a single element in the resulting matrix by multiplying the corresponding row and column elements from the input matrices.

<div style=text-align:center>
<img src="https://www.researchgate.net/profile/J-Haeuser/publication/273445689/figure/fig1/AS:648611121623049@1531652350506/The-multi-threaded-matrix-multiplication-is-performed-by-splitting-matrix-C-into.png" style="clip-path: inset(10% 11% 0% 15%);">
</div>

It's important to note that while this approach can greatly improve the performance of matrix multiplication when the matrices are large, it can also be memory intensive, as each thread requires its own stack and may also require additional memory for storing intermediate results. Additionally, creating and managing a large number of threads can also have a significant overhead, which can offset the performance benefits of parallelization.

**Overall, thread per element approach is not a common approach, and it's not always the best option for matrix multiplication, as it depends on the size of matrices, the number of cores on the machine and other factors.**

### Thread per row solution

A "thread per row" matrix multiplication approach would involve creating a separate thread for each row in the resulting matrix. Each thread would be responsible for computing the values of all the elements in a specific row of the resulting matrix by multiplying the corresponding row from the first matrix with the entire column of the second matrix.

**Overall, the thread per row approach is a common approach for matrix multiplication, which can be useful for large matrices and can achieve good performance. However, it's not always the best option, as the performance benefits can depend on the size of matrices, the number of cores on the machine and other factors.**

## Table of contents :label:

| File Name | Description                                                                                      |
|-----------|--------------------------------------------------------------------------------------------------|
| [main.c](https://github.com/XMaroRadoX/Matrix-Multipication-using-posix-threads/blob/master/main.c)   | Test and compare the performance of the different versions of the matrix multiplication function |
| [matmult.c](https://github.com/XMaroRadoX/Matrix-Multipication-using-posix-threads/blob/master/matmult.c) | Contains the implementation using : 1 process , Thread per element , Thread per row              |
| [Makefile](https://github.com/XMaroRadoX/Matrix-Multipication-using-posix-threads/blob/master/Makefile)  | Used to run the program                                                                          |

### Pre-requisites :screwdriver:

* Linux : Ubuntu or any debian based distro
* C Compiler
* make

#### Install pre-requisites :toolbox:

Have to be on debian-based distro that have apt as it's package manager to run these commands

```sh
sudo apt update && sudo apt install gcc make

```

### Run :green_circle:

* Navigate to directory
* Run Make

`make`

### Licensing :pencil:

This code is licensed under the MIT License.

### Authors :pen:

* Marwan Khaled

### Contribution :clinking_glasses:

* Images are courtesy of [geeksforgeeks](https://www.geeksforgeeks.org/),[faceprep](https://faceprep.in),[resarchgate](https://resarchgate.net)

[![License](https://img.shields.io/badge/License-MIT-red.svg)](https://opensource.org/licenses/MIT)
