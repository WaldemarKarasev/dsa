#include <iostream>
#include <vector>
#include <map>
#include <string>

void duplicate()
{
    std::vector<int> arr;
    std::map<int, int> map;
    std::string str = "hello";
    for(auto i : str)
    {
        std::cout << i << " ";
    }
}

template <typename T>
using iter = typename std::vector<T>::iterator;

int peak_1d_ver1(std::vector<int>& arr)
{
    int peak = 0;

    for(int i = 0; i < arr.size(); ++i)
    {

    }

    return peak;
}

int peak_1d_ver2(std::vector<int>& arr)
{
    int peak = 0;

    return peak;
}

int main()
{
    std::vector<int> arr = {10, 13, 5, 8, 3, 2, 1};
    std::cout << "peak_ver1 of arr: " << peak_1d_ver1(arr) << std::endl;
    std::cout << "peak_ver2 of arr: " << peak_1d_ver2(arr) << std::endl; 
    duplicate();   
}