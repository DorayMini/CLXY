#include "AnsiColor.hpp"
#include <algorithm>

template<>
bool isAnsiSupported<AnsiColor>::is256Supported = false;

template<>
bool isAnsiSupported<AnsiColor>::isTCSupported = false;

AnsiColor::AnsiColor(Color& color){
    colorCode = makeColorCode(static_cast<uint32_t>(color), 0, 0);
    colorCodeString = makeColorCodeString(colorCode);
}

AnsiColor::AnsiColor(uint8_t r, uint8_t g, uint8_t b){
    uint32_t color = ((r << 16) | (g << 8) | (b << 0));
    colorCode = makeColorCode(color, 2, 0);
    colorCodeString = makeColorCodeString(colorCode);
}

std::string AnsiColor::getColorCodeString() const{
    return colorCodeString;
}

int32_t AnsiColor::getColorCode() const{
    return colorCode;
}

void AnsiColor::decomposeColor(uint32_t color, uint8_t& r, uint8_t& g, uint8_t& b){
    r = (color >> 16) & 0xFF;
    g = (color >> 8) & 0xFF;
    b = color & 0xFF;
}

uint32_t AnsiColor::makeColorCode(uint32_t color, uint8_t type, uint8_t style){
    return ((color & 0xFFFFFF) << 8) | ((type & 0x3) << 6) | (style & 0x3F);
}

std::string AnsiColor::makeColorCodeString(uint32_t colorCode){
    uint8_t type = (colorCode >> 6) & 0x3;
    uint32_t color = (colorCode >> 8) & 0xFFFFFF;
    if(type == static_cast<uint8_t>(ColorType::ANSI16)){
        return std::format("\033[{}m", (color));
    } else if(type == static_cast<uint8_t>(ColorType::ANSI256)) {
        if(isAnsiSupported<AnsiColor>::is256Supported)
            return std::format("\033[38;5;{}m", color);
    } else if(type == static_cast<uint8_t>(ColorType::RGB)) {
        if(isAnsiSupported<AnsiColor>::isTCSupported){
            //std::cout << "R: " << ((color >> 16) & 0xFF) << " G: " << ((color >> 8) & 0xFF) << " B: " << ((color >> 0) & 0xFF);
            return std::format("\033[38;2;{};{};{}m", (color >> 16) & 0xFF, (color >> 8) & 0xFF, color & 0xFF);

        }
    }
    return "<Fail>";
}

template <>
isAnsiSupported<AnsiColor>::isAnsiSupported(){
    const char* term = std::getenv("TERM");
    if(term){
        size_t pos = std::string(term).find("256color");
        if(pos != std::string::npos)
            is256Supported = true;
    }
    const char* colorTerm = std::getenv("COLORTERM");
    if(colorTerm){
        size_t pos = std::string(colorTerm).find("truecolor");
        if(pos != std::string::npos)
            isTCSupported = true;
    }
}


isAnsiSupported<AnsiColor> AnsiColor::initializer;