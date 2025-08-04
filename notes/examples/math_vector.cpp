#include <iostream>
#include <cmath>
#include <array>
#include <sstream>
#include <algorithm>
#include <vector>
#include <type_traits>

template <typename T, std::size_t sz = 3>
class Vec
{
public:
    using size_type = std::size_t;
    using data_type = T;
    using container_type = std::array<T, sz>;

public:

    Vec() = default;
    Vec(container_type data) : data_{std::move(data)} {}
    Vec(std::initializer_list<data_type> list) 
    {
        if (list.size() == sz)
        {
            std::copy(list.begin(), list.end(), data_.begin());
        }
    }

    Vec operator-(const Vec& other)
    {
        Vec p;
        for (std::size_t i = 0; i < data_.size(); ++i)
        {
            p.data_[i] = data_[i] - other.data_[i];
        }
        return p;
    }

    Vec operator+(const Vec& other)
    {
        Vec p;
        for (std::size_t i = 0; i < data_.size(); ++i)
        {
            p.data_[i] = data_[i] + other.data_[i];
        }
        return p;
    }

    data_type norm() const 
    {
        if constexpr (std::is_arithmetic_v<data_type>)
        {
            return std::sqrt(dot(*this, *this));
        }

        return {};
    }

    Vec normilize() const 
    {
        Vec vec{data_};
        data_type n = norm();
        
        for (int i = 0; i < vec.dimensions(); ++i)
        {
            vec[i] = vec[i] / n;
        }

        return vec;
    }

    void scale(data_type scale)
    {
        for (int i = 0; i < data_.size(); ++i)
        {
            data_[i] = data_[i] * scale;
        }
    }

    static data_type dot(const Vec& left, const Vec& right) 
    {
        data_type acc{};

        if (left.dimensions() == right.dimensions())
        {
            for (std::size_t i = 0; i < left.dimensions(); ++i)
            {
                acc += left[i] * right[i];
            }
            // std::cout << "acc=" << acc << std::endl;
            return acc;
        }

        return acc;
    }

    data_type& operator[](size_type i) { return data_[i]; }
    const data_type& operator[](size_type i) const { return data_[i]; }

    size_type dimensions() const { return data_.size(); }



    void print() const
    {
        std::stringstream stream;
        stream << "Vec( "; 
        
        for (const auto& elem : data_)
        {
            stream << elem << " ";
        }

        stream << ")";

        std::cout << stream.str() << std::endl;
        // std::cout << "Point(" << x << ", " << y << ", " << z << ")" << std::endl;
    }

private:
    container_type data_;
};

template <typename Vec>
typename Vec::data_type dot(Vec left, Vec right)
{
    return Vec::dot(left, right);
}

template <typename Vec>
Vec proj(Vec v, Vec dir)
{
    typename Vec::data_type scale = Vec::dot(v, dir) / Vec::dot(dir, dir);

    // std::cout << scale << std::endl;
    dir.scale(scale);
    return dir;
}

int main(int argc, char const *argv[])
{
    Vec<double, 5> a1{2, 0, -1, -2, 0};
    Vec<double, 5> a2{0, -2, 2, 2, -2};
    Vec<double, 5> a3{1, -1, 0, 1, -1};

    auto b2 = a2 - proj(a2, a1) - proj(a2, a3);

    auto e1 = a1.normilize();
    auto e3 = a3.normilize();
    // double acc
    // for (int i = 0; i < e1.dimensions(); ++i)
    // {
    //     std::cout << e1[i] * e3[i] << std::endl;
    // }

    // b2.normilize().print();
    // std::cout << a1.norm() << std::endl;
    // std::cout << a3.norm() << std::endl;
    std::cout << dot(a1.normilize(), a3.normilize()) << std::endl;
    std::cout << dot(a1, b2.normilize()) << std::endl;
    b2.normilize().print();
}
