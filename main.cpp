#include <iostream>

#include "tester/tester.h"

int main() {
    Tester::execute();

    Matrix<int> matrix(5,5);
    matrix.set(0,0,1);matrix.set(0,1,2);matrix.set(0,2,3);matrix.set(0,3,4);matrix.set(0,4,5);
    matrix.set(1,0,6);matrix.set(1,1,7);matrix.set(1,2,8);matrix.set(1,3,9);matrix.set(1,4,10);
    matrix.set(2,0,11);matrix.set(2,1,12);matrix.set(2,2,13);matrix.set(2,3,14);matrix.set(2,4,15);
    matrix.set(3,0,16);matrix.set(3,1,17);matrix.set(3,2,18);matrix.set(3,3,19);matrix.set(3,4,20);
    matrix.set(4,0,21);matrix.set(4,1,22);matrix.set(4,2,23);matrix.set(4,3,24);matrix.set(4,4,25);
    matrix.print();
    cout<<endl;
    cout<<endl;

    matrix.operator*(3);
    matrix.print();


    matrix.print();
    return EXIT_SUCCESS;
}

