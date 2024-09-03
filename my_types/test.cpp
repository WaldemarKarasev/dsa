#include <gtest/gtest.h>
#include "../data_structures/vector/vector.h"
#include "matrix.h"

using s_t = MyTypes::matrix<int, containers::vector<int>>::size_type;

TEST(OPERATORS, EQUAL)
{
    MyTypes::matrix<int, containers::vector<int>> mat1(3, 2, {1, 2, 3, 4, 5, 6});
    MyTypes::matrix<int, containers::vector<int>> mat2(3, 2, {1, 2, 3, 4, 5, 6});
    MyTypes::matrix<int, containers::vector<int>> mat3(3, 2, {1, 1, 1, 1, 1, 1});
    MyTypes::matrix<int, containers::vector<int>> mat4(2, 3, {1, 2, 3, 4, 5, 6});

    EXPECT_EQ(true,  mat1 == mat2);
    EXPECT_EQ(false, mat1 == mat3);
    EXPECT_EQ(false, mat1 == mat4);
}

TEST(CTORS, DEFAULT_CTOR)
{
    MyTypes::matrix<int, containers::vector<int>> mat;
    containers::vector<int> vec;
    EXPECT_EQ(0, mat.getRows());
    EXPECT_EQ(0, mat.getCols());
    EXPECT_EQ(vec, mat.getBuf());
}

TEST(CTORS, RCV_CTOR)
{
    constexpr s_t ROWS = 2;
    constexpr s_t COLS = 3;

    MyTypes::matrix<int, containers::vector<int>> mat1(ROWS, COLS);
    containers::vector<int> vec1(ROWS * COLS);
    EXPECT_EQ(ROWS, mat1.getRows());
    EXPECT_EQ(COLS, mat1.getCols());
    EXPECT_EQ(vec1, mat1.getBuf());

    MyTypes::matrix<int, containers::vector<int>> mat2(ROWS, COLS, {1, 2, 3, 4, 5, 6});
    containers::vector<int> vec2{1, 2, 3, 4, 5, 6};
    EXPECT_EQ(vec2, mat2.getBuf());
}

TEST(CTORS_TEST, MOVE_CTORS)
{
    constexpr s_t ROWS = 2;
    constexpr s_t COLS = 3;

    MyTypes::matrix<int, containers::vector<int>> mat1(ROWS, COLS, {1, 2, 3, 4, 5, 6});

    s_t row = mat1.getRows();
    s_t col = mat1.getCols();
    containers::vector<int> vec_init = mat1.getBuf();

    MyTypes::matrix<int, containers::vector<int>> mat2(std::move(mat1));
    containers::vector<int> vec;

    EXPECT_EQ(vec, mat1.getBuf());
    EXPECT_EQ(row, mat2.getRows());
    EXPECT_EQ(col, mat2.getCols());
    EXPECT_EQ(vec_init, mat2.getBuf());

    MyTypes::matrix<int, containers::vector<int>> mat3;
    mat3 = std::move(mat2);

    EXPECT_EQ(vec, mat2.getBuf());
    EXPECT_EQ(row, mat3.getRows());
    EXPECT_EQ(col, mat3.getCols());
    EXPECT_EQ(vec_init, mat3.getBuf());
}

TEST(CTORS_TEST, COPY_CTORS)
{
    constexpr s_t ROWS = 2;
    constexpr s_t COLS = 3;

    MyTypes::matrix<int, containers::vector<int>> mat1(ROWS, COLS, {1, 2, 3, 4, 5, 6});

    MyTypes::matrix<int, containers::vector<int>> mat2(mat1);
    EXPECT_EQ(mat1.getRows(), mat2.getRows());
    EXPECT_EQ(mat1.getCols(), mat2.getCols());
    EXPECT_EQ(mat1.getBuf(), mat2.getBuf());

    MyTypes::matrix<int, containers::vector<int>> mat3;
    mat3 = mat1;
    EXPECT_EQ(mat1.getRows(), mat3.getRows());
    EXPECT_EQ(mat1.getCols(), mat3.getCols());
    EXPECT_EQ(mat1.getBuf(), mat3.getBuf());
}


TEST(OPERATIONS, TRANSPOSE)
{
    constexpr s_t ROWS = 2;
    constexpr s_t COLS = 3;

    MyTypes::matrix<int, containers::vector<int>> mat1(ROWS, COLS, {1, 2, 3, 4, 5, 6});
    mat1.transpose();

    EXPECT_EQ(COLS, mat1.getRows());
    EXPECT_EQ(ROWS, mat1.getCols());
    
}

TEST(OPERATIONS, SPLICE)
{
    constexpr s_t ROWS = 2;
    constexpr s_t COLS = 3;

    MyTypes::matrix<int, containers::vector<int>> mat1(ROWS, COLS, {1, 2, 3, 4, 5, 6});
    MyTypes::matrix<int, containers::vector<int>> mat2(ROWS-1, COLS-1, {5, 6});
    MyTypes::matrix<int, containers::vector<int>> mat3 = mat1.splice(1, 1);

    //EXPECT_EQ(true, mat2 == mat3);
    EXPECT_EQ(mat2, mat3);

}

TEST(OPERATIONS, DETERMINANTE)
{
    MyTypes::matrix<int, containers::vector<int>> mat1(3, 3, {13, 3, 4, 43, 76, 3, 4, 4, 3});

    int det = mat1.determinante();

    EXPECT_EQ(1929, det);
}

TEST(M_OPERATIONS, SUM)
{
    MyTypes::matrix<int, containers::vector<int>> mat1(2, 2, {1, 1, 1, 1});
    MyTypes::matrix<int, containers::vector<int>> mat2(2, 2, {1, 1, 1, 1});
    MyTypes::matrix<int, containers::vector<int>> mat3(2, 2, {2, 2, 2, 2});

    MyTypes::matrix<int, containers::vector<int>> res = mat1 + mat2;

    EXPECT_EQ(true, res == mat3);
}

TEST(M_OPERATIONS, MULT)
{
    MyTypes::matrix<int, containers::vector<int>> mat1(1, 2, {2, 4});
    MyTypes::matrix<int, containers::vector<int>> mat2(2, 1, {1, 9});
    MyTypes::matrix<int, containers::vector<int>> mat3(1, 1, {38});

    MyTypes::matrix<int, containers::vector<int>> res = mat1 * mat2;

    EXPECT_EQ(true, res == mat3);
}

int main(int argc, char* argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return ::RUN_ALL_TESTS();
}
