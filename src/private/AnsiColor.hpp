#pragma once

#include <iostream>
#include <string>
#include <stdint.h>
#include <stdexcept>
#include <cstdlib>
#include <format>

template<typename T>
struct isAnsi256Supported{
   static bool isSupported;
   isAnsi256Supported();
};

class AnsiColor{
 public:
   enum class Color;

   AnsiColor() = default;
   AnsiColor(uint8_t r, uint8_t g, uint8_t b);
   AnsiColor(Color& color);
   void setColorCodeString(uint8_t color);

   std::string getColorCodeString() const;
   std::string getColorCodeString(uint8_t color);
   int8_t getColorCode() const;
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
   static isAnsi256Supported<AnsiColor> initializer;
   std::string ansiColorCodeString;
   uint8_t ansiColorCode;
};