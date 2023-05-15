# ToTreeOrNotToTree
![Hamlet](./misc/hamlet.jpeg "Hamlet")

# Build
This project uses [CMake](https://cmake.org/) to build. To build the project, run the following commands:
```bash
mkdir build
cd build
cmake ..
make
```
### Note
Read the dependencies, but if the project will not build it is likely because you are on a computer that doesn't have
CURL installed by default, or CMAKE cannot find it.
If this is the case, you can install it with the following command (or similar, check your OS):
```bash
sudo apt-get install libcurl4-openssl-dev
```
If this still doesn't work, you can try to manually specify the path to CURL in the CMakeLists.txt file.

## Run
One target is produced:
* `analyze`

Analyze takes one argument, the path to the file to analyze.
It produces two primary outputs: a file called 'NAME_report.txt' and a file called 'NAME_report.pdf', which
contain the same information in different formats.

For example:
```bash
./analyze ../data/input/crimeandpunishment.txt
```
will produce the following files:
* `crimeandpunishment_report.txt`
* `crimeandpunishment_report.pdf`
* `crimeandpunishment_report.html` (extra)

The report contains the following information:
* Total number of words in the report
* Number of unique words
* Number of unique words of more than three letters
* Average word length 
* Average sentence length
* An index (alphabetical listing) of all the unique words

Warnings are also produced for the following cases:
* Word used too often: Each word that which represents more than 5% of the total (long) words used
* Sentence length : Average sentence length > 10
* Word length : Average word length > 5

## Dependencies
* [CMake](https://cmake.org/) (For building)
* [libcurl](https://curl.haxx.se/libcurl/) (Upload/download files)
* [ctml](https://github.com/tinfoilboy/CTML) (HTML generation, could easily be done without though)

# Design
## Overview
The project is split into three main components:
* `main.cpp` - The main entry point for the program.
  * Parses command line arguments
  * Reads the input file
  * Calls the analyzer/report functions
* `FileHandle.cpp` - Handles writing files
* `Tree/Wordnet.h` - Structure of the tree and the functions to analyze the input file

## Process
1. Read the input file into the wordnet
2. Analyze the wordnet
3. Write the text report
4. Write the HTML report by inserting HTML strings into a template
5. Send the HTML report to a server
6. Server converts the HTML report to a PDF and sends it back
7. Save the PDF report locally