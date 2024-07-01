#include <iostream>
#include <curl/curl.h>
#include <map>
#include <request.hpp>

static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
    ((std::string *)userp)->append((char *)contents, size * nmemb);
    return size * nmemb;
}

int main(){
    std::string url = "http://www.example.com";
std::map<std::string, std::string> arguments = {{"param1", "value1"}, {"param2", "value2"}};
std::string method = "GET"; // or "POST"

std::string response = makeHttpRequest(url, arguments, method);
std::cout << "Response: " << response << std::endl;

    
    
    return 0;
}

