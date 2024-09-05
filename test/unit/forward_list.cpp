// STL
#include <iostream>
#include <chrono>
#include <thread>

// Testing
#include <gtest/gtest.h>

// ForwaredList
#include <lib/containers/forward_list.hpp>

#include <list>
#include <forward_list>

template <typename T>
using list = lib::containers::ForwaredList<T>;

TEST(Atomic, Load) {

    list<int> list;
}

int main(int argc, char *argv[])
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}