#include <iostream>
#include <curl/curl.h>
#include <map>
#include <request.hpp>
#include <string>
#include <unordered_map>
#include "json.hpp"
#include <utils.hpp>
#include <thread>
#include <vector>
#include <mutex>

static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
    ((std::string *)userp)->append((char *)contents, size * nmemb);
    return size * nmemb;
}

std::mutex mtx;

void processSymbol(const std::string &symbol)
{
    std::string qty = "1";
    std::string side = "buy";
    std::string type = "market";
    std::string time_in_force = "gtc";

    json response = get_historical(symbol, "2024-01-05T09:30:00-04:00", "2024-07-05T16:00:00-04:00", "1Day");
    auto response2 = get_historical(symbol, "2015-01-05T09:30:00-04:00", "2024-07-05T16:00:00-04:00", "12Month");

    auto bars_json2 = response2["bars"][symbol];
    std::vector<double> bars2(bars_json2.size());
    for (int i = 0; i < bars_json2.size(); i++)
    {
        bars2[i] = bars_json2[i]["c"];
    }

    auto std_dev_prices_historical = calculateStandardDeviation(bars2);

    {
        std::lock_guard<std::mutex> lock(mtx);
        std::cout << "Symbol: " << symbol << std::endl;
        std::cout << "Standard Deviation of Prices: " << std_dev_prices_historical << std::endl;
    }

    if (response.find("error") != response.end())
    {
        std::lock_guard<std::mutex> lock(mtx);
        std::cout << "Error for " << symbol << ": " << response["error"]["message"] << std::endl;
        return;
    }

    auto bars_json = response["bars"][symbol];
    std::vector<double> bars(bars_json.size());
    for (int i = 0; i < bars_json.size(); i++)
    {
        bars[i] = bars_json[i]["c"];
    }

    auto sma_bars = simple_moving_average(bars, 7);
    auto normalized_sma_bars = normalize(sma_bars);
    auto normalized_slope = calculate_slope(sma_bars);
    auto slope = calculate_slope(bars);

    bool isNeutralBullish = isNeutralBullishTrend(normalized_slope);

    {
        std::lock_guard<std::mutex> lock(mtx);
        std::cout << "Symbol: " << symbol << std::endl;
        std::cout << "Is Neutral Bullish: " << isNeutralBullish << std::endl;
        if (isNeutralBullish)
        {
            std::cout << "Neutral Bullish Trend Detected" << std::endl;
        }
        else
        {
            std::cout << "Neutral Bullish Trend Not Detected" << std::endl;
            return;
        }
    }

    double std_dev = calculateStandardDeviation(normalized_slope);
    double std_dev_prices = calculateStandardDeviation(bars);
    double meanSlope = std::accumulate(normalized_slope.begin(), normalized_slope.end(), 0.0) / normalized_slope.size();

    double strike = bars[bars.size() - 1] + ((meanSlope + 0.15 * std_dev) * 40);

    double time_to_expiration = 60;
    double spot = bars[bars.size() - 1];
    double risk_free_rate = 4.29;
    double vol = std_dev_prices_historical / spot;

    BlackScholes call(1, spot, strike, risk_free_rate, vol, time_to_expiration);
    double call_price = call.Price();

    {
        std::lock_guard<std::mutex> lock(mtx);
        std::cout << "Symbol: " << symbol << std::endl;
        std::cout << "Standard Deviation: " << std_dev << std::endl;
        std::cout << "Mean Slope: " << meanSlope << std::endl;
        std::cout << "Last Stock Price: " << spot << std::endl;
        std::cout << "Strike: " << strike << std::endl;
        std::cout << "Volatility: " << vol << std::endl;
        std::cout << "Call Price: " << call_price << std::endl;
        std::cout << "------------------------" << std::endl;
    }
}

int main()
{
    std::string url = "https://paper-api.alpaca.markets/v2/positions";
    std::map<std::string, std::string> arguments = {{"exchange", "NYSE"}};
    std::string method = "GET";

    std::cout << "Making HTTP request to: " << url << std::endl;

    json response = makeHttpRequest(url, arguments, method);
    std::cout << "Response: " << response.dump(4) << std::endl;

    // List of energy sector symbols to process
    std::vector<std::string> symbols = {"XOM", "CVX", "COP", "EOG", "SLB", "PXD", "MPC", "VLO", "PSX", "OXY"};

    std::vector<std::thread> threads;
    for (const auto &symbol : symbols)
    {
        threads.emplace_back(processSymbol, symbol);
    }

    for (auto &thread : threads)
    {
        thread.join();
    }

    return 0;
}
