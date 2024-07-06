#include <iostream>
#include <vector>

std::vector<double> rolling_slope(const std::vector<double> &arr, int windowSize)
{
    std::vector<double> slopes;

    if (arr.empty() || windowSize <= 1 || windowSize > arr.size())
    {
        return slopes;
    }

    for (int i = 0; i <= arr.size() - windowSize; ++i)
    {
        double sumX = 0, sumY = 0, sumXY = 0, sumXX = 0;
        for (int j = 0; j < windowSize; ++j)
        {
            sumX += j;
            sumY += arr[i + j];
            sumXY += j * arr[i + j];
            sumXX += j * j;
        }

        double slope = (windowSize * sumXY - sumX * sumY) / (windowSize * sumXX - sumX * sumX);
        slopes.push_back(slope);
    }

    return slopes;
}