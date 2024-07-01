#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <string>
#include <map>

// Declaration of the function
std::string makeHttpRequest(const std::string &url, const std::map<std::string, std::string> &arguments, const std::string &method);

#endif // FUNCTIONS_H
