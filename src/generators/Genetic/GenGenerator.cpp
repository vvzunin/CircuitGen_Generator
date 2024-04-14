
#include <algorithm>
#include <filesystem>
#include <iostream>
#include <string>
#include <utility>

#include <additional/filesTools/FilesTools.h>
#include <baseStructures/Parser.h>
#include <baseStructures/truthTable/TruthTable.h>
#include <circuits/Circuit.h>
#include <generators/simple/SimpleGenerators.h>
#include <GenGenerator.h>

#include "cstdlib"

// Deleted anonymous namespace. And moved template function definition into
// header GenGenerator.h because otherwise it can not be compiled.
//  bool isNumber(const std::string& s)
//  {
//    for (auto c : s)
//    {
//      if (!std::isdigit(c))
//        return false;
//    }
//    return true;
//  }

// int getNumFolderFromString(const std::string& path)
// {
//   int lastSlash = 0;
//   for (int i = 0; i < path.size(); ++i)
//   {
//     if (path[i] == '_')
//       lastSlash = i;
//   }
//   std::string lastDir = path.substr(lastSlash);
//   int res = 0;
//   if (!isNumber(lastDir))
//     return 0;
//   return std::stoi(lastDir);
// }
