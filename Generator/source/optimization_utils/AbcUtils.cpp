#include <map>
#include <string>
#include <iostream>
#include <vector>
#include <cassert>
#include <stdlib.h>
#include <algorithm>

#include "AbcUtils.h"


// declare of value of static var
static std::string d_utilWord = "abc ";
static std::string d_className = "AbcUtils";
static int d_utilLen = 8;

// which commands can output something
static std::vector<std::string> d_allowedOutput = {
    "read",
    "print",
    "map"
};
// which words means errors
static std::vector<std::string> d_incorrectWords = {
    "Error",
    "failed",
    "Cannot"
};


CommandWorkResult AbcUtils::standartExecutor(
            std::string i_command,
            std::vector<StandartCommandInfo> i_info) 
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

    CommandWorkResult workResult;
    workResult.commandsOutput = std::map<std::string, std::string>();

    // if there was an error
    if (firstPos != std::string::npos) {
        for (auto currentCommand : i_info) {
            int secondPos = result.find(d_utilWord, firstPos + 1);

            // if there was an error
            if (secondPos == std::string::npos && currentCommand.info != "quit") {
                std::string errText = "Something went wrong during files parsing in " + d_className + '\n';

                std::cerr << errText;
                workResult.commandsOutput.clear();
                workResult.commandsOutput["error"] = errText;
                    
                correct = false;
                break;
            }
            else if (currentCommand.info == "quit") {
                break;
            }

            int delta = d_utilLen + currentCommand.sumLen;
            
            // Проверяем, что в команде мы не запрашивали вывод
            bool allowedToPrint = false;
            for (int i = 0; i < d_allowedOutput.size() && !allowedToPrint; ++i)
                allowedToPrint = currentCommand.info.find(d_allowedOutput[i]) != std::string::npos;
            

            // If something went wrong during read
            // and abc wrote something
            if (!allowedToPrint && secondPos - firstPos > delta) {
                std::string errText = "Incorrect " + currentCommand.info + ": " + result.substr(firstPos + delta, secondPos - firstPos - delta) + '\n';
                
                std::cerr << errText;
                workResult.commandsOutput.clear();
                workResult.commandsOutput["error"] = errText;
                
                correct = false;
                break;
            }
            // If we can print sth, we check, is there something illegal in this output
            else if (allowedToPrint) {
                std::string output = result.substr(firstPos + delta, secondPos - firstPos - delta);

                for (int i = 0; i < d_incorrectWords.size() && correct; ++i) {
                    if (output.find(d_incorrectWords[i]) != std::string::npos) {
                        std::string errText = "Incorrect " + currentCommand.info + ": " + output + '\n';

                        std::cerr << errText;
                        workResult.commandsOutput.clear();
                        workResult.commandsOutput["error"] = errText;

                        correct = false;
                    }
                }

                if (!correct)
                    break;
                
                workResult.commandsOutput[currentCommand.info] = output;
            }

            firstPos = secondPos;
        }
    }
    else {
        std::cout << "Something went wrong during files parsing in " << d_className << '\n';
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
    
    while (start != std::string::npos) {
        int commandNameStart = i_command.find_first_not_of(" ", start + 1);
        // if it's read_verilog etc, frist is ' ', else - '"'
        int commandNameEnd = std::min(
            i_command.find(' ', commandNameStart),
            i_command.find('"', commandNameStart)        
        );

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


CommandWorkResult AbcUtils::runExecutorForStats(
        std::string i_command,
        std::vector<StandartCommandInfo> i_info)
{
    CommandWorkResult final_res = standartExecutor(
        i_command, 
        i_info
    );

    // if there were no errors and sth was printed
    if (final_res.correct && final_res.commandsOutput.count("print_stats")) {
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

        while (startPos != std::string::npos) {
            int wordEnd = stats.find(' ', startPos + 1);

            int digitStart = stats.find('=', wordEnd + 1);
            digitStart = stats.find_first_not_of(' ', digitStart + 1);

            int digitEnd = stats.find(' ', digitStart + 1);

            final_res.commandsOutput[stats.substr(startPos, wordEnd - startPos)] = stats.substr(digitStart, digitEnd - digitStart);

            startPos = stats.find_first_not_of(' ', digitEnd + 1);
        }
    }
    else if (final_res.correct && !final_res.commandsOutput.count("print_stats")) {
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
    std::string i_libName)
{
        // format i_command, then execute it with specified parametrs
    std::string i_command = "(echo \"read_verilog " + i_inputFileName + "\" ";
    i_command += "&& echo \"read " + i_libName + "\" ";
    i_command += "&& echo \"map\" ";
    i_command += "&& echo \"print_stats\") | abc";
    
    return runExecutorForStats(
        i_command, 
        parseCommand(i_command)
    );
}

CommandWorkResult AbcUtils::getStats(
    std::string i_inputFileName,  
    std::string i_libName,
    std::string i_fileDirectory,
    std::string i_libDirectory)
{
    if (i_fileDirectory[i_fileDirectory.size() - 1] != '/')
        i_fileDirectory += "/";
    
    if (i_libDirectory[i_libDirectory.size() - 1] != '/')
        i_libDirectory += "/";

    return getStats(
        i_fileDirectory + i_inputFileName,
        i_libDirectory + i_libName
    );
}

CommandWorkResult AbcUtils::resyn2(
    std::string i_inputFileName,  
    std::string i_libName)
{
    std::string real_name = i_inputFileName;
    // if is neccessary, remove .v
    if (real_name.find(".v") != std::string::npos)
        real_name.erase(real_name.size() - 2, 2);

    // format i_command, then execute it with specified parametrs
    std::string i_command = "(echo \"read_verilog " + i_inputFileName + "\" ";
    i_command += "&& echo \"read " + i_libName + "\" ";
    i_command += "&& echo \"balance\" ";
    i_command += "&& echo \"rewrite\" ";
    i_command += "&& echo \"refactor\" ";
    i_command += "&& echo \"balance\" ";
    i_command += "&& echo \"rewrite\" ";
    i_command += "&& echo \"rewrite -z\" ";
    i_command += "&& echo \"balance\" ";
    i_command += "&& echo \"refactor -z\" ";
    i_command += "&& echo \"rewrite -z\" ";
    i_command += "&& echo \"write_verilog " + real_name + "_RESYN2.aig\" ";
    i_command += "&& echo \"map\" ";
    i_command += "&& echo \"print_stats\" ";
    i_command += "&& echo \"unmap\" ";
    i_command += "&& echo \"write_verilog " + real_name + "_RESYN2.v\") | abc";
    
    
    CommandWorkResult res = runExecutorForStats(
        i_command, 
        parseCommand(i_command)
    );

    res.commandsOutput["optimization_type"] = "Resyn2";

    return res;
}

CommandWorkResult AbcUtils::resyn2(
    std::string i_inputFileName,  
    std::string i_libName,
    std::string i_fileDirectory,
    std::string i_libDirectory) 
{
    if (i_fileDirectory[i_fileDirectory.size() - 1] != '/')
        i_fileDirectory += "/";
    
    if (i_libDirectory[i_libDirectory.size() - 1] != '/')
        i_libDirectory += "/";

    return resyn2(
        i_fileDirectory + i_inputFileName,
        i_libDirectory + i_libName
    );
}

CommandWorkResult AbcUtils::optimizeWithLib(
    std::string i_inputFileName,  
    std::string i_libName) 
{
    std::string real_name = i_inputFileName;
    // if is neccessary, remove .v
    if (real_name.find(".v") != std::string::npos)
        real_name.erase(real_name.size() - 2, 2);

    // format i_command, then execute it with specified parametrs
    std::string i_command = "(echo \"read_verilog " + i_inputFileName + "\" ";
    i_command += "&& echo \"read " + i_libName + "\" ";
    i_command += "&& echo \"balance\" ";
    i_command += "&& echo \"write_verilog " + real_name + ".aig\" ";
    i_command += "&& echo \"refactor -z\" ";
    i_command += "&& echo \"balance -x\" ";
    i_command += "&& echo \"rewrite -z\" ";
    i_command += "&& echo \"write_verilog " + real_name + "_BALANCED.aig\" ";
    i_command += "&& echo \"map\" ";
    i_command += "&& echo \"print_stats\" ";
    i_command += "&& echo \"unmap\" ";
    i_command += "&& echo \"write_verilog " + real_name + "_BALANCED.v\") | abc";
    
    
    CommandWorkResult res = runExecutorForStats(
        i_command, 
        parseCommand(i_command)
    );

    res.commandsOutput["optimization_type"] = "Balance";

    return res;
}

CommandWorkResult AbcUtils::optimizeWithLib(
    std::string i_inputFileName,   
    std::string i_libName,
    std::string i_fileDirectory,
    std::string i_libDirectory)
{
    if (i_fileDirectory[i_fileDirectory.size() - 1] != '/')
        i_fileDirectory += "/";
    
    if (i_libDirectory[i_libDirectory.size() - 1] != '/')
        i_libDirectory += "/";

    return optimizeWithLib(
        i_fileDirectory + i_inputFileName,
        i_libDirectory + i_libName
    );
}


CommandWorkResult AbcUtils::verilogToAiger(
    std::string i_inputFileName,  std::string i_outputFileName) 
{
    // format i_command, then execute it with specified parametrs
    std::string i_command = "(echo \"read_verilog " + i_inputFileName + "\"";
    i_command += "&& echo \"strash\" && echo \"";
    i_command += "write_aiger " + i_outputFileName + "\") | abc";
    
    return standartExecutor( 
        i_command, 
        parseCommand(i_command)
    );
}

CommandWorkResult AbcUtils::verilogToAiger(
    std::string i_inputFileName,  std::string i_outputFileName, std::string i_directory) 
{
    if (i_directory[i_directory.size() - 1] != '/')
        i_directory += "/";

    return verilogToAiger(i_directory + i_inputFileName, i_directory + i_outputFileName);
}

CommandWorkResult AbcUtils::aigerToVerilog(
    std::string i_inputFileName,  std::string i_outputFileName) 
{
    std::string i_command = "(echo \"read_aiger " + i_inputFileName + "\"";
    i_command += "&& echo \"strash\" && echo \"";
    i_command += "write_verilog " + i_outputFileName + "\") | abc";
    
    return standartExecutor( 
        i_command, 
        parseCommand(i_command)
    );
}

CommandWorkResult AbcUtils::aigerToVerilog(
    std::string i_inputFileName,  std::string i_outputFileName, std::string i_directory) 
{
    if (i_directory[i_directory.size() - 1] != '/')
        i_directory += "/";

    return aigerToVerilog(i_directory + i_inputFileName, i_directory + i_outputFileName);
}


CommandWorkResult AbcUtils::balanceVerilog(std::string i_inputFileName,  void (*i_onFinish) (CommandWorkResult)) {
    std::string i_command = "(echo \"read_verilog " + i_inputFileName + "\"";
    i_command += "&& echo \"balance\" && echo \"";
    i_command += "write_verilog " + i_inputFileName + "\") | abc";
    
    return standartExecutor( 
        i_command, 
        parseCommand(i_command)
    );
}

CommandWorkResult AbcUtils::balanceVerilog(std::string i_inputFileName,  std::string i_directory) {
    if (i_directory[i_directory.size() - 1] != '/')
        i_directory += "/";

    return balanceVerilog(i_directory + i_inputFileName);
}

CommandWorkResult AbcUtils::balanceAiger(std::string i_inputFileName,  void (*i_onFinish) (CommandWorkResult)) {
    std::string i_command = "(echo \"read_aiger " + i_inputFileName + "\"";
    i_command += "&& echo \"balance\" && echo \"";
    i_command += "write_aiger " + i_inputFileName + "\") | abc";
    
    return standartExecutor( 
        i_command, 
        parseCommand(i_command)
    );
}

CommandWorkResult AbcUtils::balanceAiger(std::string i_inputFileName,  std::string i_directory) {
    if (i_directory[i_directory.size() - 1] != '/')
        i_directory += "/";

    return balanceAiger(i_directory + i_inputFileName);
}
