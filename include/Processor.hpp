#ifndef PROCESSOR_HPP
#define PROCESSOR_HPP
#include <map>
#include <string>
#include <fstream>
#include <vector>
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;

class Processor {
protected:
    fstream file;  // shared by 2 processors
    string filePath; // shared by all processors
public:
    virtual void loadFile(const string& filepath) = 0; // new virtual interface
    virtual void printData() = 0; // pure virtual function
    virtual ~Processor() = default; // always add virtual destructor
};

// The following can be stubbed out or defined in separate headers later
class TextProcessor : public Processor 
{
protected:
    
public:
    void loadFile(const string& filepath) override;
    void printData() override;

    void findAndReplace(string& findStr, const string& replaceStr);
    int countLines();
    int countWords();
    int searchWord(string& searchWord);
};

class ImageProcessor : public Processor {
protected:
    Mat image;
public:
    void loadFile(const string& filepath) override;
    void printData() override;

    void applyThreshold(float threshold);
    void saveEdits();
};

// class AudioProcessor : public Processor {
// public:
//     void loadFile(const string& filepath) override;
//     void printData() override;

//     void loadAudioData(const string& filepath);  // same as above
//     void filterNoise();
// };

// class NumericProcessor : public Processor {
// protected:
//     vector<double> numbers;

// public:
//     void loadFile(const string& filepath) override;
//     void printData() override;

//     void applyThreshold() const;
//     double computeAverage() const;
//     double findMin() const;
//     double findMax() const;
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
