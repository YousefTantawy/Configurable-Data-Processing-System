#include <iostream>
#include <vector>
#include <map>
#include "/mnt/d/Applications/Visual Studio Code/myCodes/c++ codes/projects/Configurable-Data-Processing-System/include/ProcessorFactory.hpp"
#include "/mnt/d/Applications/Visual Studio Code/myCodes/c++ codes/projects/Configurable-Data-Processing-System/include/Processor.hpp"
#include "/mnt/d/Applications/Visual Studio Code/myCodes/c++ codes/projects/Configurable-Data-Processing-System/include/Configuration.hpp"
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

int main(void) 
{
    std::string temp, temp2;
    int choice;
    TextProcessor *text;
    ImageProcessor *image;

    Configuration Config("config/settings.txt");
    std::unique_ptr<Processor> processManager = ProcessorFactory::createProcessor(Config.get("Processor.Options.Type"));

    cout << "Write file path: ";
    getline(cin, temp);
    processManager->loadFile(temp);
    for(;;)
    {
        if(Config.get("Processor.Options.Type") == "text" || Config.get("Processor.Options.Type") == "Text")
        {
            cout << "What would you like to do:\n 1. print data | 2. Search | 3. Find and replace\n";
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
        else if(Config.get("Processor.Options.Type") == "Image" || Config.get("Processor.Options.Type") == "image")
        {
            cout << "What would you like to do:\n 1. print data | 2. Apply Threshold | 3. Save\n";
            cin >> choice;
            switch(choice)
            {
                case 1:
                    processManager->printData();
                    break;
                case 2:
                    image = dynamic_cast<ImageProcessor*>(processManager.get());
                    image->applyThreshold(std::stof(Config.get("Processor.Options.Threshold")));
                    cout << "Threshold applied" << endl;
                    break;
                case 3:
                    image = dynamic_cast<ImageProcessor*>(processManager.get());
                    image->saveEdits();
                    break;
                default:
                    cout << "Error: invalid choice"; 
            }
        }
        
    }
}

