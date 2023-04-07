#include <gtest/gtest.h>
#include "../generators/TruthTable.h"
#include <vector>

TEST(EqualOperationOfTruthTable, EqualToEachOther)
{

   EXPECT_EQ((TruthTable{ 1,  1 , std::vector<std::vector<bool>>({{true},{true}}) } == TruthTable{ 1, 1 , std::vector<std::vector<bool>>({{true},{true}}) }), true);
   EXPECT_EQ((TruthTable{ 2,  1 , std::vector<std::vector<bool>>({{true},{true} ,{true} , {false}}) } == TruthTable{ 2, 1 , std::vector<std::vector<bool>>({{true},{true} , {true} , {false}}) }), true);
   EXPECT_EQ((TruthTable{ 2,  2 , std::vector<std::vector<bool>>({{true , true},{true , true} ,{true , true} , {false , false}}) } == TruthTable{ 2,  2 , std::vector<std::vector<bool>>({{true , true},{true , true} ,{true , true} , {false , false}}) }), true);

}
TEST(EqualOperationOfTruthTable, DifferentFromEachOther)
{
    EXPECT_EQ((TruthTable{ 1,  1 , std::vector<std::vector<bool>>({{true},{true}}) } == TruthTable{ 1, 1 , std::vector<std::vector<bool>>({{true},{false}}) }), false);
    EXPECT_EQ((TruthTable{ 3,  1 , std::vector<std::vector<bool>>({{true},{true} ,{true} , {false} , {true},{true} ,{true} , {false}}) } == TruthTable{ 3, 1 , std::vector<std::vector<bool>>({{true},{true} , {true} , {false} , {true},{true} ,{true} , {true}}) }), false);
    EXPECT_EQ((TruthTable{ 1,  1 , std::vector<std::vector<bool>>({{false},{false}}) } == TruthTable{ 1, 1 , std::vector<std::vector<bool>>({{true},{true}}) }), false);
}
TEST(ConvToBinaryOfTruthTable, NormalTest)
{
    EXPECT_EQ((TruthTable{ 1  , 1 , std::vector<std::vector<bool>>({{true} , {true} }) }).convToBinary(), std::vector<std::vector<bool>>({ {false} , {true} }));
    EXPECT_EQ((TruthTable{ 2  , 1 , std::vector<std::vector<bool>>({{true} , {false}, {false} , {false} }) }).convToBinary(), std::vector<std::vector<bool>>({ { false , false }, { false , true }, { true, false }, {true , true} }));
    EXPECT_EQ((TruthTable{ 3  , 1 , std::vector<std::vector<bool>>({}) }).convToBinary(), std::vector<std::vector<bool>>({ { false , false , false },  { false , false , true },{ false , true , false }, {false , true , true} , {true , false , false} , {true , false , true} , {true, true ,false} , {true , true ,true} }));
}
TEST(ConstructorForTruthTableWithVector, CorrectSize)
{
    EXPECT_EQ((TruthTable{ 1 , 1 , std::vector<std::vector<bool>>{} }).size(), 2);
}