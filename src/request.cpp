
#include <curl/curl.h>
#include <stddef.h>
#include <iostream>
#include <map>


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

        curl_easy_setopt(curl, CURLOPT_URL, fullUrl.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

        // If POST method, set the POST fields
        if (method == "POST")
        {
            curl_easy_setopt(curl, CURLOPT_POST, 1L);
            curl_easy_setopt(curl, CURLOPT_POSTFIELDS, params.c_str());
        }

        // Perform the request
        res = curl_easy_perform(curl);

        // Check for errors
        if (res != CURLE_OK)
        {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        }

        // Cleanup
        curl_easy_cleanup(curl);
    }

    return readBuffer;
}