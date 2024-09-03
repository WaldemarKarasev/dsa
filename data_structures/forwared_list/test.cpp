// STL
#include <iostream>
#include <chrono>
#include <thread>

// Testing
#include <gtest/gtest.h>

// ForwaredList
#include "forwared_list.hpp"

TEST(Atomic, Load) {

    mylib::ForwaredList<int> list;

    list.insert_last(5);

    EXPECT_EQ(list.get_at(0), 5);
    EXPECT_EQ(list.get_at(1), 5);


}

int main(int argc, char *argv[])
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}