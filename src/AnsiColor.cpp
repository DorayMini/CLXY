#include "AnsiColor.hpp"

AnsiColor::AnsiColor(uint8_t r, uint8_t g, uint8_t b){
    r = r / 51;
    g = g / 51;
    b = b / 51;
    int color = (16 + 36 * r + 6 * g + b);
    ansiColorCode = color;
    setColorCodeString(ansiColorCode);
}

AnsiColor::AnsiColor(Color& color){
    ansiColorCode = static_cast<int8_t>(color);
    setColorCodeString(ansiColorCode);
}

void AnsiColor::setColorCodeString(uint8_t color){
    int formattedColor = static_cast<int>(color);
    if(initializer.isSupported)
        ansiColorCodeString = std::format("\033[5;{}m", static_cast<int>(color));
    else
        ansiColorCodeString = std::format("\033[{}m", static_cast<int>(color));
}

std::string AnsiColor::getColorCodeString() const{
    return ansiColorCodeString;
}

std::string AnsiColor::getColorCodeString(uint8_t color){
    ansiColorCode = color;
    setColorCodeString(color);
    return ansiColorCodeString;
}

int8_t AnsiColor::getColorCode() const{
    return ansiColorCode;
}

template<>
bool isAnsi256Supported<AnsiColor>::isSupported = false;

template <>
isAnsi256Supported<AnsiColor>::isAnsi256Supported(){
    const char* term = std::getenv("TERM");
    if(term){
        size_t pos = std::string(term).find("256color");
        if(pos != std::string::npos)
            isSupported = true;
    }
}


isAnsi256Supported<AnsiColor> AnsiColor::initializer;