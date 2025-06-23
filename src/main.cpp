#include "matrix_vector.hpp"
#include <cmath>
#include "create_matrix.hpp"
#include "initial.hpp"
#include "mpi.h"
#include <fstream>
#include <iostream>
#include <string>

int main(){
    std::string mytext;
    std::ifstream file("../input.txt");

    while(std::getline(file, mytext)){
        std::cout << mytext << '\n';
    }

    file.close();
    return 0;
}
