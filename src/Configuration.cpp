#include "Configuration.hpp"
Configuration::Configuration(const string& filePath)
{
    string line;
    settingsFile.open(filePath);
    if (!settingsFile.is_open()) 
    {
        throw runtime_error("Failed to open config file.");
    }

    while(getline(settingsFile, line))
    {
        size_t seperator = line.find('=');
        // size_t is nothing but unsigned long but its advantage is that it avoids compiler warnings for unsigned mismatches

        if(seperator != string::npos)
        {
            string key = line.substr(0, seperator);
            string value = line.substr(seperator + 1);
            configMap[key] = value;
        }
    }
}

string Configuration::get(const string& key) const
{   
    if (configMap.find(key) != configMap.end()) 
        return configMap.at(key);
    return "";
}

