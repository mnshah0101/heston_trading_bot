
#include <curl/curl.h>
#include <stddef.h>
#include <iostream>
#include <map>
#include <readenv.hpp>
#include <string>

static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
    ((std::string *)userp)->append((char *)contents, size * nmemb);
    return size * nmemb;
}

std::string makeHttpRequest(const std::string &url, const std::map<std::string, std::string> &arguments, const std::string &method)
{
    CURL *curl;
    CURLcode res;
    std::string readBuffer;

    std::unordered_map<std::string, std::string> env = readEnvFile(".env");

    std::string apiKeyId = env["ALPACA_API_KEY"];
    std::string apiSecretKey = env["ALPACA_SECRET_KEY"];

    std::cout << " API Key: " << apiKeyId << std::endl;
    std::cout << " API Secret Key: " << apiSecretKey << std::endl;




    std::cout << "Making HTTP request to: " << url << std::endl;




    // Initialize curl session
    curl = curl_easy_init();
    if (curl)
    {
        std::string fullUrl = url;
        std::string params;

        // Convert map to URL-encoded query string
        for (const auto &arg : arguments)
        {
            if (!params.empty())
            {
                params += "&";
            }
            params += curl_easy_escape(curl, arg.first.c_str(), 0) + std::string("=") + curl_easy_escape(curl, arg.second.c_str(), 0);
        }

        // If GET method, append parameters to URL
        if (method == "GET" && !params.empty())
        {
            fullUrl += "?" + params;
        }

        // Set the URL
        curl_easy_setopt(curl, CURLOPT_URL, fullUrl.c_str());
        // Set the write callback function
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        // Set the data to pass to the callback function
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

        // If POST method, set the POST fields
        if (method == "POST")
        {
            curl_easy_setopt(curl, CURLOPT_POST, 1L);
            curl_easy_setopt(curl, CURLOPT_POSTFIELDS, params.c_str());
        }

        // Set default headers
        struct curl_slist *headers = NULL;

        //'APCA-API-KEY-ID: PKCZJZQXZJZJZJZJZJZJ'


        std::string key_id = "APCA-API-KEY-ID: " + apiKeyId;

        std::string secret_id = "APCA-API-SECRET-KEY: " + apiSecretKey;







        

        headers = curl_slist_append(headers, key_id.c_str());
        headers = curl_slist_append(headers, secret_id.c_str());
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

        // Perform the request
        res = curl_easy_perform(curl);

        // Check for errors
        if (res != CURLE_OK)
        {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        }

        // Cleanup
        curl_slist_free_all(headers); // free the list of headers
        curl_easy_cleanup(curl);
    }


    std::cout << "Response: " << readBuffer << std::endl;

    return readBuffer;
}