#pragma once

// std
#include <vector>

namespace lib::algo::sort
{
    
inline void dutch_national_flag_problem(std::vector<int>& colors)
{
    int mid = 0;
    int low = 0;
    int high = colors.size() - 1;

    while (mid <= high)
    {
        int color = colors[mid];

        switch (color)
        {
        case 0:
            std::swap(colors[low], colors[mid]);
            mid++; low++;
            break;
        case 1:
            mid++;
            break;

        case 2:
            std::swap(colors[mid], colors[high]);
            high--;
            break;

        default:
            return;
            break;
        }
    }

}

} // namespace lib::algo::sort
