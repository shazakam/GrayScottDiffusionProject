#ifndef MATRIX_VECTOR
#define MATRIX_VECTOR
#include <vector>

class Matrix {
    public:
        Matrix(std::vector<double> aa, std::vector<int> ii, std::vector<int> jj, int n, int ibeg, int iend);
        std::vector<double> aa; // Non-zero values in matrix
        std::vector<int> ii; // Column indices of non-zero values
        std::vector<int> jj; // Row indices of non-zero values
        int n, ibeg, iend;
};

class Vector{

    public:
        Vector(std::vector<double> xx, int n, int ibeg, int iend);
        // Class containing vector info
        std::vector<double> xx; // Data in vector
        int n; // Total size
        int ibeg, iend; // Portion of vector processor x is responsible for
};

#endif 
