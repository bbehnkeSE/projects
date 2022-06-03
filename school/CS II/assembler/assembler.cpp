// Brian Behnke
// cs23001
// 11/5/2019
//
// Main file for postfix conversion
//

#include "utilities.hpp"

int main(int argc, char *argv[]) {

  std::ifstream fromFile(argv[1]);
  std::ofstream outFile (argv[2]);
  if(!fromFile.is_open()) {
    std::cout << "Unable to open file." << std::endl;
    return 1;
  }
  
  int i = 0;
  String line;
  fromFile >> line;
  while(line.findch(i, ';') != -1) {
    if(argc <= 2) {
      std::cout << "Infix   expression: "  << line.substr(i, line.findch(i, ';') - 1)      << std::endl
    	        << "Postfix expression: "  << postfix(line.substr(i, line.findch(i, ';'))) << std::endl
		<< "Prefix  expression: "  << prefix (line.substr(i, line.findch(i, ';'))) << std::endl
		<< "Assembly:\n"           << assembler(std::cout, postfix(line.substr(i, line.findch(i, ';'))) + " ;") << std::endl;
      fromFile >> line;
      std::cout << std::endl;
    } 
    else {
      outFile << "infix   expression: "  << line.substr(i, line.findch(i, ';') - 1)      << std::endl
              << "postfix expression: "  << postfix(line.substr(i, line.findch(i, ';'))) << std::endl
	      << "Prefix  expression: "  << prefix (line.substr(i, line.findch(i, ';'))) << std::endl
	      << "Assembly:\n"           << assembler(outFile, postfix(line.substr(i, line.findch(i, ';'))) + " ;") << std::endl;
      fromFile >> line;
      outFile << std::endl;
    }
  }

  outFile.close();
  fromFile.close();
  return 0;  
}
