#include <map>
#include <string>
#include <vector>
#include <cassert>
#include <stdlib.h>
#include <iostream>
#include <algorithm>

#include "AbcUtils.h"
#include "UtilsCommands.h"

// declare of value of static var
static std::string d_utilWord = "abc ";
static int d_utilLen = 8;

// which commands can output something
static std::vector<std::string> d_allowedOutput = {
    "read",
    "print",
    "map"};
// which words means errors
static std::vector<std::string> d_incorrectWords = {
    "Error",
    "failed",
    "Cannot"};

CommandWorkResult AbcUtils::standartExecutor(
    std::string i_command,
    std::vector<StandartCommandInfo> i_info)
{
    FILE *abcOutput;
    char out[40];
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
    // workResult.commandsOutput = std::map<std::string, std::string>();

    bool inputParsed = false;

    // if there was an error
    if (firstPos != std::string::npos)
    {
        for (auto currentCommand : i_info)
        {
            int secondPos = result.find(d_utilWord, firstPos + 1);

            // if there was an error
            if (secondPos == std::string::npos && currentCommand.info != "quit")
            {
                std::string errText = "Something went wrong during files parsing in AbcUtils\n";

                std::cerr << errText;
                workResult.commandsOutput.clear();
                workResult.commandsOutput["error"] = errText;
                workResult.commandsOutput["fileRead"] = inputParsed;

                correct = false;
                break;
            }
            else if (currentCommand.info == "quit")
            {
                break;
            }

            int delta = d_utilLen + currentCommand.sumLen;

            // Проверяем, что в команде мы не запрашивали вывод
            bool allowedToPrint = false;
            for (int i = 0; i < d_allowedOutput.size() && !allowedToPrint; ++i)
                allowedToPrint = currentCommand.info.find(d_allowedOutput[i]) != std::string::npos;

            // If something went wrong during read
            // and abc wrote something
            if (!allowedToPrint && secondPos - firstPos > delta)
            {
                std::string errText = "Incorrect " + currentCommand.info + ": " + result.substr(firstPos + delta, secondPos - firstPos - delta) + '\n';

                std::cerr << errText;
                workResult.commandsOutput.clear();
                workResult.commandsOutput["error"] = errText;
                workResult.commandsOutput["fileRead"] = inputParsed;

                correct = false;
                break;
            }
            // If we can print sth, we check, is there something illegal in this output
            else if (allowedToPrint)
            {
                std::string output = result.substr(firstPos + delta, secondPos - firstPos - delta);

                for (int i = 0; i < d_incorrectWords.size() && correct; ++i)
                {
                    if (output.find(d_incorrectWords[i]) != std::string::npos)
                    {
                        std::string errText = "Incorrect " + currentCommand.info + ": " + output + '\n';

                        std::cerr << errText;
                        workResult.commandsOutput.clear();
                        workResult.commandsOutput["error"] = errText;
                        workResult.commandsOutput["fileRead"] = inputParsed;

                        correct = false;
                    }
                }

                if (!correct)
                    break;

                workResult.commandsOutput[currentCommand.info] = output;
            }

            firstPos = secondPos;
            inputParsed = true;
        }
    }
    else
    {
        std::string errText = "Something went wrong during files parsing in AbcUtils: \n";
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

std::vector<StandartCommandInfo> AbcUtils::parseCommand(std::string i_command)
{
    // we use the fact, that each i_command is surrounded by "
    int end, start;
    std::vector<StandartCommandInfo> info;

    start = i_command.find('"');
    end = i_command.find('"', start + 1);

    while (start != std::string::npos)
    {
        int commandNameStart = i_command.find_first_not_of(" ", start + 1);
        // if it's read_verilog etc, frist is ' ', else - '"'
        int commandNameEnd = std::min(
            i_command.find(' ', commandNameStart),
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

CommandWorkResult AbcUtils::runExecutorForStats(
    std::string i_command,
    std::vector<StandartCommandInfo> i_info)
{
    CommandWorkResult final_res = standartExecutor(
        i_command,
        i_info);

    // if there were no errors and sth was printed
    if (final_res.correct && final_res.commandsOutput.count("print_stats"))
    {
        std::string stats = final_res.commandsOutput["print_stats"];

        // change \n to ' ' for correct work
        stats[stats.size() - 1] = ' ';

        final_res.commandsOutput.clear();

        int startPos = stats.find("=");
        startPos = stats.find_first_not_of(' ', startPos + 1);
        {
            int endPos = stats.find('/', startPos + 1);
            final_res.commandsOutput["inputs"] = stats.substr(startPos, endPos - startPos);

            startPos = stats.find_first_not_of(' ', endPos + 1);
            endPos = stats.find(' ', startPos + 1);

            final_res.commandsOutput["outputs"] = stats.substr(startPos, endPos - startPos);
        }

        // beginning of required info about circuit
        startPos = stats.find("lat", startPos);

        while (startPos != std::string::npos)
        {
            int wordEnd = stats.find(' ', startPos + 1);

            int digitStart = stats.find('=', wordEnd + 1);
            digitStart = stats.find_first_not_of(' ', digitStart + 1);

            int digitEnd = stats.find(' ', digitStart + 1);

            final_res.commandsOutput[stats.substr(startPos, wordEnd - startPos)] = stats.substr(digitStart, digitEnd - digitStart);

            startPos = stats.find_first_not_of(' ', digitEnd + 1);
        }
    }
    else if (final_res.correct && !final_res.commandsOutput.count("print_stats"))
    {
        final_res.commandsOutput.clear();

        final_res.commandsOutput["error"] = "Incorrect output, no stats had been printed\n";
        std::cerr << final_res.commandsOutput["error"];

        final_res.correct = false;
    }

    // for(const auto& elem : final_res.commandsOutput)
    // {
    //     std::cout << elem.first << " = " << elem.second << ";\n";
    // }

    return final_res;
}

CommandWorkResult AbcUtils::getStats(
    std::string i_inputFileName,
    std::string i_libName,
    std::string i_fileDirectory,
    std::string i_libDirectory)
{
    return prepairCommand(
        AbcCommands::getStatsCommand,
        runExecutorForStats,
        i_fileDirectory,
        i_inputFileName,
        i_libDirectory,
        i_libName
    );
}

CommandWorkResult AbcUtils::resyn2(
    std::string i_inputFileName,
    std::string i_libName,
    std::string i_fileDirectory,
    std::string i_libDirectory)
{
    std::string real_name = i_inputFileName;
    // if is neccessary, remove .v
    if (real_name.find(".v") != std::string::npos)
        real_name.erase(real_name.size() - 2, 2);

    CommandWorkResult res = prepairCommand(
        AbcCommands::resyn2Command,
        runExecutorForStats,
        i_fileDirectory,
        i_inputFileName,
        i_libDirectory,
        i_libName,
        i_fileDirectory,
        real_name,
        i_fileDirectory,
        real_name
    );

    res.commandsOutput["optimization_type"] = "Resyn2";

    return res;
}

CommandWorkResult AbcUtils::optimizeWithLib(
    std::string i_inputFileName,
    std::string i_libName,
    std::string i_fileDirectory,
    std::string i_libDirectory)
{
    std::string real_name = i_inputFileName;
    // if is neccessary, remove .v
    if (real_name.find(".v") != std::string::npos)
        real_name.erase(real_name.size() - 2, 2);

    CommandWorkResult res = prepairCommand(
        AbcCommands::balanceOptimizationCommand,
        runExecutorForStats,
        i_fileDirectory,
        i_inputFileName,
        i_libDirectory,
        i_libName,
        i_fileDirectory,
        real_name,
        i_fileDirectory,
        real_name,
        i_fileDirectory,
        real_name
    );

    res.commandsOutput["optimization_type"] = "Balance";

    return res;
}
