#ifndef ABC_UTILS_H
#define ABC_UTILS_H

#include <string>
#include <thread>
#include <vector>

#include "StandartUtil.h"

/*
This class is made for basic work with abc.
Using it, it is possible to read verlog file,
read aiger file, make strash and to write file into
verilog or aiger
*/

class AbcUtils : public StandartUtil {
    public:
        static std::thread verilogToAiger(
            std::string i_inputFileName, 
            std::string i_outputFileName,
            void (*i_onFinish) (CommandWorkResult) = NULL
        );
        static std::thread verilogToAiger(
            std::string i_inputFileName, 
            std::string i_outputFileName, 
            std::string i_directory,
            void (*i_onFinish) (CommandWorkResult) = NULL
        );

        static std::thread aigerToVerilog(
            std::string i_inputFileName, 
            std::string i_outputFileName,
            void (*i_onFinish) (CommandWorkResult) = NULL
        );
        static std::thread aigerToVerilog(
            std::string i_inputFileName, 
            std::string i_outputFileName, 
            std::string i_directory,
            void (*i_onFinish) (CommandWorkResult) = NULL
        );

        static std::thread balanceVerilog(
            std::string i_inputFileName,
            void (*i_onFinish) (CommandWorkResult) = NULL
        );
        static std::thread balanceVerilog(
            std::string i_inputFileName, 
            std::string i_directoryv,
            void (*i_onFinish) (CommandWorkResult) = NULL
        );

        static std::thread balanceAiger(
            std::string i_inputFileName,
            void (*i_onFinish) (CommandWorkResult) = NULL
        );
        static std::thread balanceAiger(
            std::string i_inputFileName, 
            std::string i_directory,
            void (*i_onFinish) (CommandWorkResult) = NULL
        );

        static void runExecutorForStats(
            std::string i_command,
            std::vector<StandartCommandInfo> i_info, 
            void (*i_onFinish) (CommandWorkResult)
        );

        static std::thread optimizeWithLib(
            std::string i_inputFileName, 
            std::string i_outputFileName, 
            std::string i_libName,
            void (*i_onFinish) (CommandWorkResult) = NULL
        );

        static std::thread optimizeWithLib(
            std::string i_inputFileName, 
            std::string i_outputFileName, 
            std::string i_libName,
            std::string i_directory,
            std::string i_libDirectory,
            void (*i_onFinish) (CommandWorkResult) = NULL
        );

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
