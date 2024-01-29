#ifndef ABC_UTILS_H
#define ABC_UTILS_H

#include <string>
#include <vector>

#include "StandartUtil.h"

/*
This class is made for basic work with abc.
Using it, it is possible to read verlog file,
read aiger file, make strash and to write file into
verilog or aiger
*/
class AbcUtils
{
public:
    static CommandWorkResult getStats(
        std::string i_inputFileName,
        std::string i_libName,
        std::string i_fileDirectory = ".",
        std::string i_libDirectory = ".");

    static CommandWorkResult resyn2(
        std::string i_inputFileName,
        std::string i_libName,
        std::string i_fileDirectory = ".",
        std::string i_libDirectory = ".");

    static CommandWorkResult optimizeWithLib(
        std::string i_inputFileName,
        std::string i_libName,
        std::string i_fileDirectory = ".",
        std::string i_libDirectory = ".");
    
    static CommandWorkResult verilogToBench(
        std::string i_inputFileName,
        std::string i_outputFileName,
        std::string i_libDirectory = ".");

    static std::vector<StandartCommandInfo> parseCommand(
        std::string i_command);

protected:
    static CommandWorkResult standartExecutor(
        std::string i_command,
        std::vector<StandartCommandInfo> i_info);

private:
    static CommandWorkResult runExecutorForStats(
        std::string i_command,
        std::vector<StandartCommandInfo> i_info);

    template <typename... Args>
    static CommandWorkResult runCommand(
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
