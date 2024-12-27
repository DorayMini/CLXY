#pragma once

#include <iostream>
#include <string>
#include <stdint.h>
#include <stdexcept>
#include <cstdlib>
#include <format>
#include <type_traits>

/*
  TODO:
    - Add support for background colors
    - Add support for font styles (e.g., italic, bold, underline)
*/

template<typename T>
struct isAnsiSupported{
  static bool is256Supported;
  static bool isTCSupported;
  isAnsiSupported();
};

class AnsiColor{
 public:
  enum class Color;

  AnsiColor(Color& color);
  AnsiColor(uint8_t r, uint8_t g, uint8_t b);
  AnsiColor(std::same_as<uint8_t> auto esc){
    colorCode = makeColorCode(esc, 1, 0);
    colorCodeString = makeColorCodeString(colorCode);
  }

  AnsiColor(std::same_as<uint32_t> auto colorCode){
    this->colorCode = colorCode;
    uint32_t color = (colorCode & 0xFFFFFF) >> 8;
    colorCodeString = makeColorCodeString(colorCode);
  }
  
  void decomposeColor(uint32_t color, uint8_t &r, uint8_t &g, uint8_t &b);
  std::string getColorCodeString() const;
  int32_t getColorCode() const;
 public:
  enum class Color{
    Black = 0x1E,
    Red = 0x1F,
    Green = 0x20,
    Yellow = 0x21,
    Blue = 0x22,
    Magenta = 0x23,
    Cyan = 0x24,
    White = 0x25,
    BrightBlack = 0x26,
    BrightRed = 0x27,
    BrightGreen = 0x28,
    BrightYellow = 0x29,
    BrightBlue = 0x0C,
    BrightMagenta = 0x2A,
    BrightCyan = 0x2B,
    BrightWhite = 0x2E
  };
 private:
  static isAnsiSupported<AnsiColor> initializer;
  std::string colorCodeString;
  /*
    color code format:
        24bits - Data(color)
        2bits - ColorType
        6bits - Ansi styles
  */
  uint32_t colorCode;
  uint32_t makeColorCode(uint32_t color, uint8_t type = static_cast<uint8_t>(ColorType::ANSI16), uint8_t style = 0);
  std::string makeColorCodeString(uint32_t colorCode);

  enum class ColorType{
    ANSI16 = 0,
    ANSI256 = 1,
    RGB = 2
  };
};