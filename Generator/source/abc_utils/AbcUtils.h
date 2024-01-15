#ifndef ABC_UTILS_H
#define ABC_UTILS_H

#include <string>
#include <thread>
#include <vector>
#include <functional>

#include "StandartUtil.h"

/*
This class is made for basic work with abc.
Using it, it is possible to read verlog file,
read aiger file, make strash and to write file into
verilog or aiger
*/

class AbcUtils : public StandartUtil {
    public:
        static const std::string defaultLibPath;

        static std::thread verilogToAiger(
            const std::string &i_inputFileName, 
            const std::string &i_outputFileName,
            void (*i_onFinish) (CommandWorkResult) = NULL
        );
        static std::thread verilogToAiger(
            const std::string &i_inputFileName, 
            const std::string &i_outputFileName, 
            std::string i_directory,
            void (*i_onFinish) (CommandWorkResult) = NULL
        );

        static std::thread aigerToVerilog(
            const std::string &i_inputFileName, 
            const std::string &i_outputFileName,
            void (*i_onFinish) (CommandWorkResult) = NULL
        );
        static std::thread aigerToVerilog(
            const std::string &i_inputFileName, 
            const std::string &i_outputFileName, 
            std::string i_directory,
            void (*i_onFinish) (CommandWorkResult) = NULL
        );

        static std::thread balanceVerilog(
            const std::string &i_inputFileName,
            void (*i_onFinish) (CommandWorkResult) = NULL
        );
        static std::thread balanceVerilog(
            const std::string &i_inputFileName, 
            std::string i_directoryv,
            void (*i_onFinish) (CommandWorkResult) = NULL
        );

        static std::thread balanceAiger(
            const std::string &i_inputFileName,
            void (*i_onFinish) (CommandWorkResult) = NULL
        );
        static std::thread balanceAiger(
            const std::string &i_inputFileName, 
            std::string i_directory,
            void (*i_onFinish) (CommandWorkResult) = NULL
        );

        static std::thread getStats(
            const std::string &i_inputFileName,
            const std::string &i_libName,
            const std::function<void(CommandWorkResult)> &i_onFinish = NULL
        );

        static std::thread getStats(
            const std::string &i_inputFileName, 
            const std::string &i_libName,
            std::string i_fileDirectory,
            std::string i_libDirectory,
            const std::function<void(CommandWorkResult)> &i_onFinish = NULL
        );

        static std::thread optimizeWithLib(
            const std::string &i_inputFileName, 
            const std::string &i_outputFileName, 
            const std::string &i_libName,
            void (*i_onFinish) (CommandWorkResult) = NULL
        );

        static std::thread optimizeWithLib(
            const std::string &i_inputFileName, 
            const std::string &i_outputFileName, 
            const std::string &i_libName,
            std::string i_fileDirectory,
            std::string i_libDirectory,
            void (*i_onFinish) (CommandWorkResult) = NULL
        );

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

        static std::vector<std::string> d_allowedOutput;
        static std::vector<std::string> d_incorrectWords;
    
    private:
        static void runExecutorForStats(
            const std::string &i_command,
            const std::vector<StandartCommandInfo> &i_info, 
            const std::function<void(CommandWorkResult)> &i_onFinish
        );

};

#endif
