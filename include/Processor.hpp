#ifndef PROCESSOR_HPP
#define PROCESSOR_HPP
#include <map>
#include <string>
#include <fstream>
#include <vector>

class Processor {
protected:
    std::fstream file;  // shared by all processors

public:
    virtual void loadFile(const std::string& filepath) = 0; // new virtual interface
    virtual void printData() = 0; // pure virtual function
    virtual ~Processor() = default; // always add virtual destructor
};

// The following can be stubbed out or defined in separate headers later
class TextProcessor : public Processor 
{
protected:
    std::string filePath;
public:
    void loadFile(const std::string& filepath) override;
    void printData() override;

    void findAndReplace(std::string& findStr, const std::string& replaceStr);
    int countLines();
    int countWords();
    int searchWord(std::string& searchWord);
};

// class ImageProcessor : public Processor {
// public:
//     void loadFile(const std::string& filepath) override;
//     void printData() override;

//     void loadPixelData(const std::string& filepath);  // could be wrapped by loadFile
//     void applyThreshold(float threshold);
// };

// class AudioProcessor : public Processor {
// public:
//     void loadFile(const std::string& filepath) override;
//     void printData() override;

//     void loadAudioData(const std::string& filepath);  // same as above
//     void filterNoise();
// };

// class NumericProcessor : public Processor 
// {
// public:
//     void loadFile(const std::string& filepath) override;
//     void printData() override;

//     void loadNumbers(const std::vector<double>& data);  // might not be from file
//     std::vector<double> applyThreshold(double threshold) const;
// };

/*
Here is a quick list of all functionalities in the Processors

1. TextProcessor
    - Read line by line 
    - Search for words (ctrl-F)
    - Count words
    - 
2. NumericProcessor
    - Filter useless numbers through threshold
    - 
3. ImageProcessor
    - Can load pixel data
    - Apply filter or threshold
4. AudioProcessor
    - 
    - 
*/

#endif
