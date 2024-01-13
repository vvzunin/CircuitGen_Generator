#ifndef STANDART_UTIL_H
#define STANDART_UTIL_H

#include <string>
#include <vector>
#include <map>

// so, this struct is used for sending info about multi-line commands
// for abc, yosys etc
struct StandartCommandInfo {
    // длина команды
    int sumLen;
    // информация о том, какая команда вызвала ошибку
    std::string info;
    // слова, которые надо найти, которые будет означать некорректность выполнения
    std::vector<std::string> incorrectWords;
};

// result of work
struct CommandWorkResult {
    bool correct;
    std::map<std::string, std::string> commandsOutput; 
};

class StandartUtil {
    public:
        // parser, which gets info about elements in command
        static std::vector<StandartCommandInfo> parseCommand(
            std::string i_command,
            bool i_parseAll = true
        );
    
    protected:
        static void standartExecutor(
            std::string i_command,
            std::vector<StandartCommandInfo> i_info, 
            void (*i_onFinish) (CommandWorkResult) = NULL
        );
        
        // len of "synthes_util*> "
        static int d_utilLen;
        // "synthes_util *" itself
        static std::string d_utilWord;

        // AbcUtils, YosysUtils etc
        static std::string d_className;

        static std::vector<std::string> d_allowedOutput;
};

#endif
