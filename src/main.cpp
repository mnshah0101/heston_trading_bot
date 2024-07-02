#include <iostream>
#include <curl/curl.h>
#include <map>
#include <request.hpp>
#include <string>
#include <unordered_map>





static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
    ((std::string *)userp)->append((char *)contents, size * nmemb);
    return size * nmemb;
}

int main(){

    std::string url = "https://paper-api.alpaca.markets/v2/assets";
    std::map<std::string, std::string> arguments = {{"exchange", "NYSE"}};
    std::string method = "GET"; // or "POST"


    std::cout << "Making HTTP request to: " << url << std::endl;

    std::string response = makeHttpRequest(url, arguments, method);

    std::cout << "Response: " << response << std::endl;

    
    
    return 0;
}

