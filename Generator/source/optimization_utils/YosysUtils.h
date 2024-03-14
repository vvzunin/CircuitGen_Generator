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

    /// @brief optVerilog The method is designed to optimize Verilog code using the Yosys tool
    /// @param i_inputFileName The path to the Verilog input file that needs to be optimized
    /// @param i_outputFileName The path to the output file where the optimized Verilog code will be saved.
    /// @param i_directory The directory where the optimization operation will be performed. If this parameter is not specified, the operation will be performed in the current working directory
    /// @return The method returns an object of the Command Work Result type, which contains information about the result of the Verilog code optimization operation
    /// */


    static CommandWorkResult optVerilog(
        std::string i_inputFileName,
        std::string i_outputFileName,
        std::string i_directory = ".");

    /// @brief writeFirrtl The method is designed to write Verilog code to FIRRTL format using the Yosys tool.
   /// @param i_inputFileName The path to the Verilog input file to be converted to FIRRTL format.
   /// @param i_outputFileName The path to the file where the code will be saved in FIRRTL format
   /// @param i_directory The directory where the write operation will be performed in the FIRRTL format
   /// @return An object of the Command Work Result type, which contains information about the result of the operation of writing Verilog code to FIRRTL format
   /// */

    static CommandWorkResult writeFirrtl(
        std::string i_inputFileName,
        std::string i_outputFileName,
        std::string i_directory = ".");

    /// @brief parseCommand The method is designed to parse the Yosys command passed as a string and extract information about each command
   /// @param i_command a string containing the Yosys command.
   /// @return an object of type std::vector<Standard Command Info>. This vector contains information about each command extracted from the i_command string. Each element of the StandartCommandInfo vector represents information about a specific command, including its name and length in characters
   /// */

    // IMPORTANT parseAll here is TRUE
    static std::vector<StandartCommandInfo> parseCommand(
        std::string i_command);

protected:

    /// @brief standartExecutor The method is designed to execute the Io sys command and process its output.
  /// @param i_command a string containing the Yosys command
  /// @param i_info a vector containing information about commands
  /// @return An object of the Command Work Result type containing information about the execution of the command***
  /// */

    static CommandWorkResult standartExecutor(
        std::string i_command,
        std::vector<StandartCommandInfo> i_info);

private:
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
