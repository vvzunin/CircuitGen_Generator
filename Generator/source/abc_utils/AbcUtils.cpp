#include <string>
#include <iostream>
#include <vector>
#include <thread>
#include <cassert>
#include <stdlib.h>

#include "AbcUtils.h"


// declare of value of static var
inline std::string AbcUtils::d_utilWord = "abc ";
inline std::string AbcUtils::d_className = "AbcUtils";
inline int AbcUtils::d_utilLen = 8;


inline void AbcUtils::standartExecutor(
            std::string i_command,
            std::vector<StandartCommandInfo> i_info, 
            void (*i_onFinish) (bool)) 
{
    FILE *abcOutput;
    char out[40];
    bool correct = true;

    // executing i_command with own read stream
    abcOutput = popen(i_command.c_str(), "r");

    std::string result;
    // parsing output
    while (fgets(out, sizeof(out), abcOutput)) {
        result += out;
    }

    // looking for each i_command execution
    int firstPos = result.find(d_utilWord, 0);

    // if there was an error
    if (firstPos != std::string::npos) {
        for (auto currentCommand : i_info) {
            int secondPos = result.find(d_utilWord, firstPos + 1);

            // if there was an error
            if (secondPos == std::string::npos) {
                std::cout << "Something went wrong during files parsing in " << d_className << '\n';
                correct = false;
                break;
            }

            int delta = d_utilLen + currentCommand.sumLen;
            
            // If something went wrong during read
            // and abc wrote something
            if (secondPos - firstPos > delta) {
                std::cerr << "Incorrect " << currentCommand.info << ": " << result.substr(firstPos + delta, secondPos - firstPos - delta) << '\n';
                correct = false;
                break;
            }

            firstPos = secondPos;
        }
    }
    else {
        std::cout << "Something went wrong during files parsing in " << d_className << '\n';
        correct = false;
    }

    if (i_onFinish)
        i_onFinish(correct);
}


inline std::vector<StandartCommandInfo> AbcUtils::parseCommand(
            std::string i_command,
            bool i_parseAll) 
{
    // we use the fact, that each i_command is surrounded by "
    int end, start;
    std::vector<StandartCommandInfo> info;

    start = i_command.find('"');
    end = i_command.find('"', start + 1);
    
    while (start != std::string::npos) {
        int commandNameStart = i_command.find_first_not_of(" ", start + 1);
        int commandNameEnd = i_command.find(" ", commandNameStart);

        // sumLen: end is bigger on 1 than real i_command ending, start is on 1 smaller,
        // but we have \n in the end, so we do not add 1
        // info: we use substr, "commandNameEnd - commandNameStart + 1" will show
        // i_command name with a space
        StandartCommandInfo commandInfo = {
            .sumLen = end - start,
            .info = i_command.substr(commandNameStart, commandNameEnd - commandNameStart)
        };

        info.push_back(commandInfo);
        
        // next two "
        start = i_command.find('"', end + 1);
        end = i_command.find('"', start + 1);
    }

    return info;
}


inline std::thread AbcUtils::verilogToAiger(
    std::string i_inputFileName, std::string i_outputFileName, void (*i_onFinish) (bool)) 
{
    // format i_command, then execute it with specified parametrs
    std::string i_command = "(echo \"read_verilog " + i_inputFileName + "\"";
    i_command += "&& echo \"strash\" && echo \"";
    i_command += "write_aiger " + i_outputFileName + "\") | abc";
    
    std::thread threadExecutor(
        standartExecutor, 
        i_command, 
        parseCommand(i_command),
        i_onFinish
    );

    return threadExecutor;
}

inline std::thread AbcUtils::verilogToAiger(
    std::string i_inputFileName, std::string i_outputFileName, std::string i_directory, void (*i_onFinish) (bool)) 
{
    if (i_directory[i_directory.size() - 1] != '/')
        i_directory += "/";

    return verilogToAiger(i_directory + i_inputFileName, i_directory + i_outputFileName, i_onFinish);
}

inline std::thread AbcUtils::aigerToVerilog(
    std::string i_inputFileName, std::string i_outputFileName, void (*i_onFinish) (bool)) 
{
    std::string i_command = "(echo \"read_aiger " + i_inputFileName + "\"";
    i_command += "&& echo \"strash\" && echo \"";
    i_command += "write_verilog " + i_outputFileName + "\") | abc";
    
    std::thread threadExecutor(
        standartExecutor, 
        i_command, 
        parseCommand(i_command),
        i_onFinish
    );

    return threadExecutor;
}

inline std::thread AbcUtils::aigerToVerilog(
    std::string i_inputFileName, std::string i_outputFileName, std::string i_directory, void (*i_onFinish) (bool)) 
{
    if (i_directory[i_directory.size() - 1] != '/')
        i_directory += "/";

    return aigerToVerilog(i_directory + i_inputFileName, i_directory + i_outputFileName, i_onFinish);
}


inline std::thread AbcUtils::balanceVerilog(std::string i_inputFileName, void (*i_onFinish) (bool)) {
    std::string i_command = "(echo \"read_verilog " + i_inputFileName + "\"";
    i_command += "&& echo \"balance\" && echo \"";
    i_command += "write_verilog " + i_inputFileName + "\") | abc";
    
    std::thread threadExecutor(
        standartExecutor, 
        i_command, 
        parseCommand(i_command),
        i_onFinish
    );

    return threadExecutor;
}

inline std::thread AbcUtils::balanceVerilog(std::string i_inputFileName, std::string i_directory, void (*i_onFinish) (bool)) {
    if (i_directory[i_directory.size() - 1] != '/')
        i_directory += "/";

    return balanceVerilog(i_directory + i_inputFileName, i_onFinish);
}

inline std::thread AbcUtils::balanceAiger(std::string i_inputFileName, void (*i_onFinish) (bool)) {
    std::string i_command = "(echo \"read_aiger " + i_inputFileName + "\"";
    i_command += "&& echo \"balance\" && echo \"";
    i_command += "write_aiger " + i_inputFileName + "\") | abc";
    
    std::thread threadExecutor(
        standartExecutor, 
        i_command, 
        parseCommand(i_command),
        i_onFinish
    );

    return threadExecutor;
}

inline std::thread AbcUtils::balanceAiger(std::string i_inputFileName, std::string i_directory, void (*i_onFinish) (bool)) {
    if (i_directory[i_directory.size() - 1] != '/')
        i_directory += "/";

    return balanceAiger(i_directory + i_inputFileName, i_onFinish);
}
