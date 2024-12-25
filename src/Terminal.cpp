#include "Terminal.hpp"

Terminal::Terminal() : signalHandler(*this){
    if(getTerminalSize()){
        buffer = new char[rows*cols];
        colorBuffer = new int8_t[rows*cols];
    }
}

Terminal::~Terminal(){
    delete[] buffer;
    delete[] colorBuffer;
}

void Terminal::flushBuffer(){
    std::cout << "\033[2J\033[H";
    for(int y = 0; y < rows; ++y){
        for(int x = 0; x < cols; ++x){
            char c = buffer[y*cols + x];
            char color = colorBuffer[y*cols + x];
            moveCursor(x+1, y+1);
            std::cout << AnsiColor().getColorCodeString(color) << c;
        }
    }
    std::cout << std::flush;
}
std::optional<std::pair<int, int>> Terminal::getTerminalSize(){
    struct winsize w;
    if(ioctl(STDOUT_FILENO, TIOCGWINSZ, &w) == 0){
        rows = w.ws_row;
        cols = w.ws_col;
        return std::pair<int, int>(cols, rows);
    }
    return std::nullopt;
}

void Terminal::moveCursor(int x, int y){
    std::cout << "\033[" << y << ";" << x << "H";
}

void Terminal::printChar(char c, int x, int y, AnsiColor::Color color){
    if(x > 0 && x <= cols && y > 0 && y <= rows){
        buffer[y*cols + x] = c;
        colorBuffer[y*cols + x] = static_cast<char>(color);
    }
}

void Terminal::printChar(char c, int x, int y, uint8_t r, uint8_t g, uint8_t b){
    AnsiColor color(r, g, b);
    if(x > 0 && x <= cols && y > 0 && y <= rows){
        buffer[y*cols + x] = c;
        colorBuffer[y*cols + x] = color.getColorCode();
    }
}

void Terminal::printString(const std::string& str, int x, int y, AnsiColor::Color color){
    moveCursor(x, y);
    for(auto i: str){
        if(x > cols - 1){
            x = 1;
            ++y;
        }
        printChar(i, x++, y, color);
    }
}

void Terminal::printString(const std::string& str, int x, int y, uint8_t r, uint8_t g, uint8_t b){
    moveCursor(x, y);
    for(auto i: str){
        if(x > rows - 1){
            x = 1;
            ++y;
        }
        printChar(i, x++, y, r, g, b);
    }
}

void Terminal::clear(){
    clearBuffer();
    std::cout << "\033[2J\033[3J\033[H";
}

void Terminal::clearBuffer(){
    for(int i = 0; i < rows*cols; i++)
        buffer[i] = ' ';
}