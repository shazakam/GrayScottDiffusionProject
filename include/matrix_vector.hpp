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

// &a is memory reference to vector 1, &b is memory reference to vector 2 to add with a, c is reference to output iterator, tau is a constant, ibeg and iend are start and end indices
// Fourth argument refers to where in memory the iterating updates should be changed
void add_scaled_slice(std::vector<double> &a, std::vector<double> &b, std::vector<double> &c, double tau, int ibeg, int iend);

void element_wise_vector_mult(std::vector<double> &a, std::vector<double> &b, std::vector<double> &c, int ibeg, int iend);

void add_constant_to_vector(std::vector<double> &a, double adding_constant, std::vector<double> &c, int ibeg, int iend);

void mat_mult(Matrix A, double alpha, std::vector<double> &u, std::vector<double> &b);
#endif 
