#ifndef MATRIX_H
#define MATRIX_H

#include <cstddef>
#include <initializer_list>
#include <type_traits>

#define MY_DEBUG
#include <lib/utility.hpp>
#include <lib/containers/vector.hpp>

namespace lib
{
    template <typename T, typename data_buf = containers::vector<T>>
    class matrix
    {
        static_assert(std::is_nothrow_move_constructible<T>::value ||
                std::is_copy_constructible<T>::value, 
                "T should be copy constructible or nothrow moveble.");
    public:
        using size_type = size_t;

    private:
        size_type m_rows_ = 0;
        size_type m_cols_ = 0;
        data_buf  m_buf_;

    public:
        matrix() = default;
        matrix(size_type rows, size_type cols);
        matrix(size_type rows, size_type cols, T num);
        matrix(size_type rows, size_type cols, std::initializer_list<T> list);
        /**
         * copy semantics
        */
        matrix(const matrix& mat) = default;
        matrix& operator=(const matrix& mat) = default;

        /**
         * move semantics
        */
        matrix(matrix&& mat) noexcept = default;
        matrix& operator=(matrix&& mat) noexcept = default;

        ~matrix()
        { 
            DEBUG_PRINT("matrix::dtor()");
        };

        size_type getRows() const noexcept { return m_rows_; }
        size_type getCols() const noexcept { return m_cols_; }
        data_buf getBuf()  const noexcept { return m_buf_;  }
        
    /**
     * operator [][]
    */
    public:
        struct ProxyRow // in future this struct should be private for class invariant protection purpose.
        {
            T* row;
            ProxyRow(T* data) : row(data) {}
            const T& operator[](size_type i) const   { return row[i]; }
            T& operator[](size_type i)               { return row[i]; }
            T& getElemInRow(size_type i)             { return row[i]; }
            const T& getElemInRow(size_type i) const { return row[i]; }
        };

        ProxyRow operator[](size_type i) { return ProxyRow(m_buf_.data() + i * m_cols_/*m_data_ + i * m_cols_*/); }
        const ProxyRow operator[](size_type i) const { return ProxyRow(m_buf_.data() + i * m_cols_/*m_data_ + i * m_cols_*/); }

        ProxyRow getRow(size_type i) noexcept             { return ProxyRow(m_buf_.data() + i * m_cols_ /*m_data_ + i * m_cols_*/); }
        const ProxyRow getRow(size_type i) const noexcept { return ProxyRow(m_buf_.data() + i * m_cols_/*m_data_ + i * m_cols_*/); }

        struct ProxyCol
        {
            T* col;
            size_type col_size;
            size_type step;
            ProxyCol(T* data, size_type size, size_type step) : col(data), col_size(size), step(step){}
            T& getElemInCol(size_type i) { return *(col + i*step); }
            const T& getElemInCol(size_type i) const { return *(col + i*step); }
        };

        ProxyCol getCol(size_type i) noexcept             { return ProxyCol(m_buf_.data() + i/*m_data_ + i*/, m_rows_, m_cols_); }
        const ProxyCol getCol(size_type i) const noexcept { return ProxyCol(m_buf_.data() + i/*m_data_ + i*/, m_rows_, m_cols_); }

    /**
     * scalar operations
    */
    // in future updates

    /**
     * bool functions
    */
    bool equal(const matrix& other) const noexcept;
    bool operator==(const matrix& other) const noexcept { return equal(other); };
    bool operator!=(const matrix& other) const noexcept{return !operator==(other);}
    
    void transpose() &;
    //matrix transposeFrom(const matrix& mat);
    matrix splice(size_type exclRow, size_type exclCol) const;
    T determinante() const;

    /**
     * output func
    */
    void dump(std::ostream& os) const;

    /**
     * static functions - static constructors
    */
    static matrix eye(size_type rows, size_type cols);

    public:
        matrix operator+=(const matrix& rhs);
        matrix& operator*=(const matrix& rhs);
    
    private:
        T dotProduct(ProxyRow& tmpRow, ProxyCol& tmpCol);


    };
    
    template <typename T, typename data_buf>
    matrix<T, data_buf>::matrix(size_type rows, size_type cols)
    : m_rows_(rows), m_cols_(cols), m_buf_(m_rows_*m_cols_)
    {
        DEBUG_PRINT("empty constructor with rows, cols");
    }

