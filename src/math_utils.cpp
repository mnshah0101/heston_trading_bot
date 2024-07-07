#include <iostream>
#include <vector>
#include <cmath>
#include <numeric>

// Function to calculate the standard deviation of a vector of doubles
double calculateStandardDeviation(const std::vector<double> &data)
{
    if (data.empty())
    {
        return 0.0;
    }

    // Calculate the mean
    double mean = std::accumulate(data.begin(), data.end(), 0.0) / data.size();

    // Calculate the squared differences from the mean
    double squared_diff_sum = 0.0;
    for (const auto &value : data)
    {
        squared_diff_sum += (value - mean) * (value - mean);
    }

    // Calculate the variance
    double variance = squared_diff_sum / data.size();

    // Calculate and return the standard deviation
    return std::sqrt(variance);
}