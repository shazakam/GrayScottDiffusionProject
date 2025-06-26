#include "matrix_vector.hpp"
#include <cmath>
#include "create_matrix.hpp"
#include "initial.hpp"
#include "mpi.h"
#include <fstream>
#include <iostream>
#include <string>

void printMatrix(std::vector<std::vector<double>> matrix) {
    for (const auto& row : matrix) {
        std::cout << "| ";
        for (double val : row) {
            std::cout << val << " ";
        }
        std::cout << "|\n";
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
    std::vector<int> ii(rows_per_process+1); // Column indices
    std::vector<int> jj(5*rows_per_process); // Row start index



    // Adjust the arguments below to match the actual Matrix constructor signature
    Matrix Delta(aa, ii, jj, n, ibeg, iend);

    Delta = createMatrix(m, Delta);

    printVector(Delta.aa);

    return 0;
}
