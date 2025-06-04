#include <iostream>
#include <vector>
#include <map>
#include "/mnt/d/Applications/Visual Studio Code/myCodes/c++ codes/projects/Configurable-Data-Processing-System/include/ProcessorFactory.hpp"
#include "/mnt/d/Applications/Visual Studio Code/myCodes/c++ codes/projects/Configurable-Data-Processing-System/include/Processor.hpp"
#include "/mnt/d/Applications/Visual Studio Code/myCodes/c++ codes/projects/Configurable-Data-Processing-System/include/Configuration.hpp"
using namespace std;

int main(void) 
{
    std::string temp, temp2;
    int choice;
    TextProcessor *text;

    Configuration Config("config/settings.txt");
    std::unique_ptr<Processor> processManager = ProcessorFactory::createProcessor(Config.get("Processor.Options.Type"));

    cout << "Write file path: ";
    getline(cin, temp);
    processManager->loadFile(temp);
    for(;;)
    {
        if(Config.get("Processor.Options.Type") == "text" || Config.get("Processor.Options.Type") == "Text")
        {
            cout << "What would you like to do:\n 1. printData | 2. Search for word | 3. Find and replace\n";
            cin >> choice;
            switch(choice)
            {
                case 1:
                    processManager->printData();
                    break;
                case 2:
                    text = dynamic_cast<TextProcessor*>(processManager.get());
                    cout << "What word would you like to search for in your file:\n";
                    cin >> temp;
                    cout << "Frequency of the word " << temp << ": " << text->searchWord(temp) << endl;
                    break;
                case 3:
                    text = dynamic_cast<TextProcessor*>(processManager.get());
                    cout << "What word would you like to replace:\n";
                    cin >> temp;
                    cout << "What is the word instead of replacement:\n";
                    cin >> temp2;
                    text->findAndReplace(temp, temp2);
                    break;
                default:
                    cout << "Error: invalid choice"; 
            }
        }
        
    }


}