#include <iostream>
#include <vector>
#include <cmath>
#include <numeric>
#include <algorithm>

std::vector<double> normalize(const std::vector<double> &vec)
{
    if (vec.empty())
    {
        return {};
    }

    double sum = std::accumulate(vec.begin(), vec.end(), 0.0);
    double mean = sum / vec.size();

    std::vector<double> diff(vec.size());
    std::transform(vec.begin(), vec.end(), diff.begin(),
                   [mean](double x)
                   { return x - mean; });

    double sq_sum = std::inner_product(diff.begin(), diff.end(), diff.begin(), 0.0);
    double stdev = std::sqrt(sq_sum / vec.size());

    std::vector<double> normalized(vec.size());
    std::transform(diff.begin(), diff.end(), normalized.begin(),
                   [stdev](double x)
                   { return x / stdev; });

    return normalized;
}