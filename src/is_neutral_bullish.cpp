
#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>

bool isNeutralBullishTrend(const std::vector<double> &slopes)
{
    if (slopes.empty())
    {
        return false;
    }

    double sum = std::accumulate(slopes.begin(), slopes.end(), 0.0);
    double meanSlope = sum / slopes.size();

    double positiveSlopeThreshold = 0.01; 
    double slopeMaximalThreshold = 0.2;
    double volatilityThreshold = 0.7;

    std::cout << "Mean slope: " << meanSlope << std::endl;

    if (meanSlope < positiveSlopeThreshold)
    {
        std::cout << "Mean slope is less than " << positiveSlopeThreshold << std::endl;





        return false;
    }

    double sq_sum = std::inner_product(slopes.begin(), slopes.end(), slopes.begin(), 0.0);
    double stdev = std::sqrt(sq_sum / slopes.size() - meanSlope * meanSlope);

    if (stdev > volatilityThreshold)
    {
        std::cout << "Volatility is greater than " << volatilityThreshold << std::endl;
        std::cout << "Volatility: " << stdev << std::endl;
        return false;
    }



    if (meanSlope > slopeMaximalThreshold)
    {
        std::cout << "Mean slope is greater than " << slopeMaximalThreshold << std::endl;
        std::cout << "Mean slope: " << meanSlope << std::endl;
        return false;
    }

    int positiveSlopeCount = std::count_if(slopes.begin(), slopes.end(), [](double slope)
                                           { return slope > 0; });
    double positiveSlopeRatio = static_cast<double>(positiveSlopeCount) / slopes.size();

    if (positiveSlopeRatio < 0.45)
    
    { 
        std::cout << "Positive slope ratio is less than 0.5" << std::endl;
        std::cout << "Positive slope ratio: " << positiveSlopeRatio << std::endl;
        return false;
    }

    return true;
}