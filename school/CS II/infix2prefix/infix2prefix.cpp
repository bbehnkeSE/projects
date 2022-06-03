// Brian Behnke
// cs23001 Lab 11
// 11/7/2011
//
// Converts infix to prefix
//

#include <fstream>
#include <iostream>
#include "../assembler/stack.hpp"
#include "../string/string.hpp"

String prefix(String infix) {
  std::vector<String> token = infix.split(' ');
  String right, left, oper;
  stack<String> conversion;
  int i = 0;
  while(token[i] != ';') {
    if(token[i] == ')') {
      right = conversion.pop();
      oper  = conversion.pop();
      left  = conversion.pop();
      conversion.push(oper + ' ' + left + ' ' + right);
    }
    else if(token[i] != '(') {
      conversion.push(token[i]);
    }
    ++i;
  }
  return conversion.pop();
}

int main() {
  std::ifstream fromFile("data3-1.txt");
  if(!fromFile.is_open()) {
    std::cout << "Unable to open file." << std::endl;
    return 1;
  }

  int i = 0;
  String line;
  fromFile >> line;
  while(line.findch(i, ';') != -1) {
    std::cout << "infix   expression: " << line.substr(i, line.findch(i, ';') - 1)     << std::endl
              << "prefix expression: "  << prefix(line.substr(i, line.findch(i, ';'))) << std::endl;
    fromFile >> line;
  }
  fromFile.close();
  return 0;
}

