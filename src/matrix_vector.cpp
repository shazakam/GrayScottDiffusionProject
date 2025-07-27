#include "matrix_vector.hpp"
//TODO: Comment and document this - Make sure everything is written to appropriate solutions

// Both of these constructor functions use initialiser lists so there is nothing in the constructor body
Matrix::Matrix(std::vector<double> aa_, std::vector<int> ii_, std::vector<int> jj_, int n_, int ibeg_, int iend_) 
    : aa(aa_), ii(ii_), jj(jj_), n(n_), ibeg(ibeg_), iend(iend_)
    {

    }

Vector::Vector(std::vector<double> xx_, int n_, int ibeg_, int iend_)
    : xx(xx_), n(n_), ibeg(ibeg_), iend(iend_)
    {

    }

// &x is memory reference to vector to be updated, &rx is memory reference to vector to add with x, tau is a constant, ibeg and iend are start and end indices
// Fourth argument refers to where in memory the iterating updates should be changed
void add_scaled_slice(std::vector<double> &a, std::vector<double> &b, std::vector<double> &c, double tau, int ibeg, int iend) {
    auto a_start = a.begin() + ibeg;
    auto a_end = a.begin() + iend + 1;  // +1 because end iterator is exclusive
    auto b_start = b.begin() + ibeg;
    auto c_start = c.begin() + ibeg;

    std::transform(a_start, a_end, b_start, c_start,
                   [tau](double a_val, double b_val) { return a_val + tau * b_val; });
}


void element_wise_vector_mult(std::vector<double> &a, std::vector<double> &b, std::vector<double> &c, int ibeg, int iend){
    auto a_start = a.begin() + ibeg;
    auto a_end = a.begin() + iend;
    auto b_start = b.begin() + ibeg;
    auto c_start = c.begin() + ibeg;
    std::transform(a_start, a_end, b_start, c_start, [](double a_val, double b_val){return a_val*b_val;});
}

void add_constant_to_vector(std::vector<double> &a, double b, std::vector<double> &c, int ibeg, int iend){
    auto a_start = a.begin() + ibeg;
    auto a_end = a.begin() + iend;
    auto c_start = c.begin() + ibeg;

    std::transform(a_start, a_end, c_start, [b](double a_val){return b+a_val;});
}

void mat_mult(Matrix A, double alpha, std::vector<double> &u, std::vector<double> &b, int ibeg, int iend){
    double Aurow;
    int i, i_j, j;
    
    for (i = ibeg; i <= iend; i++){
        Aurow = 0.0;
        b[i] = 0.0;

        for(i_j = A.ii[i-ibeg+1]; i_j <= A.ii[i-ibeg+2]-1; i_j++){
            j = A.jj[i_j];
            Aurow = Aurow + A.aa[i_j]*u[j];
        }

        b[i] = b[i] + alpha*Aurow;
    }
};