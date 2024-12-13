#include <gtest/gtest.h>
#include "gcf.h"

TEST(GCFTest, Euclidean) {
    set_gcf_function(GCF_Euclidean);
    
    EXPECT_EQ(GCF(48, 18), 6);
    EXPECT_EQ(GCF(100, 10), 10);
    EXPECT_EQ(GCF(7, 3), 1);
    EXPECT_EQ(GCF(0, 5), 5);
    EXPECT_EQ(GCF(5, 0), 5);
    EXPECT_EQ(GCF(0, 0), 0);
}

TEST(GCFTest, Naive) {
    set_gcf_function(GCF_Naive);
    
    EXPECT_EQ(GCF(48, 18), 6);
    EXPECT_EQ(GCF(100, 10), 10);
    EXPECT_EQ(GCF(7, 3), 1);
    EXPECT_EQ(GCF(0, 5), 5);
    EXPECT_EQ(GCF(5, 0), 5);
    EXPECT_EQ(GCF(0, 0), 0);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
