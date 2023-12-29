#include <string>
#include <iostream>
#include <stdlib.h>
#include <cassert>

#include "AbcUtils.h"

// declare of value of static var
inline const std::string AbcUtils::abc_word = "abc ";

// TODO at this moment can execute only three commands, in fact one operation
// make it to read more, if it would ne neccessary
inline bool AbcUtils::standartExecutor(
            std::string command,
            int i_len, 
            int o_len, 
            int first_command, 
            int second_command, 
            int third_command) 
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
    int read_pos = result.find(abc_word, 0);
    int strash_pos = result.find(abc_word, read_pos + 1);
    int write_pos = result.find(abc_word, strash_pos + 1);
    int end_pos = result.find(abc_word, write_pos + 1);

    // if there was an error
    if (
        read_pos == std::string::npos || 
        strash_pos == std::string::npos || 
        write_pos == std::string::npos || 
        end_pos == std::string::npos
    ) 
    {
        std::cout << "Something went wrong during files parsing in AbcUtils\n";
        return false;
    }

    // 2 - one space and one \n
    int delta = abc_len + first_command + 2 + i_len;

    // If something went wrong during read
    // and abc wrote something
    if (strash_pos - read_pos > delta) {
        std::cerr << "Incorrect read: " << result.substr(read_pos + delta, strash_pos - read_pos - delta) << '\n';
        return false;
    }

    delta = abc_len + second_command + 1;
    // If there were some problems with strash
    if (write_pos - strash_pos > delta) {
        std::cerr << "Incorrect strash/balance: " << result.substr(strash_pos + delta, write_pos - strash_pos - delta) << '\n';
        return false;
    }

    delta = abc_len + third_command + 2 + o_len;
    // If there were problems during writing
    if (end_pos - write_pos > delta) {
        std::cerr << "Incorrect write: " << result.substr(write_pos + delta, end_pos - write_pos - delta) << '\n';
        return false;
    }

    return true;
}

inline bool AbcUtils::verilogToAiger(std::string i_inpuFileName, std::string i_outpuFileName) {
    // format command, then execute it with specified parametrs
    std::string command = "(echo \"read_verilog " + i_inpuFileName + "\"";
    command += "&& echo \"strash\" && echo \"";
    command += "write_aiger " + i_outpuFileName + "\") | abc";

    return standartExecutor(
        command, 
        i_inpuFileName.size(), i_outpuFileName.size(), 
        r_verilog_len, strash_len, w_aiger_len
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
    
    return standartExecutor(
        command, 
        i_inpuFileName.size(), i_outpuFileName.size(), 
        r_aiger_len, strash_len, w_verilog_len
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
    
    return standartExecutor(
        command, 
        i_inpuFileName.size(), i_inpuFileName.size(), 
        r_verilog_len, balance_len, w_verilog_len
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
    
    return standartExecutor(
        command, 
        i_inpuFileName.size(), i_inpuFileName.size(), 
        r_aiger_len, balance_len, w_aiger_len
    );
}

inline  bool AbcUtils::balanceAiger(std::string i_inpuFileName, std::string i_directory) {
    if (i_directory[i_directory.size() - 1] != '/')
        i_directory += "/";

    return balanceAiger(i_directory + i_inpuFileName);
}
