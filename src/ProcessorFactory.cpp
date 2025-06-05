#include "ProcessorFactory.hpp"
#include <stdexcept>
using namespace std;

unique_ptr<Processor> ProcessorFactory::createProcessor(const string& type) 
{
    // Depending on the type, create a processor object
    if (type == "Text" || type == "text") 
    {
        return make_unique<TextProcessor>();
    } 
    else if (type == "Numeric" || type == "numeric") 
    {
        return make_unique<NumericProcessor>();
    } 
    else if (type == "Image" || type == "image") 
    {
        return make_unique<ImageProcessor>();
    } 
    // else if (type == "Audio" || type == "audio") 
    // {
    //     return make_unique<AudioProcessor>();
    // } 
    else 
    {
        throw invalid_argument("Unsupported processor type: " + type);
    }
}