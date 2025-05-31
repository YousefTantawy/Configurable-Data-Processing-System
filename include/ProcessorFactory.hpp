#ifndef PROCESSOR_FACTORY_HPP
#define PROCESSOR_FACTORY_HPP

#include "/mnt/d/Applications/Visual Studio Code/myCodes/c++ codes/projects/Configurable-Data-Processing-System/include/Processor.hpp"
#include <memory>
#include <string>


class ProcessorFactory 
{
public:
    static std::unique_ptr<Processor> createProcessor(const std::string& type);
};

#endif 
