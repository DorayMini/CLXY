#include <iostream>
#include <thread>
#include <chrono>
#include "Terminal.hpp"

int main(int argc, char *argv[]) {
    Terminal t;

    for(int i = 5; i < 10; i++) {
        t.clear();
        t.printChar('A', i, 5);
        t.flushBuffer();
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
    getchar();

    return 0;
}