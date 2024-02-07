#ifndef UTILS_COMMANDS
#define UTILS_COMMANDS

namespace AbcCommands {
static const char* resyn2Command = 
    "(echo \"read_verilog %/%\" "
    "&& echo \"read %/%\" "
    "&& echo \"balance\" "
    "&& echo \"rewrite\" "
    "&& echo \"refactor\" "
    "&& echo \"balance\" "
    "&& echo \"rewrite\" "
    "&& echo \"rewrite -z\" "
    "&& echo \"balance\" "
    "&& echo \"refactor -z\" "
    "&& echo \"rewrite -z\" "
    "&& echo \"write_verilog %/%_RESYN2.aig\" "
    "&& echo \"write_verilog %/%_RESYN2.v\" "
    "&& echo \"map\" "
    "&& echo \"print_stats\") | abc";

static const char *balanceOptimizationCommand = 
    "(echo \"read_verilog %/%\" "
    "&& echo \"read %/%\" "
    "&& echo \"balance\" "
    "&& echo \"write_verilog %/%.aig\" "
    "&& echo \"refactor -z\" "
    "&& echo \"balance -x\" "
    "&& echo \"rewrite -z\" "
    "&& echo \"write_verilog %/%_BALANCED.aig\" "
    "&& echo \"write_verilog %/%_BALANCED.v\" "
    "&& echo \"map\" "
    "&& echo \"print_stats\") | abc";

static const char *getStatsCommand = 
    "(echo \"read_verilog %/%\" "
    "&& echo \"read %/%\" "
    "&& echo \"map\" "
    "&& echo \"print_stats\") | abc";

static const char *convertVerilogToBench = 
    "cd % "
    "&& ((echo \"read_verilog %\" "
    "&& echo \"write_bench %\") | abc)";
// namesapce end
}

namespace YosysCommands {
static const char* optVerilogCommand = 
    "(echo \"read_verilog %/%\" "
    "&& echo \"opt\" "
    "&& echo \"write_verilog %/%\") | yosys";

static const char *writeFirrtlCommand = 
    "(cd % "
    "&& (echo \"read_verilog %\" "
    "&& echo \"write_firrtl %\") | yosys)";
// namesapce end
}

#endif
