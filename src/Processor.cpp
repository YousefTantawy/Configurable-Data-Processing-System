#include "/mnt/d/Applications/Visual Studio Code/myCodes/c++ codes/projects/Configurable-Data-Processing-System/include/Processor.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cctype>
#include <map>
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

// -------------------- TextProcessor --------------------

void TextProcessor::loadFile(const std::string& filepath) 
{
    // Remember the filepath so that later findAndReplace can re‐open with trunc:
    filePath = filepath;

    // Open in read/write mode:
    file.open(filepath, ios::in | ios::out);
    if (!file.is_open()) 
    {
        throw std::invalid_argument("Failed to open text");
    }
}
int TextProcessor::countLines()
{
    file.clear(); 
    file.seekg(0, std::ios::beg);
    std::string temp;
    int counter = 0;
    while (std::getline(file, temp)) {
        counter++;
    }
    return counter;
}
int TextProcessor::countWords()
{
    file.clear(); 
    file.seekg(0, std::ios::beg);
    std::string line, word;
    int counter = 0;

    while (std::getline(file, line)) {
        std::istringstream iss(line);
        while (iss >> word) {
            counter++;
        }
    }
    return counter;
}
int TextProcessor::searchWord(std::string& searchWord) 
{
    file.clear();
    file.seekg(0, std::ios::beg);

    std::string line, word;
    int counter = 0;

    // Lowercase the search term
    for (char& c : searchWord) 
        c = std::tolower(static_cast<unsigned char>(c));

    while (std::getline(file, line)) {
        std::istringstream iss(line);
        while (iss >> word) {
            for (char& c : word) 
                c = std::tolower(static_cast<unsigned char>(c));
            if (word == searchWord)
                counter++;
        }
    }

    return counter;
}
void TextProcessor::printData() 
{
    if (file.is_open()) {
        std::cout << "Number of lines in provided file: " << countLines() << std::endl;
        std::cout << "Number of words in provided file: " << countWords() << std::endl;
    }
    else {
        std::cout << "No file provided!\n";
    }
}
void TextProcessor::findAndReplace(std::string& findStr, const std::string& replaceStr)
{
    // 1) Read entire file into 'content':
    file.clear();
    file.seekg(0, std::ios::beg);

    std::ostringstream buffer;
    buffer << file.rdbuf();
    std::string content = buffer.str();

    // 2) Do a simple find/replace (case‐sensitive, substring matches):
    size_t pos = 0;
    while ((pos = content.find(findStr, pos)) != std::string::npos) {
        content.replace(pos, findStr.length(), replaceStr);
        pos += replaceStr.length();
    }

    // 3) Now close the fstream and re‐open in trunc mode to overwrite:
    file.close();

    // Re‐open with trunc so that writing 'content' replaces everything:
    file.open(filePath, std::ios::out | std::ios::trunc);
    if (!file.is_open()) {
        std::cerr << "Failed to reopen \"" << filePath << "\" for overwriting.\n";
        return;
    }

    file << content;
    file.flush();
    file.close();

    // 4) (Optional) Re‐open in read/write mode again, in case main() wants to do more operations
    file.open(filePath, std::ios::in | std::ios::out);
    if (!file.is_open()) {
        std::cerr << "Failed to re‐open \"" << filePath << "\" in read/write mode after replace.\n";
    }
}
// -------------------- ImageProcessor --------------------
void ImageProcessor::loadFile(const std::string& filepath) 
{
    if(filepath != filePath)
        filePath = filepath;
    image = imread(filepath);
    if (image.empty()) 
    {
        throw std::invalid_argument("Failed to load image.");
    }
}

void ImageProcessor::applyThreshold(float threshold)
{
    cvtColor(image, image, COLOR_BGR2GRAY);
    cv::threshold(image, image, int(threshold*255), 255, THRESH_BINARY);
}

void ImageProcessor::printData()
{
    if (image.empty()) {
        std::cout << "No image loaded.\n";
        return;
    }

    std::cout << "Image Information:\n";
    std::cout << "------------------\n";
    std::cout << "File Path: " << filePath << '\n';
    std::cout << "Resolution (Width x Height): " << image.cols << " x " << image.rows << '\n';
    std::cout << "Channels: " << image.channels() << '\n';
    std::cout << "Depth (bit precision per channel): ";

    switch (image.depth()) {
        case CV_8U:  std::cout << "8-bit unsigned\n"; break;
        case CV_8S:  std::cout << "8-bit signed\n"; break;
        case CV_16U: std::cout << "16-bit unsigned\n"; break;
        case CV_16S: std::cout << "16-bit signed\n"; break;
        case CV_32S: std::cout << "32-bit signed\n"; break;
        case CV_32F: std::cout << "32-bit float\n"; break;
        case CV_64F: std::cout << "64-bit float\n"; break;
        default:     std::cout << "Unknown\n"; break;
    }

    std::cout << "Total Pixels: " << image.total() << '\n';
    std::cout << "Image Size (rows x cols): " << image.size() << '\n';
}


void ImageProcessor::saveEdits()
{
    std::string savePath = "savedImage.jpg";
    imwrite(savePath, image);

    loadFile(filePath);
}
