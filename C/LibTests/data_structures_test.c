#include "data_structures.h"
#include "gtest.h"

TEST(swap,Test1) 
{
    double list[5];
    list[0] = 5;
    list[1] = 7;
    list[2] = 2;
    list[3] = 2.6;
    list[4] = 65;

        

    EXPECT_EQ(list[0],5);
    EXPECT_EQ(list[1],7);
    EXPECT_EQ(list[2],2);
    EXPECT_EQ(list[3],2.6);
    EXPECT_EQ(list[4],65);

    swap(list,0,1);

    EXPECT_EQ(list[0],7);
    EXPECT_EQ(list[1],5);
    EXPECT_EQ(list[2],2);
    EXPECT_EQ(list[3],2.6);
    EXPECT_EQ(list[4],65);

}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

















