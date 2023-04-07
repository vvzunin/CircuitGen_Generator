#include <gtest/gtest.h>
#include "../generators/TruthTable.h"
#include <vector>

TEST(EqualOperationOfTruthTable, EqualToEachOther)
{

   EXPECT_EQ((TruthTable{ 1,  1 , std::vector<std::vector<bool>>({{true},{true}}) } == TruthTable{ 1, 1 , std::vector<std::vector<bool>>({{true},{true}}) }), true);
   EXPECT_EQ((TruthTable{ 2,  1 , std::vector<std::vector<bool>>({{true},{true} ,{true} , {false}}) } == TruthTable{ 2, 1 , std::vector<std::vector<bool>>({{true},{true} , {true} , {false}}) }), true);
   EXPECT_EQ((TruthTable{ 2,  2 , std::vector<std::vector<bool>>({{true , true},{true , true} ,{true , true} , {false , false}}) } == TruthTable{ 2,  2 , std::vector<std::vector<bool>>({{true , true},{true , true} ,{true , true} , {false , false}}) }), true);

}