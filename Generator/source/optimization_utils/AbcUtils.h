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

    /// @brief getStats The method is designed to obtain statistics using the ABC tool.
    /// @param i_inputFileName The path to the input file for which you want to get statistics
    /// @param i_libName The name of the library that is used to get statistics
    /// @param i_fileDirectory The directory where the input file is located. If this parameter is not specified, the operation will be performed in the current working directory
    /// @param i_libDirectory The directory where the library is located. If this parameter is not specified, the operation will be performed in the current working directory
    /// @return an object of the Command Work Result type, which contains information about the result of performing an operation to obtain statistics using the ABC tool
    /// */

    static CommandWorkResult getStats(
        std::string i_inputFileName,
        std::string i_libName,
        std::string i_fileDirectory = ".",
        std::string i_libDirectory = ".");

   /// @brief resyn2 The method is designed to perform a resynthesis operation using the ABC tool
   /// @param i_inputFileName The path to the input file to be resynthesized
   /// @param i_libName The name of the library to be used in the process of resynthesis
   /// @param i_fileDirectory The directory where the input file is located. If this parameter is not specified, the operation will be performed in the current working directory
   /// @param i_libDirectory The directory where the library is located. If this parameter is not specified, the operation will be performed in the current working directory
   /// @return An object of the Command Work Result type, which contains information about the result of performing a resynthesis operation using the ABC tool
   /// */

    static CommandWorkResult resyn2(
        std::string i_inputFileName,
        std::string i_libName,
        std::string i_fileDirectory = ".",
        std::string i_libDirectory = ".");

   /// @brief optimizeWithLib The method is designed to perform an optimization operation using a given library using the ABC tool.
   /// @param i_inputFileName The path to the input file that will be used in the optimization process.
   /// @param i_libName The name of the library to be used in the optimization process
   /// @param i_fileDirectory The directory where the input file is located. If this parameter is not specified, the operation will be performed in the current working directory
   /// @param i_libDirectory The directory where the library is located. If this parameter is not specified, the operation will be performed in the current working directory
   /// @return an object of the Command Work Result type, which contains information about the result of performing an optimization operation using a given library using the ABC tool***
   /// */

    static CommandWorkResult optimizeWithLib(
        std::string i_inputFileName,
        std::string i_libName,
        std::string i_fileDirectory = ".",
        std::string i_libDirectory = ".");

   /// @brief verilogToBench The method is designed to convert Verilog code into the BENCH format using the ABC tool
   /// @param i_inputFileName The path to the input file in Verilog format, which will be converted to the BENCH format
   /// @param i_outputFileName The path to the output file where the code will be saved in the BENCH format after conversion
   /// @param i_libDirectory A directory containing libraries that can be used in the conversion process. This parameter may be empty if libraries are not used during conversion
   /// @return An object of the Command Work Result type. This object contains information about the result of the Verilog code conversion operation to the BENCH format
   /// */
    
    static CommandWorkResult verilogToBench(
        std::string i_inputFileName,
        std::string i_outputFileName,
        std::string i_libDirectory = ".");

   /// @brief parseCommand The method is designed to analyze the command line of the FIZ and extract information about each command from this line.
   /// @param i_command a string representing the ABC command
   /// @return A vector of objects of the Standard Command Info type containing information about each command in a string
   /// */

    static std::vector<StandartCommandInfo> parseCommand(
        std::string i_command);

protected:

   /// @brief standartExecutor TO DO:
   /// 
   /// </summary>
   /// <param name="i_command"></param>
   /// <param name="i_info"></param>
   /// */

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
