#include <iostream>
#include <cmath>
#include "Terminal.hpp"

int main(int argc, char *argv[]) {
    Terminal t;
    t.clear();
    t.printString("Kutsovol", 10, 10, 255, 0, 0);
    t.flushBuffer();

    return 0;
}

