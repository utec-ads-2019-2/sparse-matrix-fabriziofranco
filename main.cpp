#include <iostream>

#include "tester/tester.h"

int main() {
    Tester::execute();
    Matrix<int> matrix(4,3);
    matrix.set(0,0,1);matrix.set(0,1,2);matrix.set(0,2,3);
    matrix.set(1,0,4);matrix.set(1,1,5);matrix.set(1,2,6);
    matrix.set(2,0,7);matrix.set(2,1,8);matrix.set(2,2,9);
    matrix.set(3,0,0);matrix.set(3,1,0);matrix.set(3,2,0);

    matrix.print();
    return EXIT_SUCCESS;
}

