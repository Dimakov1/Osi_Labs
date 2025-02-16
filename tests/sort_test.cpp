#include <gtest/gtest.h>
#include "sort.h"
#include <algorithm>
#include <time.h>

bool is_sorted_correctly(const int* sorted, const int* expected, int size) {
    for(int i = 0; i < size; ++i) {
        if(sorted[i] != expected[i]) {
            return false;
        }
    }
    return true;
}

TEST(SortTest, BubbleSort) {
    set_sort_function(Sort_Bubble);
    
    {
        int array[] = {5, 2, 9, 1, 5, 6};
        int expected[] = {1, 2, 5, 5, 6, 9};
        int size = sizeof(array)/sizeof(array[0]);
        
        Sort(array, size);
        
        EXPECT_TRUE(is_sorted_correctly(array, expected, size));
    }
    
    {
        int array[] = {3, 0, -1, 8, 7, 2};
        int expected[] = {-1, 0, 2, 3, 7, 8};
        int size = sizeof(array)/sizeof(array[0]);
        
        Sort(array, size);
        
        EXPECT_TRUE(is_sorted_correctly(array, expected, size));
    }
    
    {
        int array[] = {1};
        int expected[] = {1};
        int size = sizeof(array)/sizeof(array[0]);
        
        Sort(array, size);
        
        EXPECT_TRUE(is_sorted_correctly(array, expected, size));
    }
    
    {
        int* array = nullptr;
        int* expected = nullptr;
        int size = 0;
        
        Sort(array, size);
        
        EXPECT_TRUE(is_sorted_correctly(array, expected, size));
    }
}

TEST(SortTest, QuickSort) {
    set_sort_function(Sort_Quick);
        {
        int array[] = {5, 2, 9, 1, 5, 6};
        int expected[] = {1, 2, 5, 5, 6, 9};
        int size = sizeof(array)/sizeof(array[0]);
        
        Sort(array, size);
        
        EXPECT_TRUE(is_sorted_correctly(array, expected, size));
    }
    
    {
        int array[] = {3, 0, -1, 8, 7, 2};
        int expected[] = {-1, 0, 2, 3, 7, 8};
        int size = sizeof(array)/sizeof(array[0]);
        
        Sort(array, size);
        
        EXPECT_TRUE(is_sorted_correctly(array, expected, size));
    }
    
    {
        int array[] = {1};
        int expected[] = {1};
        int size = sizeof(array)/sizeof(array[0]);
        
        Sort(array, size);
        
        EXPECT_TRUE(is_sorted_correctly(array, expected, size));
    }
    
    {
        int* array = nullptr;
        int* expected = nullptr;
        int size = 0;
        
        Sort(array, size);
        
        EXPECT_TRUE(is_sorted_correctly(array, expected, size));
    }
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
