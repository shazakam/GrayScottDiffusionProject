#ifndef RHS
#define RHS

#include <matrix_vector.hpp>
#include <vector>


void rhs(Vector u, Vector v, double F, double k, double Du, double Dv, Matrix &Delta, std::vector<double> &ru, std::vector<double> &rv);

#endif