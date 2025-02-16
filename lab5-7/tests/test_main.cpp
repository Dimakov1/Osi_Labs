#include <gtest/gtest.h>
#include "../include/node.h"

class NodeTest : public ::testing::Test {
protected:
    Node root;

    NodeTest() : root(-1) {}

    void TearDown() override {
        root.Remove_child(10);
        root.Remove_child(20);
        root.Remove_child(50);
        root.Remove_child(60);
    }
};

TEST_F(NodeTest, ExecSumCommand) {
    std::vector<int> numbers = {10, 20, 30};
    EXPECT_EQ(root.Exec_sum(numbers), 60);

    numbers = {-5, 15, 10};
    EXPECT_EQ(root.Exec_sum(numbers), 20);
}

TEST_F(NodeTest, CreateRemoveNodes) {
    EXPECT_TRUE(root.Create_child(10));
    EXPECT_TRUE(root.Create_child(20));

    EXPECT_TRUE(root.Ping_child(10));
    EXPECT_TRUE(root.Ping_child(20));

    EXPECT_TRUE(root.Remove_child(10));
    EXPECT_FALSE(root.Ping_child(10));

    EXPECT_FALSE(root.Remove_child(10));
}

TEST_F(NodeTest, RemoveNodeHierarchy) {
    EXPECT_TRUE(root.Create_child(50));
    EXPECT_TRUE(root.Create_child(60));

    EXPECT_TRUE(root.Ping_child(50));
    EXPECT_TRUE(root.Ping_child(60));

    EXPECT_TRUE(root.Remove_child(50));
    EXPECT_FALSE(root.Ping_child(50));

    EXPECT_FALSE(root.Remove_child(50));
}

TEST_F(NodeTest, CreateDuplicateNodes) {
    EXPECT_TRUE(root.Create_child(30));
    EXPECT_FALSE(root.Create_child(30)); 
}

TEST_F(NodeTest, RemoveAllNodesBeforeExit) {
    EXPECT_TRUE(root.Create_child(10));
    EXPECT_TRUE(root.Create_child(20));
    EXPECT_TRUE(root.Create_child(30));

    EXPECT_TRUE(root.Remove_child(10));
    EXPECT_TRUE(root.Remove_child(20));
    EXPECT_TRUE(root.Remove_child(30));

    EXPECT_FALSE(root.Ping_child(10));
    EXPECT_FALSE(root.Ping_child(20));
    EXPECT_FALSE(root.Ping_child(30));
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
