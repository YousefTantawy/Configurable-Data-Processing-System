#ifndef PROCESSOR_FACTORY_HPP
#define PROCESSOR_FACTORY_HPP

#include "Processor.hpp"
#include <memory>
using namespace std;

class ProcessorFactory 
{
public:
    /*
        Static function for creating the base class
        Static because making an object of this is pointless
    */ 
    static unique_ptr<Processor> createProcessor(const string& type);
};

#endif 
