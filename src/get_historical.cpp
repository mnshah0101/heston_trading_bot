#include <iostream>
#include <curl/curl.h>
#include <map>
#include <request.hpp>
#include <string>
#include <unordered_map>
#include "json.hpp"



json get_historical(const std::string &symbol, const std::string &start, const std::string &end, const std::string &timeframe)
{
    std::string url = "https://data.alpaca.markets/v2/stocks/bars" ;
    std::map<std::string, std::string> arguments = { {"symbols", symbol}, {"start", start}, {"end", end}, {"timeframe", timeframe }};
    std::string method = "GET";

    std::cout << "Making HTTP request to: " << url << std::endl;

    json response = makeHttpRequest(url, arguments, method);









    return response;
}