# Configurable-Data-Processing-System
A C++‐based framework for defining and running data‐processing pipelines purely through external configuration files. Instead of hard‐coding each processing step, this project lets you specify which “processors” to run—and in what order—via a configuration file. The core engine reads the configuration, dynamically instantiates the requested processing modules (e.g., numerical transforms, filters, aggregators), and executes them on one or more input data streams. Everything is modular: you can add new processors by dropping a header/source pair into `include/` and `src/`, and then reference them in your config.

1. [Features](#features)  
2. [HowToBuild](#HowToBuild)

## Features
This project currently features 3 processors
1. Image
    a. Prints basic image data such as resolution, pixel depth, etc..
    b. Applying a threshold
2. Text
    a. Prints basic text data such as word count and line count
    b. Find and replace word
    c. Searching for word frequency
3. Numerical
    a. Prints basic numerical data such as Max, min, Mean, etc..
    b. Applying a threshold


## HowToBuild
- Bash:
g++ src/main.cpp src/Configuration.cpp src/Processor.cpp src/ProcessorFactory.cpp -Iinclude -o Output `pkg-config --cflags --libs opencv4`