    template <typename T, typename data_buf>
    matrix<T, data_buf>::matrix(size_type rows, size_type cols, T num)
    : m_rows_(rows), m_cols_(cols), m_buf_(m_rows_*m_cols_, num)
    {
        DEBUG_PRINT("fill constructor");
    }

    template <typename T, typename data_buf>
    matrix<T, data_buf>::matrix(size_type rows, size_type cols, std::initializer_list<T> list)
    : m_rows_(rows), m_cols_(cols), m_buf_(list)
    {
        DEBUG_PRINT("matrix(std::initializer_list list)");        
    }

    template <typename T, typename data_buf>
    bool matrix<T, data_buf>::equal(const matrix<T, data_buf>& other) const noexcept
    {
        DEBUG_PRINT("matrix::equal()");
        if(m_rows_ != other.m_rows_ || m_cols_ != other.m_cols_)
        {
            DEBUG_PRINT("rows != other.rows || cols != other.cols");
            return false;
        }
        if(this == &other)
        {
            DEBUG_PRINT("this == &other");
            return true;
        }

        if(m_buf_ == other.m_buf_)
        {
            DEBUG_PRINT("buf == other.buf")
            return true;
        }
        
        return false;
    }


    template <typename T, typename data_buf>
    void matrix<T, data_buf>::transpose() &
    {
        // create matrix with reverse rows and columns
        matrix<T, data_buf> ret(m_cols_, m_rows_);
        for(size_type i = 0; i < m_rows_; ++i)
        {
            for (size_type j = 0; j < m_cols_; ++j)
            {
                ret[j][i] = operator[](i).operator[](j);
            }
        }
        
        *this = std::move(ret);
    }

    template <typename T, typename data_buf>
    matrix<T, data_buf> matrix<T, data_buf>::splice(size_type exclRow, size_type exclCol) const
    {
        exclRow--;
        exclCol--;

        matrix<T, data_buf> ret(m_rows_ - 1, m_cols_ - 1);

        size_type rowOffset = 0;
        size_type colOffset = 0;

        for (size_type i = 0; i < ret.m_rows_; ++i)
        {
            if(i == exclRow)
                rowOffset=1;

            for (size_type j = 0; j < ret.m_cols_; ++j)
            {
                if(j == exclCol)
                    colOffset=1;

                ret[i][j] = operator[](i + rowOffset).operator[](j + colOffset);
            }
            
        }
        
        return ret;
    }

    template <typename T, typename data_buf>
    T matrix<T, data_buf>::determinante() const 
    {
        DEBUG_PRINT("matrix::determinante()");
        if(m_rows_ != m_cols_) return 0;//??????

        // base cases
        if(m_rows_ == 1) return operator[](0).operator[](0); // don't check row because rows==cols

        int cofactotsign = 1;
        T ret = 0;

        for (size_type i = 0; i < m_cols_; ++i)
        {
            ret += cofactotsign * operator[](0).operator[](i) * splice(1, i + 1).determinante(); // need to thik about return value for splice to optimize numbers of copy ctors
            
            cofactotsign = -cofactotsign;
        }
        return ret;
    }

    template <typename T, typename data_buf>
    void matrix<T, data_buf>::dump(std::ostream& os) const
    {
        DEBUG_PRINT("matrix::dump()");
        for (size_type i = 0; i < m_rows_; ++i)
        {
            os << "|";
            for (size_type j = 0; j < m_cols_; ++j)
            {
                os << operator[](i).operator[](j);
                if(j != m_cols_ - 1) os << " ";
                else os << "";
            }
            os << "|\n";
        }
        
        
    }

    template <typename T, typename data_buf>
    matrix<T, data_buf> matrix<T, data_buf>::eye(size_type rows, size_type cols)
    {
        // break RVO
    #define RVO
    #if defined(RVO)
        DEBUG_PRINT("RVO eye")
        matrix<T, data_buf> mat(rows, cols, 1);
        return mat;
    
    #else
        // break RVO
        matrix<T> mat;
        mat.fill_mat(mat.m_data_, 1);
        return mat;
    
    #endif
    }
    
