#include "/mnt/d/Applications/Visual Studio Code/myCodes/c++ codes/projects/Configurable-Data-Processing-System/include/Configuration.hpp"
Configuration::Configuration(const std::string& filePath)
{
    std::string line;
    settingsFile.open(filePath);
    if (!settingsFile.is_open()) 
    {
        throw std::runtime_error("Failed to open config file.");
    }

    while(std::getline(settingsFile, line))
    {
        std::size_t seperator = line.find('=');
        // size_t is nothing but unsigned long but its advantage is that it avoids compiler warnings for unsigned mismatches

        if(seperator != std::string::npos)
        {
            std::string key = line.substr(0, seperator);
            std::string value = line.substr(seperator + 1);
            configMap[key] = value;
        }
    }
}

std::string Configuration::get(const std::string& key) const
{   
    if (configMap.find(key) != configMap.end()) 
        return configMap.at(key);
    return "";
}

