#ifndef TEST1_H_
#define TEST1_H_

#include <iostream>
#include <cmath>
#include "dllmain.h"

class Test1 : public Base {
public:
    void print(void) {
        std::cout << "Hello Everybody! Test1!" << std::endl;
    }

    double calc(double val) {
        return sqrt(abs(val / 5 * 1.61));
    }
};

#endif