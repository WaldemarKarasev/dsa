// STL
#include <iostream>
#include <chrono>
#include <thread>

// Testing
#include <gtest/gtest.h>

// ForwaredList
#include <lib/containers/lock_free/MichielSchottQueue.hpp>


TEST(LockFree, Enqueue) {

    lib::containers::lock_free::MichielSchottQueue<int> queue;

    queue.Enqueue(5);
    queue.Enqueue(1);

    EXPECT_EQ(queue.Dequeue(), 1);
    EXPECT_EQ(queue.Dequeue(), 5);
}


TEST(LockFree, Dequeue) {

    


}

int main(int argc, char *argv[])
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}