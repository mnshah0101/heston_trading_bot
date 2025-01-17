#ifndef GET_HISTORICAL_H
#define GET_HISTORICAL_H


#include <string>

#include "json.hpp"

using json = nlohmann::json;

// Function declaration
json get_historical(const std::string &symbol, const std::string &start, const std::string &end, const std::string &timeframe);

#endif // GET_HISTORICAL_H

