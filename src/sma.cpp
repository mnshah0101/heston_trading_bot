#include <iostream>
#include <vector>

std::vector<double>
simple_moving_average(const std::vector<double> &arr, int windowSize)
{
    std::vector<double> movingAverages;

    if (arr.empty() || windowSize <= 0 || windowSize > arr.size())
    {
        return movingAverages;
    }

    double windowSum = 0;
    for (int i = 0; i < windowSize; ++i)
    {
        windowSum += arr[i];
    }
    movingAverages.push_back(windowSum / windowSize);

    for (int i = windowSize; i < arr.size(); ++i)
    {
        windowSum += arr[i] - arr[i - windowSize];
        movingAverages.push_back(windowSum / windowSize);
    }

    return movingAverages;
}