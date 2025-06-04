#ifndef Configuration_HPP
#define Configuration_HPP
#include <fstream>
#include <map>
using namespace std;

class Configuration
{
    private:
    // Map used for storing data from config fil
    map<string, string> configMap;
    ifstream settingsFile;

    public:
    Configuration(const string& filePath);
    // get here is used to search for key in map
    string get(const string& key) const;
};
#endif