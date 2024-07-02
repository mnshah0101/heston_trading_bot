// a function to create an order


#include <iostream>
#include <curl/curl.h>
#include <map>
#include <request.hpp>
#include <string>
#include <unordered_map>
#include "json.hpp"



json create_trade(const std::string &symbol, const std::string &qty, const std::string &side, const std::string &type, const std::string &time_in_force)
{
    std::string url = "https://paper-api.alpaca.markets/v2/orders";
    std::map<std::string, std::string> arguments = {{"symbol", symbol}, {"qty", qty}, {"side", side}, {"type", type}, {"time_in_force", time_in_force}};
    std::string method = "POST";

    std::cout << "Making HTTP request to: " << url << std::endl;

    json response = makeHttpRequest(url, arguments, method);

    return response;
}


