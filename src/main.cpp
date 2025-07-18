#include "matrix_vector.hpp"
#include <cmath>
#include "create_matrix.hpp"
#include "initial.hpp"
#include "mpi.h"
#include <fstream>
#include <iostream>
#include <string>

void printCRSMatrix(Matrix matrix){
    /* Print the matrix in Compressed Row Storage (CRS) format
    for i in range(matrix size)
        row_start = matrix.ii[i]
        row_end = matrix.ii[i+1] - 1

        k = row_start
        
        for j in range(matrix.size)
            if k <= row_end and matrix.jj[k] == j then
                print matrix.aa[k]
                k++
            else
                print 0      
    */ 

    for (int i  = 0; i < matrix.aa.size();i++){
        int row_start = matrix.ii[i];
        int row_end = matrix.ii[i+1] - 1;

        int k = row_start;

        for (int j = 0; j < matrix.aa.size(); j++){
            if (k <= row_end && matrix.jj[k] == j){
                std::cout << matrix.aa[k] << " ";
                k = k + 1;
            }
            else{
                std::cout << 0 << " ";
            }
        }
         std::cout << "\n";
    }
}

void printVector(std::vector<double> vec) {
    std::cout << "[ ";
    for (double val : vec) {
        std::cout << val << " ";
    }
    std::cout << "]\n";
}


int main(int argc, char** argv){
    int m, n; // m is problem size and n is 2D problem size
    double tau, T, F, k, Du, Dv;
    int myid, numprocs, nrows, ibeg, iend, rows_per_process; // Processor ID and total number of processors


    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &myid);
    MPI_Comm_size(MPI_COMM_WORLD, &numprocs);

    // Read input data file

    if (myid == 0){    
        
        std::string mytext;
        std::ifstream file("../input.txt");
        file >> m >> tau >> T >> F >> k >> Du >> Dv;
        file.close();

        //while(std::getline(file, mytext)){
    //    std::cout << mytext << '\n';
    // }

    }

    MPI_Bcast(&m, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(&tau, 1, MPI_DOUBLE_PRECISION, 0, MPI_COMM_WORLD);
    MPI_Bcast(&T, 1, MPI_DOUBLE_PRECISION, 0, MPI_COMM_WORLD);
    MPI_Bcast(&F, 1, MPI_DOUBLE_PRECISION, 0, MPI_COMM_WORLD);
    MPI_Bcast(&k, 1, MPI_DOUBLE_PRECISION, 0, MPI_COMM_WORLD);
    MPI_Bcast(&Du, 1, MPI_DOUBLE_PRECISION, 0, MPI_COMM_WORLD);
    MPI_Bcast(&Dv, 1, MPI_DOUBLE_PRECISION, 0, MPI_COMM_WORLD);

    n = m*m;
    rows_per_process = n / numprocs;
    ibeg = myid*rows_per_process + 1;
    iend = (myid +1)*rows_per_process;
    nrows = iend - ibeg + 1;
    
    std::vector<double> aa(5*rows_per_process); // nnz values in matrix
    std::vector<int> ii(rows_per_process+1); // Column startindices
    std::vector<int> jj(5*rows_per_process); // Row start index



    // Adjust the arguments below to match the actual Matrix constructor signature
    Matrix Delta(aa, ii, jj, n, ibeg, iend);

    Delta = createMatrix(m, Delta);

    // TODO: Output vector and matrix to file for debugging
    printVector(Delta.aa);

    // TODO: Initialize vectors u and v and test output

    // TODO: Finish timestepping script

    // TODO: Write solution to gif / video file

    return 0;
}
