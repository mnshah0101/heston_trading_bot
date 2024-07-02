#ifndef CREATE_ORDER_H
#define CREATE_ORDER_H

#include <string>
#include "json.hpp"

using json = nlohmann::json;

// Function declaration
json create_trade(const std::string &symbol, const std::string &qty, const std::string &side, const std::string &type, const std::string &time_in_force);

#endif // CREATE_ORDER_H

