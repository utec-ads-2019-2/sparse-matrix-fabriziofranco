#include <iostream>

#include "tester/tester.h"

int main() {
    Tester::execute();
/*    Matrix<int> matrix(3,2);
    matrix.set(0,0,1);matrix.set(0,1,-1);
    matrix.set(1,0,-2);matrix.set(1,1,0);
    matrix.set(2,0,3);matrix.set(2,1,2);
    matrix.print();
    matrix=matrix.transpose();
    auto matrix2=matrix.transpose().transpose();
    auto matrix3=matrix.operator*(matrix2);
    matrix3.print();*/

    return EXIT_SUCCESS;
}

