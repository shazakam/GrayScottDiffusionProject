#include "matrix_vector.hpp"
#include <cmath>
#include "create_matrix.hpp"
#include "initial.hpp"
#include "mpi.h"
#include <fstream>
#include <iostream>
#include <string>
#include <rhs.hpp>
// // &x is memory reference to vector to be updated, &rx is memory reference to vector to add with x, tau is a constant, ibeg and iend are start and end indices
// // Fourth argument refers to where in memory the iterating updates should be changed
// void add_scaled_slice(std::vector<double>& x, std::vector<double>& rx, double tau, int ibeg, int iend) {
//     auto x_start = x.begin() + ibeg;
//     auto x_end = x.begin() + iend + 1;  // +1 because end iterator is exclusive
//     auto rx_start = rx.begin() + ibeg;

//     std::transform(x_start, x_end, rx_start, x_start,
//                    [tau](double x_val, double rx_val) { return x_val + tau * rx_val; });
// }


void timeStepping(Vector u, Vector v, double tau, double T, double F, double k, double Du, double Dv, Matrix Delta){
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