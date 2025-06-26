#include "matrix_vector.hpp"
#include <cmath>
#include "create_matrix.hpp"
#include "initial.hpp"
#include <iostream>
#include <gtest/gtest.h>

void printVector(std::vector<int>& vec) {
    std::cout << "[ ";
    for (int val : vec) {
        std::cout << val << " ";
    }
    std::cout << "]\n";
}

void printMatrix(std::vector<std::vector<int>>& matrix) {
    for (const auto& row : matrix) {
        std::cout << "| ";
        for (int val : row) {
            std::cout << val << " ";
        }
        std::cout << "|\n";
    }
}

TEST(INITIALISATION, TestCreateMatrix){
    
}

