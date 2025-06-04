#include "/mnt/d/Applications/Visual Studio Code/myCodes/c++ codes/projects/Configurable-Data-Processing-System/include/Processor.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cctype>
#include <map>
using namespace std;

// -------------------- TextProcessor --------------------

void TextProcessor::loadFile(const std::string& filepath) 
{
    // Remember the filepath so that later findAndReplace can re‐open with trunc:
    filePath = filepath;

    // Open in read/write mode:
    file.open(filepath, ios::in | ios::out);
    if (!file.is_open()) {
        std::cerr << "Failed to open \"" << filepath << "\" for reading/writing.\n";
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
