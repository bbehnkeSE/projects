// Brian Behnke
// cs23001
// Lab 5, reads from file

#include<iostream>
#include<fstream>

void printFromFile() {
  std::ifstream readFile ("fileio-text.txt");
  if(!readFile.is_open()){
    std::cout << "Unable to open file" << std::endl;
  }
  char fromFile;
  readFile.get(fromFile);
  while(!readFile.eof() && fromFile != ' ') {
    std::cout << fromFile;
    readFile.get(fromFile);
  }
  std::cout << std::endl;
  readFile.close();
}

void addFromFile() {
  std::ifstream addFile ("fileio-data-1.txt");
  if(!addFile.is_open()){
    std::cout << "Unable to open file" << std::endl;
  }
  int num1;
  int num2;
  addFile >> num1;
  addFile.get();
  addFile >> num2;
  std::cout << num1 << "+" << num2 << "=" << num1 + num2;
  std::cout << std::endl;
  addFile.close();
}

int main() {
  printFromFile();
  addFromFile();
  return 0;
}
