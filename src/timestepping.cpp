#include "matrix_vector.hpp"
#include <cmath>
#include "create_matrix.hpp"
#include "initial.hpp"
#include "mpi.h"
#include <fstream>
#include <iostream>
#include <string>
#include <rhs.hpp>

void timeStepping(Vector &u, Vector &v, double tau, double T, double F, double k, double Du, double Dv, Matrix Delta){

    std::vector<double> ru(u.n);
    std::vector<double> rv(v.n);
    std::vector<double> ru_hat(u.n);
    std::vector<double> rv_hat(v.n);

    int num_steps = int(T / tau);

    for(int i = 0; i < num_steps; i++){

        rhs(u, v, F, k, Du, Dv, Delta, ru, rv);

        // Update u and v
        add_scaled_slice(u.xx, ru, u.xx, tau, u.ibeg, u.iend);
        add_scaled_slice(v.xx, rv, v.xx, tau, v.ibeg, v.iend);

        rhs(u, v, F, k, Du, Dv, Delta, ru_hat, rv_hat);

        // Final updates for u and v
        add_scaled_slice(u.xx, ru_hat, u.xx, tau, u.ibeg, u.iend);
        add_scaled_slice(u.xx, ru, u.xx, -0.50, u.ibeg, u.iend);

        add_scaled_slice(v.xx, rv_hat, v.xx, tau, v.ibeg, v.iend);
        add_scaled_slice(v.xx, rv, v.xx, -0.50, v.ibeg, v.iend);   
    };
}