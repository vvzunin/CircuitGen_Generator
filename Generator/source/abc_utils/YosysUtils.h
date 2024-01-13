#ifndef YOSYS_UTILS_H
#define YOSYS_UTILS_H

#include <string>
#include <thread>
#include <vector>
#include <functional>

#include "StandartUtil.h"

/*
This class is made for basic work with yosys.
Using it, it is possible to read verlog file,
make opt and to write file into verilog
*/


class YosysUtils : public StandartUtil {
    public:
        static std::thread optVerilog(
            const std::string &i_inputFileName,
            const std::string &i_outputFileName,
            void (*i_onFinish) (CommandWorkResult) = NULL
        );
        static std::thread optVerilog(
            const std::string &i_inputFileName,
            const std::string &i_outputFileName, 
            std::string i_directory,
            void (*i_onFinish) (CommandWorkResult) = NULL
        );

        // IMPORTANT parseAll here is TRUE
        static std::vector<StandartCommandInfo> parseCommand(
            std::string i_command
        );
    protected:
        static void standartExecutor(
            const std::string &i_command,
            const std::vector<StandartCommandInfo> &i_info, 
            const std::function<void(CommandWorkResult)> &i_onFinish = NULL
        );

        // len of "synthes_util*> "
        static int d_utilLen;
        // "synthes_util *" itself
        static std::string d_utilWord;

        // AbcUtils, YosysUtils etc
        static std::string d_className;

        static std::vector<std::string> d_incorrectWords;
};

#endif
