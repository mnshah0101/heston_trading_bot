#include <fstream>
#include <sstream>
#include <iostream>
#include <unordered_map>
#include <string>


// Function definition
std::unordered_map<std::string, std::string> readEnvFile(const std::string &filename)
{
    std::cout << "Reading environment variables from file: " << filename << std::endl;



    std::unordered_map<std::string, std::string> envMap;
    std::ifstream file(filename);

    if (!file.is_open())
    {
        std::cerr << "Error: Could not open the file " << filename << std::endl;
        return envMap;
    }

    std::string line;
    while (std::getline(file, line))
    {
        if (line.empty() || line[0] == '#')
        {
            continue;
        }
        std::istringstream lineStream(line);

        std::cout << "Reading line: " << line << std::endl;


        std::string key;
        if (std::getline(lineStream, key, '='))
        {
            std::string value;
            if (std::getline(lineStream, value))
            {
                envMap[key] = value;
            }
        }
    }

    file.close();

    return envMap;

}



   
