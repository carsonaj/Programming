#include "Sample.h"
#include "gtest.h"

TEST(Add,positiveNumbers) 
{
    EXPECT_EQ(8+7, add(8,7));
    EXPECT_EQ(8+7, add(7,8));
}


//TEST() 
//{
//
//}
//
//
//TEST() 
//{
//
//}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

