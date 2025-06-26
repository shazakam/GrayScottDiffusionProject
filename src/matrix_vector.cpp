#include "matrix_vector.hpp"

// Both of these constructor functions use initialiser lists so there is nothing in the constructor body

Matrix::Matrix(std::vector<double> aa_, std::vector<int> ii_, std::vector<int> jj_, int n_, int ibeg_, int iend_) 
    : aa(aa_), ii(ii_), jj(jj_), n(n_), ibeg(ibeg_), iend(iend_)
    {

    }

Vector::Vector(std::vector<double> xx_, int n_, int ibeg_, int iend_)
    : xx(xx_), n(n_), ibeg(ibeg_), iend(iend_)
    {

    }

