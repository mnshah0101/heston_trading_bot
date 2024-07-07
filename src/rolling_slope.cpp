#include <iostream>
#include <vector>

std::vector<double> calculate_slope(const std::vector<double> &arr)
{
    std::vector<double> slopes;

    if (arr.empty())
    {
        return slopes;
    }

    for (int i = 1; i < arr.size(); i++)
    {
        slopes.push_back(arr[i] - arr[i - 1]);
    }

    return slopes;
}