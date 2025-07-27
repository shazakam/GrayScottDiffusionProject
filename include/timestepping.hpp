#ifndef TIMESTEPPING
#define TIMESTEPPING
#include <matrix_vector.hpp>
#include <vector>
#endif

void timeStepping(Vector &u, Vector &v, double tau, double T, double F, double k, double Du, double Dv);