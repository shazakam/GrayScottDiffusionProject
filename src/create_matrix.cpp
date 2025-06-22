#include <vector>
#include <cmath>
#include "matrix_vector.hpp"
#include <mpi.h>
#include "create_matrix.hpp"

Matrix createMatrix(int m, Matrix Delta){

    // Loop counters: total, horizontal, vertical, nonzeros, neighbour
    int irow, i, j,  inz, next;

    // Total problem size
    int n;

    // processor rank, num processors, ierr for MPI, rows responsible per processor, start row and end row for processor
    int myid, numprocs, ierr, rows_per_process, start_row, end_row;


    MPI_Comm_rank(MPI_COMM_WORLD, &myid);
    MPI_Comm_size(MPI_COMM_WORLD, &numprocs);

    n = m*m;
    rows_per_process = n / numprocs;

    start_row = myid*rows_per_process + 1;
    end_row = (myid+1)*rows_per_process;

    inz = 1;

    for (int irow = start_row; irow <= end_row; irow++){
        // Cartesian index splitting
        j = (irow-1)/m + 1;
        i + irow - (j-1)*m;

        Delta.ii[irow-start_row+1] = inz;

        Delta.aa[inz] = -4.0 * pow(m,2);
        Delta.jj[inz] = irow;

        inz = inz + 1;

        Delta.aa[inz] = pow(m,2);
        next = i-1;
        if (next < 1) {
            next = m;
        }
        Delta.jj[inz] = next + (j-1)*m;

        inz = inz + 1;

        Delta.aa[inz] = pow(m, 2);
        next = i+1;
        if(next > m){
            next = 1;
        }
        Delta.jj[inz] = next + (j-1)*m;
        inz = inz + 1;

        Delta.aa[inz] = pow(m, 2);
        next = j-1;
        if(next < 1){
            next = m;
        }
        inz = inz + 1;

        Delta.aa[inz] = pow(m,2);
        next = j+1;
        if(next > m){
            next = 1;
        }
        inz = inz + 1;
    }

    Delta.ii[rows_per_process+1] = inz;
    Delta.nnz = inz-1;

    return Delta;
};