#pragma once

#include <string>

/*
This class is made for basic work with abc.
Using it, it is possible to read verlog file,
read aiger file, make strash and to write file into
verilog or aiger
*/

class AbcUtils {
    public:
        static bool verilogToAiger(std::string i_inpuFileName, std::string i_outpuFileName);
        static bool verilogToAiger(
            std::string i_inpuFileName, std::string i_outpuFileName, std::string i_directory
        );

        static bool aigerToVerilog(std::string i_inpuFileName, std::string i_outpuFileName);
        static bool aigerToVerilog(
            std::string i_inpuFileName, std::string i_outpuFileName, std::string i_directory
        );

        static bool balanceVerilog(std::string i_inpuFileName);
        static bool balanceVerilog(std::string i_inpuFileName, std::string i_directory);

        static bool balanceAiger(std::string i_inpuFileName);
        static bool balanceAiger(std::string i_inpuFileName, std::string i_directory);

        static bool strashVerilog(std::string i_inpuFileName);
        static bool strashVerilog(std::string i_inpuFileName, std::string i_directory);

        static bool strashAiger(std::string i_inpuFileName);
        static bool strashAiger(std::string i_inpuFileName, std::string i_directory);
    private:
        // len of "abc 0*> "
        static const int abc_len = 8;
        // "abc *" itself
        static const std::string abc_word;

        // "read_verilog" len
        static const int r_verilog_len = 12;
        // "write_verilog" len
        static const int w_verilog_len = 13;

        // "read_aiger" len
        static const int r_aiger_len = 10;
        // "write_aiger" len
        static const int w_aiger_len = 11;

        // len of "strash"
        static const int strash_len = 6;
        // len of "balance"
        static const int balance_len = 7;

        static bool standartExecutor(
            std::string command,
            int i_len, 
            int o_len, 
            int first_command, 
            int second_command, 
            int third_command
        );
};
