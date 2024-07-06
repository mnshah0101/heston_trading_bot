#include <iostream>
#include <curl/curl.h>
#include <map>
#include <request.hpp>
#include <string>
#include <unordered_map>
#include "json.hpp"

#include <utils.hpp>









static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
    ((std::string *)userp)->append((char *)contents, size * nmemb);
    return size * nmemb;
}

int main(){

    std::string url = "https://paper-api.alpaca.markets/v2/positions";
    std::map<std::string, std::string> arguments = {{"exchange", "NYSE"}};
    std::string method = "GET";


    std::cout << "Making HTTP request to: " << url << std::endl;

    json response = makeHttpRequest(url, arguments, method);




    std::cout << "Response: " << response.dump(4) << std::endl;

    

    std::string symbol = "FIS";
    std::string qty = "1";
    std::string side = "buy";
    std::string type = "market";
    std::string time_in_force = "gtc";

    response = create_trade(symbol, qty, side, type, time_in_force);





    std::cout << "Response: " << response.dump(4) << std::endl;

    response = get_historical(symbol, "2024-03-01T09:30:00-04:00", "2024-07-05T16:00:00-04:00", "1Day");

    if (response.find("error") != response.end())
    {
        std::cout << "Error: " << response["error"]["message"] << std::endl;
    }
    else
    {
        std::cout << "Response: " << response.dump(4) << std::endl;
    }

    auto bars_json = response["bars"][symbol];


    

    std::vector<double> bars(bars_json.size());

    for(int i = 0; i < bars_json.size(); i++){
        bars[i] = bars_json[i]["c"];
    }


 

    auto sma_bars = simple_moving_average(bars, 7);

    for(int i = 0; i < sma_bars.size(); i++){
        std::cout << sma_bars[i] << std::endl;
    }

    auto normalized_sma_bars = normalize(sma_bars);


    auto normalized_slope = rolling_slope(sma_bars, 7);
    auto slope = rolling_slope(bars, 7);



    for (int i = 0; i < normalized_slope.size(); i++)
    {
        std::cout << normalized_slope[i] << std::endl;
    }

    bool isNeutralBullish = isNeutralBullishTrend(normalized_slope);

    std::cout << "Is Neutral Bullish: " << isNeutralBullish << std::endl;


    if(isNeutralBullish){
        std::cout << "Neutral Bullish Trend Detected" << std::endl;
    }else{
        std::cout << "Neutral Bullish Trend Not Detected" << std::endl;
        return 0;
    }


    double std_slope = std::accumulate(slope.begin(), slope.end(), 0.0) / slope.size();

    double strike = bars[bars.size() - 1] * ((1 + std_slope)*0.95);




    std::cout << "Last Stock Price: " << bars[bars.size() - 1] << std::endl;
    

    std::cout << "Strike: " << strike << std::endl;

    double  profit_if_excercised;
    double profit_if_not_excercised;

    double time_to_expiration = 1/12;

    double spot = bars[bars.size() - 1];
    double risk_free_rate = 0.0429;
    double vol = 0.7;

    double call_price, put_price;
    black_scholes_pricer(spot, strike, time_to_expiration, risk_free_rate, vol, &call_price, &put_price);
    printf("Call Price: %.2f\n", call_price);
    printf("Put Price: %.2f\n", put_price);

    double profit_if_exercised, profit_if_not_exercised;
    covered_call(spot, strike, time_to_expiration, risk_free_rate, vol, &profit_if_exercised, &profit_if_not_exercised);
    printf("Profit if Exercised: %.2f\n", profit_if_exercised);
    printf("Profit if Not Exercised: %.2f\n", profit_if_not_exercised);

    return 0;
}

