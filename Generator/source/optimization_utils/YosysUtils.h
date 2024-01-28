#ifndef YOSYS_UTILS_H
#define YOSYS_UTILS_H

#include <string>
#include <vector>

#include "StandartUtil.h"

/*
This class is made for basic work with yosys.
Using it, it is possible to read verlog file,
make opt and to write file into verilog
*/

class YosysUtils
{
public:
    static CommandWorkResult optVerilog(
        std::string i_inputFileName,
        std::string i_outputFileName,
        std::string i_directory = ".");
    static CommandWorkResult writeFirrtl(
        std::string i_inputFileName,
        std::string i_outputFileName,
        std::string i_directory = ".");

    // IMPORTANT parseAll here is TRUE
    static std::vector<StandartCommandInfo> parseCommand(
        std::string i_command);

protected:
    static CommandWorkResult standartExecutor(
        std::string i_command,
        std::vector<StandartCommandInfo> i_info);

private:
    template <typename... Args>
    static CommandWorkResult prepairCommand(
        const std::string& i_command,
        CommandWorkResult (*executableFunc)(std::string, std::vector<StandartCommandInfo>),
        Args &&...filenames)
    {
        std::string command = format(i_command, filenames...);

        return executableFunc(
            command,
            parseCommand(command)
        );
    }
};

#endif
