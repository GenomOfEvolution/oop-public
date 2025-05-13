#pragma once
#include <vector>

template <typename T, typename Less>
bool FindMax(std::vector<T> const& arr, T& maxValue, Less const& less)
{
    if (arr.empty())
    {
        return false;
    }

    auto it = std::max_element(arr.begin(), arr.end(), less);
    maxValue = *it; 

    return true;
}