#ifndef TERMINAL_HPP
#define TERMINAL_HPP

#include <iostream>
#include <sys/ioctl.h>
#include <unistd.h>

class Terminal{
 public:
    Terminal();
    ~Terminal();

    void flushBuffer();
    bool getTerminalSize();
    void moveCursor(int x, int y);
    void printChar(char c, int x, int y);
    void clear();

 private:
    int rows, cols;
    char* buffer;
 private:
    void clearBuffer();
    void clearDisplay();
};
#endif // TERMINAL_HPP