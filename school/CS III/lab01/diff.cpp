// Compares contents of two files and prints differences.
// Brian Behnke
// 8/30/2021

#include <iostream>
#include <fstream>
#include <string>

std::string consolidateFileInfo(const std::string&, const int&);
std::string spaceString(const int&, const char&);

int main(int argc, char* argv[]) {
    // Checks if enough files are provided.
    if(argc < 3) {
        std::cerr << "Too few arguments. Exiting...\n";
        return 1;
    }

    // Convert C-style string to C++.
    std::string sFileName1(argv[1]);
    std::string sFileName2(argv[2]);

    // Creates ifstream objects and opens files.
    std::ifstream file1, file2;
    file1.open(sFileName1);
    file2.open(sFileName2);

    if(file1.is_open() && file2.is_open()) {
        std::string lineFromFile1, lineFromFile2;
        int numberOfSpaces;     // Sum of spaces required to put the caret under the first difference. Used for spaceString().
        int lineCounter = 1;    // Keeps track of current line being read from file.

        while(!file1.eof() || !file2.eof()) {
            // Checks if at end of file. If true set line to be empty, else get line from file.
            if(file1.eof()) {
                lineFromFile1 = "";
            }
            else {
                getline(file1, lineFromFile1);
            }
            if(file2.eof()) {
                lineFromFile2 = "";
            }
            else {
                getline(file2, lineFromFile2);
            }
            
            // If two lines aren't equal, iterate through them char by char to find the first difference, then print the information.
            if(lineFromFile1 != lineFromFile2) {
                int i = 0;      // Number of characters before first difference.
                while(lineFromFile1[i] == lineFromFile2[i]) {
                    ++i;
                }
                numberOfSpaces = consolidateFileInfo(sFileName1, lineCounter).length() + i;
                std::cout << consolidateFileInfo(sFileName1, lineCounter) << lineFromFile1 << std::endl;
                std::cout << consolidateFileInfo(sFileName2, lineCounter) << lineFromFile2 << std::endl;
                std::cout << spaceString(numberOfSpaces, ' ') << "^" << std::endl;
            }
            ++lineCounter;
        }
    }
    else {
        std::cerr << "Unable to open file(s). Exiting...\n";
        return 1;
    }
    file1.close();
    file2.close();

    return 0;
}


// Combines the file information and formatting into a single string.
// Used to easily find the total length needed for spaceString() regardless of line number digits.
std::string consolidateFileInfo(const std::string& fileName, const int& lineNumber) {
    std::string sLineNumber = std::to_string(lineNumber);
    std::string fileInfo = fileName + ": " + sLineNumber + ": ";

    return fileInfo;
}


// Creates a string of spaces.
std::string spaceString(const int& length, const char& space) {
    std::string stringOfSpaces;
    for(int i = 0; i < length; ++i) {
        stringOfSpaces += space;
    }
    return stringOfSpaces;
}