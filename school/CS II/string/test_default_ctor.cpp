// String test program
//
// Tests:  default constructor, uses ==
//
//
#include "string.hpp"
#include <cassert>

//=============================================================================
int main() {
  // Test
  String s;

  // Verify
  assert(s == '\0');
  std::cout << "String is empty." << std::endl;
}
