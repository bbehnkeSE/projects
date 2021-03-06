#ifndef CS23001_UTILITIES_HPP
#define CS23001_UTILITIES_HPP

///////////////////////////////////////////////////////////
// Brian Behnke
// cs23001 
// 11/5/2019 
//
// HPP File to convert infix to postfix/prefix/assembly
//

#include <fstream>
#include <iostream>
#include "stack.hpp" 

String postfix  (String);
String prefix   (String);
String evaluate (String, String, String, std::ostream&, int);
String toString (int);

std::ostream& assembler    (std::ostream&, String);

#endif
