#ifndef DOTENV_H
#define DOTENV_H

#include <unordered_map>
#include <string>

// Function declaration
std::unordered_map<std::string, std::string> readEnvFile(const std::string &filename);

#endif // DOTENV_H
