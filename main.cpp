#include <iostream>
#include <cmath>
#include "Terminal.hpp"

int main(int argc, char *argv[]) {
    Terminal t;
    
    t.printChar('d', 10, 10, 105);
    t.printString("Hello, World!", 5, 5, AnsiColor::Color::Green);
    t.flushBuffer();
    return 0;
}

