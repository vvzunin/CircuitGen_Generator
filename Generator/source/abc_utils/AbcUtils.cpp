#include <string>
#include <iostream>
#include <stdlib.h>
#include <cassert>
#include <vector>

#include "AbcUtils.h"

// declare of value of static var
inline const std::string AbcUtils::abc_word = "abc ";

// TODO at this moment can execute only three commands, in fact one operation
// make it to read more, if it would ne neccessary
inline bool AbcUtils::standartExecutor(
            std::string command,
            std::vector<standartCommandInfo> info) 
{
    FILE *abc_output;
    char out[40];      

    // executing command with own read stream
    abc_output = popen(command.c_str(), "r");

    std::string result;
    // parsing output
    while (fgets(out, sizeof(out), abc_output)) {
        result += out;
    }

    // looking for each command execution
    int first_pos = result.find(abc_word, 0);

    // if there was an error
    if (first_pos == std::string::npos) {
        std::cout << "Something went wrong during files parsing in AbcUtils\n";
        return false;
    }

    for (auto currentCommand : info) {
        int second_pos = result.find(abc_word, first_pos + 1);

        // if there was an error
        if (second_pos == std::string::npos) {
            std::cout << "Something went wrong during files parsing in AbcUtils\n";
            return false;
        }
        // 2 - one space and one \n
        int delta = abc_len + currentCommand.filenameLen + 
                              currentCommand.spacesAndNewlines + 
                              currentCommand.commandLen + 
                              currentCommand.flagsLen;
        
        // If something went wrong during read
        // and abc wrote something
        if (second_pos - first_pos > delta) {
            std::cerr << "Incorrect " << currentCommand.info << ": " << result.substr(first_pos + delta, second_pos - first_pos - delta) << '\n';
            return false;
        }

        first_pos = second_pos;
    }

    return true;
}

// TODO I know, that creating such structs is a bit ugly. So, I'm going
// tp fix it, but at this moment it's 22:06 of 31.12.2023, and I'm going to have a rest
inline bool AbcUtils::verilogToAiger(std::string i_inpuFileName, std::string i_outpuFileName) {
    // format command, then execute it with specified parametrs
    std::string command = "(echo \"read_verilog " + i_inpuFileName + "\"";
    command += "&& echo \"strash\" && echo \"";
    command += "write_aiger " + i_outpuFileName + "\") | abc";

    standartCommandInfo com1 = {
        .filenameLen = (int) i_inpuFileName.size(),
        .commandLen = r_verilog_len,
        .spacesAndNewlines = 2,
        .flagsLen = 0,
        .info = "read"
    };

    standartCommandInfo com2 = {
        .filenameLen = 0,
        .commandLen = strash_len,
        .spacesAndNewlines = 1,
        .flagsLen = 0,
        .info = "strash/balance"
    };

    standartCommandInfo com3 = {
        .filenameLen = (int) i_outpuFileName.size(),
        .commandLen = w_aiger_len,
        .spacesAndNewlines = 2,
        .flagsLen = 0,
        .info = "write"
    };

    std::vector<standartCommandInfo> data = { com1, com2, com3 };

    return standartExecutor(
        command, 
        data
    );
}

inline bool AbcUtils::verilogToAiger(std::string i_inpuFileName, std::string i_outpuFileName, std::string i_directory) {
    if (i_directory[i_directory.size() - 1] != '/')
        i_directory += "/";

    return verilogToAiger(i_directory + i_inpuFileName, i_directory + i_outpuFileName);
}

inline bool AbcUtils::aigerToVerilog(std::string i_inpuFileName, std::string i_outpuFileName) {
    std::string command = "(echo \"read_aiger " + i_inpuFileName + "\"";
    command += "&& echo \"strash\" && echo \"";
    command += "write_verilog " + i_outpuFileName + "\") | abc";
    
    standartCommandInfo com1 = {
        .filenameLen = (int) i_inpuFileName.size(),
        .commandLen = r_aiger_len,
        .spacesAndNewlines = 2,
        .flagsLen = 0,
        .info = "read"
    };

    standartCommandInfo com2 = {
        .filenameLen = 0,
        .commandLen = strash_len,
        .spacesAndNewlines = 1,
        .flagsLen = 0,
        .info = "strash/balance"
    };

    standartCommandInfo com3 = {
        .filenameLen = (int) i_outpuFileName.size(),
        .commandLen = w_verilog_len,
        .spacesAndNewlines = 2,
        .flagsLen = 0,
        .info = "write"
    }; 
    
    std::vector<standartCommandInfo> data = { com1, com2, com3 };

    return standartExecutor(
        command, 
        data
    );
}

inline bool AbcUtils::aigerToVerilog(std::string i_inpuFileName, std::string i_outpuFileName, std::string i_directory) {
    if (i_directory[i_directory.size() - 1] != '/')
        i_directory += "/";

    return aigerToVerilog(i_directory + i_inpuFileName, i_directory + i_outpuFileName);
}


inline bool AbcUtils::balanceVerilog(std::string i_inpuFileName) {
    std::string command = "(echo \"read_verilog " + i_inpuFileName + "\"";
    command += "&& echo \"balance\" && echo \"";
    command += "write_verilog " + i_inpuFileName + "\") | abc";
    
    standartCommandInfo com1 = {
        .filenameLen = (int) i_inpuFileName.size(),
        .commandLen = r_verilog_len,
        .spacesAndNewlines = 2,
        .flagsLen = 0,
        .info = "read"
    };

    standartCommandInfo com2 = {
        .filenameLen = 0,
        .commandLen = balance_len,
        .spacesAndNewlines = 1,
        .flagsLen = 0,
        .info = "strash/balance"
    };

    standartCommandInfo com3 = {
        .filenameLen = (int) i_inpuFileName.size(),
        .commandLen = w_verilog_len,
        .spacesAndNewlines = 2,
        .flagsLen = 0,
        .info = "write"
    }; 
    
    std::vector<standartCommandInfo> data = { com1, com2, com3 };

    return standartExecutor(
        command, 
        data
    );
}

inline bool AbcUtils::balanceVerilog(std::string i_inpuFileName, std::string i_directory) {
    if (i_directory[i_directory.size() - 1] != '/')
        i_directory += "/";

    return balanceVerilog(i_directory + i_inpuFileName);
}

inline bool AbcUtils::balanceAiger(std::string i_inpuFileName) {
    std::string command = "(echo \"read_aiger " + i_inpuFileName + "\"";
    command += "&& echo \"balance\" && echo \"";
    command += "write_aiger " + i_inpuFileName + "\") | abc";
    
    standartCommandInfo com1 = {
        .filenameLen = (int) i_inpuFileName.size(),
        .commandLen = r_aiger_len,
        .spacesAndNewlines = 2,
        .flagsLen = 0,
        .info = "read"
    };

    standartCommandInfo com2 = {
        .filenameLen = 0,
        .commandLen = balance_len,
        .spacesAndNewlines = 1,
        .flagsLen = 0,
        .info = "strash/balance"
    };

    standartCommandInfo com3 = {
        .filenameLen = (int) i_inpuFileName.size(),
        .commandLen = w_aiger_len,
        .spacesAndNewlines = 2,
        .flagsLen = 0,
        .info = "write"
    }; 
    
    std::vector<standartCommandInfo> data = { com1, com2, com3 };

    return standartExecutor(
        command, 
        data
    );
}

inline  bool AbcUtils::balanceAiger(std::string i_inpuFileName, std::string i_directory) {
    if (i_directory[i_directory.size() - 1] != '/')
        i_directory += "/";

    return balanceAiger(i_directory + i_inpuFileName);
}
