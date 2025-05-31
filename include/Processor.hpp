#ifndef PROCESSOR_HPP
#define PROCESSOR_HPP

class Processor {
public:
    virtual void process(const std::string& input) = 0; // pure virtual function
    virtual ~Processor() = default; // always add virtual destructor
};

// The following can be stubbed out or defined in separate headers later
class TextProcessor : public Processor {
public:
    void process(const std::string& input) override;
};

class ImageProcessor : public Processor {
public:
    void process(const std::string& input) override;
};

class AudioProcessor : public Processor {
public:
    void process(const std::string& input) override;
};

class NumericProcessor : public Processor {
public:
    void process(const std::string& input) override;
};

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