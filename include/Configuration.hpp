#ifndef Configuration_HPP
#define Configuration_HPP
#include <fstream>
#include <map>

class Configuration
{
    private:
    std::map<std::string, std::string> configMap;
    std::ifstream settingsFile;

    public:
    Configuration(const std::string& filePath);

    std::string get(const std::string& key) const;
};
#endif