    template <typename T, typename data_buf>
    matrix<T, data_buf> matrix<T, data_buf>::operator+=(const matrix<T, data_buf>& rhs)
    {
        DEBUG_PRINT("operator+=()");
        if(m_cols_ != rhs.m_cols_ || m_rows_ != rhs.m_rows_) 
        {
            DEBUG_PRINT("operator+=():not equals sizes");
            return *this;
        }

        for (size_type i = 0; i < m_buf_.size(); ++i)
        {
            m_buf_[i] += rhs.m_buf_[i];
        }

        return *this;        
    }


    template <typename T, typename data_buf>
    T matrix<T, data_buf>::dotProduct(ProxyRow& tmpRow, ProxyCol& tmpCol)
    {
        DEBUG_PRINT("dotProduct()")
        T ret = T();

        for(size_type i = 0; i < tmpCol.col_size; ++i)
        {
            T rowEl = tmpRow.getElemInRow(i);
            T colEl = tmpCol.getElemInCol(i);
            ret += rowEl*colEl;            
        }

        return ret; 
    }


    template <typename T, typename data_buf>
    matrix<T, data_buf>& matrix<T, data_buf>::operator*=(const matrix<T, data_buf>& rhs)
    {
        DEBUG_PRINT("operator*=()");
        if(m_cols_ != rhs.m_rows_)
        {
            DEBUG_PRINT("operator*=():now equal sizes");
            return *this;
        }

        matrix<T, data_buf> ret(m_rows_, rhs.m_cols_);
        
        for(size_type i = 0; i < ret.m_rows_; ++i) // row
        {
            size_type j;
            for( j = 0; j < ret.m_cols_; ++j) // column
            {
                ProxyRow tmpRow = getRow(i);
                ProxyCol tmpCol = rhs.getCol(j);
                T res = dotProduct(tmpRow, tmpCol);
                ret[i][j] = res;
            }
        }
        
        *this = std::move(ret);
        return *this;
    }   
}

namespace MyTypes
{
    template <typename T, typename data_buf>
    matrix<T, data_buf> operator+(const matrix<T, data_buf>& lhs, const matrix<T, data_buf>& rhs)
    {
        DEBUG_PRINT("binary operator+()");
        matrix<T, data_buf> ret = lhs;
        ret += rhs;
        return ret;
    }

    template <typename T, typename data_buf>
    matrix<T, data_buf> operator*(const matrix<T, data_buf>& lhs, const matrix<T, data_buf>& rhs)
    {
        DEBUG_PRINT("binary operator*()");
        matrix<T, data_buf> ret = lhs;
        ret *= rhs;
        return ret;
    }   
}

template <typename T, typename data_buf>
std::ostream& operator<<(std::ostream& os, const MyTypes::matrix<T, data_buf>& mat)
{
    mat.dump(os);
    return os;
}

template <typename T, typename data_buf>
bool operator==(const MyTypes::matrix<T, data_buf>& mat1, const MyTypes::matrix<T, data_buf>& mat2) noexcept
{
    return mat1.equal(mat2);
}

template <typename T, typename data_buf>
bool operator!=(const MyTypes::matrix<T, data_buf>& mat1, const MyTypes::matrix<T, data_buf>& mat2) noexcept
{
    return !mat1.equal(mat2);
}
#if 0
// class to ptinting matrix
namespace MyTypes
{
    template <typename T, typename data_buf, template<typename> class matrix>
    class printMat
    {
    public:
        static void printMAT(matrix<T, data_buf>& mat);
    };

    template <typename T, typename data_buf, template<typename, typename> class matrix>
    void printMat<T, data_buf, matrix>::printMAT(matrix<T, data_buf>& mat)
    {
        std::cout << std::endl;
        DEBUG_PRINT("mat.rows = " << mat.getRows() << " mat.cols = " << mat.getCols());
        #if 0
        for (typename matrix<T>::size_type i = 0; i < mat.getCols()*mat.getRows(); ++i)
        {
            if(i % mat.getCols() == 0 && i != 0) std::cout << std::endl;
            std::cout << mat.getData()[i] << " ";
        }
        #endif
        #if 1

        for (typename matrix<T, data_buf>::size_type i = 0; i < mat.getRows(); ++i)
        {
            for(typename matrix<T, data_buf>::size_type j = 0; j < mat.getCols(); ++j)
                std::cout << mat[i][j] << " ";

            std::cout << std::endl;
        }
        #endif
        std::cout << std::endl;
    }
}
#endif

#endif