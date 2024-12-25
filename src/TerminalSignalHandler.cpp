#include "Terminal.hpp"


Terminal::TerminalSignalHandler::TerminalSignalHandler(Terminal& terminal) : terminal(terminal){
    signal(SIGWINCH, signalHandler);
    instance = this;
}

Terminal::TerminalSignalHandler::~TerminalSignalHandler(){
    signal(SIGWINCH, SIG_DFL);
}

void Terminal::TerminalSignalHandler::signalHandler(int signal){
    if(signal == SIGWINCH && instance){
        instance->handleSIGWINCH(signal);
    }
}

void Terminal::TerminalSignalHandler::handleSIGWINCH(int /*signal*/){
    instance->terminal.getTerminalSize();
    std::string str = std::format("{}:{}", instance->terminal.cols, instance->terminal.rows);
    instance->terminal.printString(str, 0, 0, AnsiColor::Color::Yellow);

}

Terminal::TerminalSignalHandler* Terminal::TerminalSignalHandler::instance = nullptr;