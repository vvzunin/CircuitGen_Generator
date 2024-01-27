#include <string>
#include <iostream>
#include <vector>
#include <thread>
#include <algorithm>
#include <functional>

#include "YosysUtils.h"

// declare of value of static var
static std::string d_utilWord = "yosys";
static int d_utilLen = 7;

static std::vector<std::string> d_incorrectWords = {
    "ERROR"};

CommandWorkResult YosysUtils::standartExecutor(
    std::string i_command,
    std::vector<StandartCommandInfo> i_info)
{
    FILE *abcOutput;
    char out[80];
    bool correct = true;

    if (i_command.find("2>&1") == std::string::npos)
        i_command += " 2>&1";
    
    // executing i_command with own read stream
    abcOutput = popen(i_command.c_str(), "r");

    std::string result;
    // parsing output
    while (fgets(out, sizeof(out), abcOutput))
    {
        result += out;
    }

    // looking for each i_command execution
    int firstPos = result.find(d_utilWord, 0);
    CommandWorkResult workResult;
    
    bool inputParsed = false;

    // if there was an error
    if (firstPos != std::string::npos)
    {
        for (auto currentCommand : i_info)
        {
            int secondPos = result.find(d_utilWord, firstPos + 1);

            // перебираем все слова-ошибки
            for (auto word : d_incorrectWords)
            {
                int errorPos = result.find(word, firstPos);

                // if there was an error
                if (secondPos == std::string::npos && errorPos == std::string::npos)
                {
                    std::string errText = "Something went wrong during files parsing in YosysUtils\n";

                    std::cerr << errText;
                    workResult.commandsOutput.clear();
                    workResult.commandsOutput["error"] = errText;
                    workResult.commandsOutput["fileRead"] = inputParsed;

                    correct = false;
                    break;
                }

                // If something went wrong during read
                // and abc wrote something
                if (errorPos != std::string::npos && (errorPos < secondPos || secondPos == std::string::npos))
                {
                    int endPos = secondPos - errorPos - 1;
                    if (secondPos == std::string::npos)
                        endPos = result.size() - errorPos - 1;

                    std::string errText = "Incorrect " + currentCommand.info + ": " + result.substr(errorPos, endPos) + '\n';
                    
                    std::cerr << errText;
                    workResult.commandsOutput.clear();
                    workResult.commandsOutput["error"] = errText;
                    workResult.commandsOutput["fileRead"] = inputParsed;
                    
                    correct = false;
                    break;
                }
            }

            firstPos = secondPos;
            inputParsed = true;
        }
    }
    else
    {
        std::string errText = "Something went wrong during files parsing in YosysUtils: \n";
        errText += result;

        std::cerr << errText;
        workResult.commandsOutput.clear();
        workResult.commandsOutput["error"] = errText;
        workResult.commandsOutput["fileRead"] = inputParsed;

        correct = false;
    }
    workResult.correct = correct;

    return workResult;
}

std::vector<StandartCommandInfo> YosysUtils::parseCommand(std::string i_command)
{
    // we use the fact, that each i_command is surrounded by "
    int end, start;
    std::vector<StandartCommandInfo> info;

    start = i_command.find('"');
    end = i_command.find('"', start + 1);

    while (start != std::string::npos)
    {
        int commandNameStart = i_command.find_first_not_of(" ", start + 1);
        int commandNameEnd = std::min(
            i_command.find(" ", commandNameStart),
            i_command.find('"', commandNameStart));

        // sumLen: end is bigger on 1 than real i_command ending, start is on 1 smaller,
        // but we have \n in the end, so we do not add 1
        // info: we use substr, "commandNameEnd - commandNameStart + 1" will show
        // i_command name with a space
        StandartCommandInfo commandInfo = {
            .sumLen = end - start,
            .info = i_command.substr(commandNameStart, commandNameEnd - commandNameStart)};

        info.push_back(commandInfo);

        // next two "
        start = i_command.find('"', end + 1);
        end = i_command.find('"', start + 1);
    }

    return info;
}

CommandWorkResult YosysUtils::optVerilog(
    std::string i_inputFileName,
    std::string i_outputFileName,
    std::string i_directory)
{
    // format i_command, then execute it with specified parametrs
    // REMEMBER
    std::string i_command = "(echo \"read_verilog " + i_directory + "/" + i_inputFileName + "\"";
    i_command += "&& echo \"opt\" && echo \"";
    i_command += "write_verilog " + i_directory + "/" + i_outputFileName + "\") | yosys 2>&1";

    return standartExecutor(
        i_command,
        parseCommand(i_command));
}

CommandWorkResult YosysUtils::writeFirrtl(
    std::string i_inputFileName,
    std::string i_outputFileName)
{

    std::string i_command = "(echo \"read_verilog " + i_inputFileName + ".v\"";
    i_command += "&& echo \"write_firrtl " + i_outputFileName + ".fir\") | yosys 2>&1";

    return standartExecutor(
        i_command,
        parseCommand(i_command));
}
