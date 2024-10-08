#include <gtest/gtest.h>

#include <lib/containers/vector.hpp>
#include <lib/types/matrix.hpp>

using s_t =lib::matrix<int, lib::containers::vector<int>>::size_type; // ???

template <typename T, typename data_buf = lib::containers::vector<T>>
using matrix = lib::matrix<T, data_buf>;

template <typename T>
using vector = lib::containers::vector<T>;

TEST(OPERATORS, EQUAL)
{
    matrix<int, vector<int>> mat1(3, 2, {1, 2, 3, 4, 5, 6});
    matrix<int, vector<int>> mat2(3, 2, {1, 2, 3, 4, 5, 6});
    matrix<int, vector<int>> mat3(3, 2, {1, 1, 1, 1, 1, 1});
    matrix<int, vector<int>> mat4(2, 3, {1, 2, 3, 4, 5, 6});

    EXPECT_EQ(true,  mat1 == mat2);
    EXPECT_EQ(false, mat1 == mat3);
    EXPECT_EQ(false, mat1 == mat4);
}

TEST(CTORS, DEFAULT_CTOR)
{
    matrix<int, vector<int>> mat;
    vector<int> vec;
    EXPECT_EQ(0, mat.getRows());
    EXPECT_EQ(0, mat.getCols());
    EXPECT_EQ(vec, mat.getBuf());
}

TEST(CTORS, RCV_CTOR)
{
    constexpr s_t ROWS = 2;
    constexpr s_t COLS = 3;

    matrix<int, vector<int>> mat1(ROWS, COLS);
    vector<int> vec1(ROWS * COLS);
    EXPECT_EQ(ROWS, mat1.getRows());
    EXPECT_EQ(COLS, mat1.getCols());
    EXPECT_EQ(vec1, mat1.getBuf());

    matrix<int, vector<int>> mat2(ROWS, COLS, {1, 2, 3, 4, 5, 6});
    vector<int> vec2{1, 2, 3, 4, 5, 6};
    EXPECT_EQ(vec2, mat2.getBuf());
}

TEST(CTORS_TEST, MOVE_CTORS)
{
    constexpr s_t ROWS = 2;
    constexpr s_t COLS = 3;

    matrix<int, vector<int>> mat1(ROWS, COLS, {1, 2, 3, 4, 5, 6});

    s_t row = mat1.getRows();
    s_t col = mat1.getCols();
    vector<int> vec_init = mat1.getBuf();

    matrix<int, vector<int>> mat2(std::move(mat1));
    vector<int> vec;

    EXPECT_EQ(vec, mat1.getBuf());
    EXPECT_EQ(row, mat2.getRows());
    EXPECT_EQ(col, mat2.getCols());
    EXPECT_EQ(vec_init, mat2.getBuf());

    matrix<int, vector<int>> mat3;
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

    matrix<int, vector<int>> mat1(ROWS, COLS, {1, 2, 3, 4, 5, 6});

    matrix<int, vector<int>> mat2(mat1);
    EXPECT_EQ(mat1.getRows(), mat2.getRows());
    EXPECT_EQ(mat1.getCols(), mat2.getCols());
    EXPECT_EQ(mat1.getBuf(), mat2.getBuf());

    matrix<int, vector<int>> mat3;
    mat3 = mat1;
    EXPECT_EQ(mat1.getRows(), mat3.getRows());
    EXPECT_EQ(mat1.getCols(), mat3.getCols());
    EXPECT_EQ(mat1.getBuf(), mat3.getBuf());
}


TEST(OPERATIONS, TRANSPOSE)
{
    constexpr s_t ROWS = 2;
    constexpr s_t COLS = 3;

    matrix<int, vector<int>> mat1(ROWS, COLS, {1, 2, 3, 4, 5, 6});
    mat1.transpose();

    EXPECT_EQ(COLS, mat1.getRows());
    EXPECT_EQ(ROWS, mat1.getCols());
    
}

TEST(OPERATIONS, SPLICE)
{
    constexpr s_t ROWS = 2;
    constexpr s_t COLS = 3;

    matrix<int, vector<int>> mat1(ROWS, COLS, {1, 2, 3, 4, 5, 6});
    matrix<int, vector<int>> mat2(ROWS-1, COLS-1, {5, 6});
    matrix<int, vector<int>> mat3 = mat1.splice(1, 1);

    //EXPECT_EQ(true, mat2 == mat3);
    EXPECT_EQ(mat2, mat3);

}

TEST(OPERATIONS, DETERMINANTE)
{
    matrix<int, vector<int>> mat1(3, 3, {13, 3, 4, 43, 76, 3, 4, 4, 3});

    int det = mat1.determinante();

    EXPECT_EQ(1929, det);
}

TEST(M_OPERATIONS, SUM)
{
    matrix<int, vector<int>> mat1(2, 2, {1, 1, 1, 1});
    matrix<int, vector<int>> mat2(2, 2, {1, 1, 1, 1});
    matrix<int, vector<int>> mat3(2, 2, {2, 2, 2, 2});

    matrix<int, vector<int>> res = mat1 + mat2;

    EXPECT_EQ(true, res == mat3);
}

TEST(M_OPERATIONS, MULT)
{
    matrix<int, vector<int>> mat1(1, 2, {2, 4});
    matrix<int, vector<int>> mat2(2, 1, {1, 9});
    matrix<int, vector<int>> mat3(1, 1, {38});

    matrix<int, vector<int>> res = mat1 * mat2;

    EXPECT_EQ(true, res == mat3);
}

int main(int argc, char* argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return ::RUN_ALL_TESTS();
}
