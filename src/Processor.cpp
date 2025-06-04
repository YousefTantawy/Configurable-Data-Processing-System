#include "Processor.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cctype>
#include <map>
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

// -------------------- TextProcessor --------------------

void TextProcessor::loadFile(const string& filepath) 
{
    // Remember the filepath so that later findAndReplace can re‐open with trunc:
    filePath = filepath;

    // Open in read/write mode:
    file.open(filepath, ios::in | ios::out);
    if (!file.is_open()) 
    {
        throw invalid_argument("Failed to open text");
    }
}
int TextProcessor::countLines()
{
    file.clear(); 
    file.seekg(0, ios::beg);
    string temp;
    int counter = 0;
    while (getline(file, temp)) {
        counter++;
    }
    return counter;
}
int TextProcessor::countWords()
{
    file.clear(); 
    file.seekg(0, ios::beg);
    string line, word;
    int counter = 0;

    while (getline(file, line)) {
        istringstream iss(line);
        while (iss >> word) {
            counter++;
        }
    }
    return counter;
}
int TextProcessor::searchWord(string& searchWord) 
{
    file.clear();
    file.seekg(0, ios::beg);

    string line, word;
    int counter = 0;

    // Lowercase the search term
    for (char& c : searchWord) 
        c = tolower(static_cast<unsigned char>(c));

    while (getline(file, line)) {
        istringstream iss(line);
        while (iss >> word) {
            for (char& c : word) 
                c = tolower(static_cast<unsigned char>(c));
            if (word == searchWord)
                counter++;
        }
    }

    return counter;
}
void TextProcessor::printData() 
{
    if (file.is_open()) {
        cout << "Number of lines in provided file: " << countLines() << endl;
        cout << "Number of words in provided file: " << countWords() << endl;
    }
    else {
        cout << "No file provided!\n";
    }
}
void TextProcessor::findAndReplace(string& findStr, const string& replaceStr)
{
    // 1) Read entire file into 'content':
    file.clear();
    file.seekg(0, ios::beg);

    ostringstream buffer;
    buffer << file.rdbuf();
    string content = buffer.str();

    // 2) Do a simple find/replace (case‐sensitive, substring matches):
    size_t pos = 0;
    while ((pos = content.find(findStr, pos)) != string::npos) {
        content.replace(pos, findStr.length(), replaceStr);
        pos += replaceStr.length();
    }

    // 3) Now close the fstream and re‐open in trunc mode to overwrite:
    file.close();

    // Re‐open with trunc so that writing 'content' replaces everything:
    file.open(filePath, ios::out | ios::trunc);
    if (!file.is_open()) {
        cerr << "Failed to reopen \"" << filePath << "\" for overwriting.\n";
        return;
    }

    file << content;
    file.flush();
    file.close();

    // 4) (Optional) Re‐open in read/write mode again, in case main() wants to do more operations
    file.open(filePath, ios::in | ios::out);
    if (!file.is_open()) {
        cerr << "Failed to re‐open \"" << filePath << "\" in read/write mode after replace.\n";
    }
}
// -------------------- ImageProcessor --------------------
void ImageProcessor::loadFile(const string& filepath) 
{
    if(filepath != filePath)
        filePath = filepath;
    image = imread(filepath);
    if (image.empty()) 
    {
        throw invalid_argument("Failed to load image.");
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
        cout << "No image loaded.\n";
        return;
    }

    cout << "Image Information:\n";
    cout << "------------------\n";
    cout << "File Path: " << filePath << '\n';
    cout << "Resolution (Width x Height): " << image.cols << " x " << image.rows << '\n';
    cout << "Channels: " << image.channels() << '\n';
    cout << "Depth (bit precision per channel): ";

    switch (image.depth()) {
        case CV_8U:  cout << "8-bit unsigned\n"; break;
        case CV_8S:  cout << "8-bit signed\n"; break;
        case CV_16U: cout << "16-bit unsigned\n"; break;
        case CV_16S: cout << "16-bit signed\n"; break;
        case CV_32S: cout << "32-bit signed\n"; break;
        case CV_32F: cout << "32-bit float\n"; break;
        case CV_64F: cout << "64-bit float\n"; break;
        default:     cout << "Unknown\n"; break;
    }

    cout << "Total Pixels: " << image.total() << '\n';
    cout << "Image Size (rows x cols): " << image.size() << '\n';
}


void ImageProcessor::saveEdits()
{
    string savePath = "savedImage.jpg";
    imwrite(savePath, image);

    loadFile(filePath);
}
