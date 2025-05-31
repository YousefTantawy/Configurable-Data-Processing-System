#include "/mnt/d/Applications/Visual Studio Code/myCodes/c++ codes/projects/Configurable-Data-Processing-System/include/ProcessorFactory.hpp"
#include <stdexcept>

std::unique_ptr<Processor> ProcessorFactory::createProcessor(const std::string& type) 
{
    if (type == "Text") {
        return std::make_unique<TextProcessor>();
    } else if (type == "Numeric") {
        return std::make_unique<NumericProcessor>();
    } else if (type == "Image") {
        return std::make_unique<ImageProcessor>();
    } else if (type == "Audio") {
        return std::make_unique<AudioProcessor>();
    } else {
        throw std::invalid_argument("Unsupported processor type: " + type);
    }
}