#include "initial.hpp"
#include <cmath>
#include <vector>
#include "mpi.h"
#include "matrix_vector.hpp"

void initial(int m, Vector& u, Vector& v){
    double x, y, h, v2;
    int irow, i, j;
    int myid, numprocs, ierr, rows_per_process, start_row, end_row;
    
    MPI_Comm_rank(MPI_COMM_WORLD, &myid);
    MPI_Comm_size(MPI_COMM_WORLD, &numprocs);

    rows_per_process = (m*m) / numprocs;
    start_row = myid*rows_per_process;
    end_row = (myid+1)*rows_per_process - 1;
    h = 1.0 / m;
    v2 = 0.02;

    for(irow = start_row; irow <= end_row; irow++){
        j = irow / m;
        i = irow % m;
        y = (j + 1) * h;
        x = (i + 1) * h;

        u.xx[irow] = 1.0 - 0.5*exp(-pow(x-0.5,2)/v2 - pow(y-0.5, 2)/v2)- 0.5*exp(-pow(x-0.4,2)/v2 - pow(y-0.6, 2)/v2);

        v.xx[irow] = 0.25*exp(-pow(x-0.4,2)/v2 - pow(y-0.4, 2)/v2) + 0.25*exp(-pow(x-0.5,2)/v2 - pow(y-0.6, 2)/v2);
    };
}