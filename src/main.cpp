#include <iostream>
#include <vector>
#include <map>
#include "Processor.hpp"
#include "ProcessorFactory.hpp"
#include "Configuration.hpp"
using namespace std;

int main(void) 
{
    // ------------------Variables------------------------------------------------------------
    string tempStr, tempStr2; // Using for temporary operations that require strings
    int choice; // For user choice on what function to run
    TextProcessor *text; // Pointer for functions exclusive to text processor class
    ImageProcessor *image; // Pointer for functions exclusive to image processor class
    NumericProcessor *Numeric; // Pointer for functions exclusive to Numeric processor class

    Configuration Config("config/settings.txt");
    // Create a base pointer that points towards a processor object according to settings.txt
    unique_ptr<Processor> processManager = ProcessorFactory::createProcessor(Config.get("Processor.Options.Type"));

    cout << "--------------------------------------------------------------------------\n";
    cout << "Write file path: ";
    getline(cin, tempStr);
    processManager->loadFile(tempStr);
    for(;;)
    {
        if(Config.get("Processor.Options.Type") == "text" || Config.get("Processor.Options.Type") == "Text")
        {
            cout << "--------------------------------------------------------------------------\n";
            cout << "What would you like to do:\n 1. print data | 2. Search | 3. Find and replace\n";
            cin >> choice;
            switch(choice)
            {
                case 1:
                    processManager->printData();
                    break;
                case 2:
                    text = dynamic_cast<TextProcessor*>(processManager.get());
                    cout << "--------------------------------------------------------------------------\n";
                    cout << "What word would you like to search for in your file:\n";
                    cin >> tempStr;
                    cout << "--------------------------------------------------------------------------\n";
                    cout << "Frequency of the word " << tempStr << ": " << text->searchWord(tempStr) << endl;
                    break;
                case 3:
                    text = dynamic_cast<TextProcessor*>(processManager.get());
                    cout << "--------------------------------------------------------------------------\n";
                    cout << "What word would you like to replace:\n";
                    cin >> tempStr;
                    cout << "--------------------------------------------------------------------------\n";
                    cout << "What is the word instead of replacement:\n";
                    cin >> tempStr2;
                    text->findAndReplace(tempStr, tempStr2);
                    break;
                default:
                cout << "--------------------------------------------------------------------------\n";
                    cout << "Error: invalid choice. Exitting...";
                    return 0; 
            }
        }
        else if(Config.get("Processor.Options.Type") == "Image" || Config.get("Processor.Options.Type") == "image")
        {
            cout << "--------------------------------------------------------------------------\n";
            cout << "What would you like to do:\n 1. print data | 2. Apply Threshold | 3. Save\n";
            cin >> choice;
            switch(choice)
            {
                case 1:
                    processManager->printData();
                    break;
                case 2:
                    image = dynamic_cast<ImageProcessor*>(processManager.get());
                    image->applyThreshold(stof(Config.get("Processor.Options.Threshold")));
                    cout << "--------------------------------------------------------------------------\n";
                    cout << "Threshold of " << Config.get("Processor.Options.Threshold") << " applied" << endl;
                    break;
                case 3:
                    image = dynamic_cast<ImageProcessor*>(processManager.get());
                    image->saveEdits();
                    break;
                default:
                    cout << "--------------------------------------------------------------------------\n";
                    cout << "Error: invalid choice. Exitting...";
                    return 0;  
            }
        }     
        else if(Config.get("Processor.Options.Type") == "Numeric" || Config.get("Processor.Options.Type") == "Numeric")
        {
            cout << "--------------------------------------------------------------------------\n";
            cout << "What would you like to do:\n 1. print data | 2. Apply Threshold\n";
            cin >> choice;
            switch(choice)
            {
                case 1:
                    processManager->printData();
                    break;
                case 2:
                    Numeric = dynamic_cast<NumericProcessor*>(processManager.get());
                    Numeric->applyThreshold(stof(Config.get("Processor.Options.Threshold")));
                    cout << "Threshold of " << Config.get("Processor.Options.Threshold") << " applied" << endl;
                    Numeric = nullptr;
                    break;
                default:
                    cout << "--------------------------------------------------------------------------\n";
                    cout << "Error: invalid choice. Exitting...";
                    return 0;  
            }
        }
    }
}

