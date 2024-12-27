#pragma once

#include <iostream>
#include <optional>
#include <signal.h>
#include <string>
#include <unistd.h>
#include <memory>

#ifdef __unix__
#include <sys/ioctl.h>
#endif

#include "AnsiColor.hpp"

/*
  TODO:
  - Add support for Windows terminals.

  #ifdef _WIN32
    #include <windows.h>
  #endif
*/

/*
  TODO:

*/
class Terminal{
 public:
   Terminal();
   ~Terminal();

   void flushBuffer();
   void printChar(char c, int x, int y, AnsiColor::Color color);
   void printChar(char c, int x, int y, uint8_t r, uint8_t g, uint8_t b);
   void printChar(char c, int x, int y, uint8_t esc);
   void printString(const std::string& str, int x, int y, AnsiColor::Color color = AnsiColor::Color::White);
   void printString(const std::string& str, int x, int y, uint8_t esc);
   void printString(const std::string& str, int x, int y, uint8_t r, uint8_t g, uint8_t b);
   void moveCursor(int x, int y);
   std::optional<std::pair<int, int>> getTerminalSize();
   void clear();

 private:
   class TerminalSignalHandler{
    public:
      TerminalSignalHandler(Terminal& terminal);
      ~TerminalSignalHandler();
      static void signalHandler(int signal);
      void handleSIGWINCH(int /*signal*/);
    private:
      Terminal& terminal;
      static TerminalSignalHandler* instance;
   };
 
    int rows, cols;
    std::unique_ptr<char[]> buffer;
    std::unique_ptr<uint32_t[]> attributeBuffer;
    TerminalSignalHandler signalHandler;
 private:
    void initializeBuffer();
    void clearBuffer();
    void clearDisplay();
};