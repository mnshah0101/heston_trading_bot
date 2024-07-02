#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <string>
#include <map>
#include "json.hpp"

using json = nlohmann::json;
// for convenience

// Declaration of the function
json makeHttpRequest(const std::string &url, const std::map<std::string, std::string> &arguments, const std::string &method);

#endif // FUNCTIONS_H
