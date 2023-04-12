#include <gtest/gtest.h>
#include <algorithm>
#include "../FilesTools.h"
namespace fs = std::filesystem;
using namespace FilesTools;
//I check the using of getDirectories and I can confirm that in test we can let ourselves do not care about order of directories in the vector. Full understanding will come after  all commens below.

//There are differencies between softwares in terms of order of directories when we creating them through filesystem.
// So we will not care about the order of directories. The elements of the vectors that contain name of directories have to be the same. See below.
TEST(FileTools , OnlyDirectoriesNoFiles)
{

    fs::path tmpPath = (fs::temp_directory_path() / "test");//Created temporary guaranted directory to deal with
    std::string tmp; // This variable exist because otherwise we will not be able push tmpPath.string() to method getDirectories(Here it is gonna be)
    std::fstream file; // Created fstream variable to have the possibility to create files into temp directory to test the fucntion on counting only directories.

    fs::create_directories(tmpPath / "6");// Just created directories within temporary directory . The order does not matter. You will see below why
    fs::create_directories(tmpPath / "5");
    fs::create_directories(tmpPath / "4");
    fs::create_directories(tmpPath / "3");
    fs::create_directories(tmpPath / "2");
    fs::create_directories(tmpPath / "1");


    std::vector<std::string> correctVec = 
    {     (tmpPath / "1").string() , (tmpPath / "2").string()
        , (tmpPath / "3").string() , (tmpPath / "4").string()
        , (tmpPath / "5").string() , (tmpPath / "6").string() }; // Created vector that's gonna be compared with the result vector we wanna test 
   
    tmp = tmpPath.string();// get the path to the current directory which contain created directories
    std::vector<std::string> resVec = getDirectories(tmp);// Vector which we wanna test 

    std::sort(correctVec.begin(), correctVec.end());// If the elements of correctVec and resVec are the same
    std::sort(resVec.begin(), resVec.end());        // after sort they are both will be equal to each other.

    EXPECT_EQ(resVec, correctVec);

    std::filesystem::remove_all(tmpPath.string());//Delete the current directory we work with.
    
}
