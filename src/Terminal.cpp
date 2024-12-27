#include "Terminal.hpp"

Terminal::Terminal() : signalHandler(*this){
    clearDisplay();
    auto size = getTerminalSize();
    if(size){
        rows = size->first;
        cols = size->second;
    }
    initializeBuffer();
}

Terminal::~Terminal(){
}

void Terminal::flushBuffer(){
    clearDisplay();
    moveCursor(0, 0);
    for(int y = 0; y < rows; ++y){
        for(int x = 0; x < cols; ++x){
            char c = buffer[y*cols + x];
            uint32_t colorCode = attributeBuffer[y*cols + x];
            moveCursor(x+1, y+1);
            if (colorCode)
                std::cout << AnsiColor(colorCode).getColorCodeString() << c << "\033[0m";
            //std::cout << colorCode << std::endl;
        }
    }
    std::cout << std::flush;
}
std::optional<std::pair<int, int>> Terminal::getTerminalSize(){
    struct winsize w;
    if(ioctl(STDOUT_FILENO, TIOCGWINSZ, &w) == 0){
        return std::pair<int, int>(w.ws_col, w.ws_row);
    }
    return std::nullopt;
}

void Terminal::moveCursor(int x, int y){
    std::cout << "\033[" << y << ";" << x << "H";
}

void Terminal::printChar(char c, int x, int y, AnsiColor::Color color){
    if(x > 0 && x <= cols && y > 0 && y <= rows){
        buffer[y*cols + x] = c;
        attributeBuffer[y*cols + x] = AnsiColor(color).getColorCode();
        //std::cout << "Color: " << attributeBuffer[y*cols+x] << std::endl;
        //std::cout << std::bitset<32>(AnsiColor(color).getColorCode());
    }
}
void Terminal::printChar(char c, int x, int y, uint8_t r, uint8_t g, uint8_t b){
    if(x > 0 && x <= cols && y > 0 && y <= rows){
        buffer[y*cols + x] = c;
        attributeBuffer[y*cols + x] = AnsiColor(r, g, b).getColorCode();
        //std::cout << AnsiColor(r, g, b).getColorCode() << std::endl;
    }
}
void Terminal::printChar(char c, int x, int y, uint8_t esc){
    if(x > 0 && x <= cols && y > 0 && y <= rows){
        buffer[y*cols + x] = c;
        attributeBuffer[y*cols + x] = AnsiColor(esc).getColorCode();
        //std::cout << AnsiColor(esc).getColorCode() << std::endl;
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
    clearDisplay();
    clearBuffer();
}

void Terminal::clearDisplay(){
    std::cout << "\033[2J\033[3J\033[H";
}
void Terminal::clearBuffer(){
    std::fill(buffer.get(), buffer.get() + rows*cols, ' ');
    std::fill(attributeBuffer.get(), attributeBuffer.get() + rows*cols, 0);
}

void Terminal::initializeBuffer(){
    buffer = std::make_unique<char[]>(rows*cols);
    attributeBuffer = std::make_unique<uint32_t[]>(rows*cols);
}