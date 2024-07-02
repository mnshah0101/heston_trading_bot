#include <iostream>
#include <curl/curl.h>
#include <map>
#include <request.hpp>
#include <string>
#include <unordered_map>
#include "json.hpp"
#include <create_order.hpp>





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

    

    std::string symbol = "AAPL";
    std::string qty = "1";
    std::string side = "buy";
    std::string type = "market";
    std::string time_in_force = "gtc";

    response = create_trade(symbol, qty, side, type, time_in_force);

    std::cout << "Response: " << response.dump(4) << std::endl;




        return 0;
}

