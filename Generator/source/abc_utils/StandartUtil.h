#ifndef STANDART_UTIL_H
#define STANDART_UTIL_H

#include <string>
#include <vector>

// so, this struct is used for sending info about multi-line commands
// for abc, yosys etc
struct StandartCommandInfo {
    // длина команды
    int sumLen;
    // информация о том, какая команда вызвала ошибку
    std::string info;
    // слово, которое надо найти, которое будет означать некорректность выполнения
    std::string incorrectWord;
};

class StandartUtil {
    public:
        // parser, which gets info about elements in command
        static std::vector<StandartCommandInfo> parseCommand(
            std::string i_command,
            bool i_parseAll = false
        );
    
    protected:
        static void standartExecutor(
            std::string i_command,
            std::vector<StandartCommandInfo> i_info, 
            void (*i_onFinish) (bool) = NULL
        );
        
        // len of "synthes_util*> "
        static int d_utilLen;
        // "synthes_util *" itself
        static std::string d_utilWord;

        // AbcUtils, YosysUtils etc
        static std::string d_className;
};

#endif
