#include "Terminal.hpp"

Terminal::Terminal(){
    if(getTerminalSize())
        buffer = new char[rows*cols];
}

Terminal::~Terminal(){
    delete[] buffer;
}

void Terminal::flushBuffer(){
    std::cout << "\033[2J\033[H";
    for(int i = 0; i < rows*cols; ++i){
        char c = buffer[i];
        int x = i / rows;
        int y = i % rows;
        moveCursor(x, y);
        std::cout << c;
    }
}
bool Terminal::getTerminalSize(){
    struct winsize w;
    if(ioctl(STDOUT_FILENO, TIOCGWINSZ, &w) == 0){
        rows = w.ws_row;
        cols = w.ws_col;
        std::cout << rows << ";" << cols << std::endl;
        return true;
    }
    return false;
}

void Terminal::moveCursor(int x, int y){
    std::cout << "\033[" << y << ";" << x << "H";
}

void Terminal::printChar(char c, int x, int y){
    if(x >= 0 && x <= cols && y >= 0 && y <= rows)
        buffer[y*cols + x] = c;
}

void Terminal::clear(){
    clearBuffer();
    std::cout << "\033[2J\033[H";
}

void Terminal::clearBuffer(){
    for(int i = 0; i < rows*cols; i++)
        buffer[i] = ' ';
}