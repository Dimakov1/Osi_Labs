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

double measure_sort_time(void (*sort_func)(int*, int), int* array, int size, int iterations) {
    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);
    for(int i = 0; i < iterations; ++i) {
        int* temp_array = new int[size];
        memcpy(temp_array, array, size * sizeof(int));
        sort_func(temp_array, size);
        delete[] temp_array;
    }
    clock_gettime(CLOCK_MONOTONIC, &end);
    double total_time = (end.tv_sec - start.tv_sec) * 1e3 + 
                        (end.tv_nsec - start.tv_nsec) / 1e6;
    return total_time / iterations;
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
