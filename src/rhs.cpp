#include "matrix_vector.hpp"

void RHS(Vector &u, Vector &v, double F, double k, double Du, double Dv, Matrix &Delta, std::vector<double> &ru, std::vector<double> &rv){

    std::vector<double> u_v_v(u.n);

    // define in matrix_vector file
    mat_mult(Delta, Du, u.xx, ru);
    mat_mult(Delta, Dv, v.xx, rv);

    // Calculating u*v*v
    element_wise_vector_mult(u.xx, v.xx, u_v_v, u.ibeg, u.iend);
    element_wise_vector_mult(u_v_v, v.xx, u_v_v, u.ibeg, u.iend);

    // ru update
    add_scaled_slice(ru, u.xx, ru, -F, u.ibeg, u.iend);
    add_constant_to_vector(ru, F, ru, u.ibeg, u.iend);
    add_scaled_slice(ru, u_v_v, ru, -1.0, u.ibeg, u.iend);

    // rv update
    add_scaled_slice(rv, v.xx, rv, -(F+k), v.ibeg, v.iend);
    add_scaled_slice(rv, u_v_v, rv, 1.0, v.ibeg, v.iend);
}