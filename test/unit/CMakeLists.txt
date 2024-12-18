add_executable(forward_list forward_list.cpp)
target_link_libraries(forward_list
    lib
    gtest
)

add_executable(vector vector.cpp)
target_link_libraries(vector
    lib
    gtest
)

add_executable(matrix matrix.cpp)
target_link_libraries(matrix
    lib
    gtest
)

add_executable(lock_free lock_free_queue.cpp)
target_link_libraries(lock_free
    lib
    gtest
)

gtest_discover_tests(forward_list)
gtest_discover_tests(vector)
gtest_discover_tests(matrix)
gtest_discover_tests(lock_free)