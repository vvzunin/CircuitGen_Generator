#ifndef STANDART_UTIL_H
#define STANDART_UTIL_H

#include <string>
#include <map>

// so, this struct is used for sending info about multi-line commands
// for abc, yosys etc
struct StandartCommandInfo {
    // длина команды
    int sumLen;
    // информация о том, какая команда вызвала ошибку
    std::string info;
};

// result of work
struct CommandWorkResult {
    bool correct;
    std::map<std::string, std::string> commandsOutput; 
};

#endif
