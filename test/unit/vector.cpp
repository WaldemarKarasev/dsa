#include <gtest/gtest.h>
#include <initializer_list>
#include <iostream>


#include <lib/containers/vector.hpp>

using s_t = lib::containers::vector<int>::size_type;

template <typename T>
using vector = lib::containers::vector<T>;

TEST(ctor_test, DEFAULT_CTOR)
{
    vector<int> vec;
    EXPECT_EQ(0, vec.allocated());
    EXPECT_EQ(0, vec.size());
    EXPECT_EQ(nullptr, vec.data());
}

TEST(ctor_test, DEFAULT_MOVE_CTOR)
{
    vector<int> vec1(2, 2);
    s_t alloc = vec1.allocated();
    s_t size = vec1.size();
    
    vector<int> vec2 = std::move(vec1);

    EXPECT_EQ(0, vec1.allocated());
    EXPECT_EQ(0, vec1.size());
    EXPECT_EQ(nullptr, vec1.data());

    EXPECT_EQ(alloc, vec2.allocated());
    EXPECT_EQ(size, vec2.size());
    for (s_t i = 0; i < vec2.size(); ++i)
    {
        EXPECT_EQ(vec2[i], 2) << "Vectors vec2 &  are not equal at index " << i;
    }
}

TEST(ctor_test, DEFAULT_MOVE_ASSIGNMENT)
{
    vector<int> vec1(2, 2);
    using s_t = vector<int>::size_type;
    s_t alloc = vec1.allocated();
    s_t size = vec1.size();
    auto ptr = vec1.data();

    vector<int> vec2;
    vec2 = std::move(vec1);

    EXPECT_EQ(0, vec1.allocated());
    EXPECT_EQ(0, vec1.size());
    EXPECT_EQ(nullptr, vec1.data());

    EXPECT_EQ(alloc, vec2.allocated());
    EXPECT_EQ(size, vec2.size());
    EXPECT_EQ(ptr, vec2.data());
}

TEST(ctor_test, COPY_CTOR)
{
    vector<int> vec1(2, 2);
    vector<int> vec2(vec1);

    EXPECT_EQ(vec1.allocated(), vec2.allocated());
    EXPECT_EQ(vec1.size(), vec2.size());
    EXPECT_NE(vec1.data(), vec2.data());
}

TEST(ctor_test, COPY_ASSIGNMENT)
{
    vector<int> vec1(2, 2);
    vector<int> vec2;
    
    vec2 = vec1;

    EXPECT_EQ(vec1.allocated(), vec2.allocated());
    EXPECT_EQ(vec1.size(), vec2.size());
    EXPECT_NE(vec1.data(), vec2.data());
}

TEST(ctor_test, INITLIST_CTOR)
{
    std::initializer_list<int> list = {0, 1, 2, 3, 4};
    vector<int> vec{0, 1, 2, 3, 4};
    
    EXPECT_EQ(list.size(), vec.size());
    EXPECT_EQ(list.size(), vec.allocated());

    for (s_t i = 0; i < vec.size(); ++i)
    {
        ASSERT_EQ(vec[i], *(list.begin()+i)) << "Vectors vec & init_list are not equal by elements comparison.\n First different elements occures at index " << i;
    }
}

TEST(ctor_test, SZ_AND_VAL_CTOR)
{
    vector<int> vec(2, 2);
    EXPECT_EQ(2, vec.allocated());
    EXPECT_EQ(2, vec.size());
    EXPECT_EQ(2, vec.allocated());
}


TEST(operators_test, OP_EQ)
{
    vector<int> vec1(2, 2);
    vector<int> vec2(2, 2);
    vector<int> vec3(2, 3);
    vector<int> vec4(3, 2);
    vector<int> vec5(2, 3);

    EXPECT_EQ(vec1, vec2);
    EXPECT_NE(vec1, vec3);
    EXPECT_NE(vec1, vec4);

    for (s_t i = 0; i < vec1.size(); ++i)
    {
        ASSERT_EQ(vec1[i], vec2[i]) << "Vectors vec1 & vec2 are not equal by elements comparison.\nFirst different elements occures at index " << i;
    }
}

TEST(allocation_test, REALLOC)
{
    constexpr s_t SZ = 10;
    vector<int> vec(SZ, 1);

    vec.push(2);

    EXPECT_EQ(SZ * 2 + 1, vec.allocated()) << "new capaxity is different from formula 2*old_cap + 1.\nOld capacity = " << SZ << "; new capacity = " << vec.allocated();
    EXPECT_EQ(SZ + 1, vec.size()) << "New size is different from formula SZ + 1.\nOld size = " << SZ << "; new size = " << vec.size(); 
    
}

TEST(exception_test, POP_EXCEPTION)
{
    vector<int> vec(1, 1);
    try
    {
        vec.pop();
        vec.pop();
        FAIL() << "Expected std::invalid_argument\n";
    }
    catch(const std::invalid_argument& e)
    {
        std::cerr << e.what() << std::endl;
        EXPECT_EQ(e.what(), std::string("trying pop from empty vector"));
    }
    catch(...)
    {
        FAIL() << "Expected pop exception";
    }
}

TEST(exception_test, TOP_EXCEPTION)
{
    vector<int> vec;
    try
    {
        vec.top();
        FAIL() << "Expected std::invalid_argument\n";
    }
    catch(const std::invalid_argument& e)
    {
        std::cerr << e.what() << std::endl;
        EXPECT_EQ(e.what(), std::string("trying top from empty vector"));
    }
    catch(...)
    {
        FAIL() << "Expected top exception";
    }
}

int main(int argc, char* argv[])
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}