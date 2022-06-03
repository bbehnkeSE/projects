// Test File for String
//
// Tests:  findch()
//
//

#include "string.hpp"

//=============================================================
int main() {
  {
  // Test
  String  s1("abcdefghijko");

  // Verify
  std::cout << "String s1 == " << s1 << std::endl
	    << "'g' is located at position: " << s1.findch(0, 'g')
	    << std::endl; 
  }
}
