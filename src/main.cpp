#include <iostream>
#include <vector>
#include <map>
// #include "/mnt/d/Applications/Visual Studio Code/myCodes/c++ codes/projects/Configurable-Data-Processing-System/include/ProcessorFactory.hpp"
// #include "/mnt/d/Applications/Visual Studio Code/myCodes/c++ codes/projects/Configurable-Data-Processing-System/include/Processor.hpp"
#include "/mnt/d/Applications/Visual Studio Code/myCodes/c++ codes/projects/Configurable-Data-Processing-System/include/Configuration.hpp"
using namespace std;

int main(void) 
{
    Configuration Config("config/settings.txt");

    string processorType;
    std::cin >> processorType;
    processorType = Config.get(processorType);

    if (processorType.empty()) 
    throw runtime_error("Unmatched key with settings.txt");
    
    cout << processorType; 
}