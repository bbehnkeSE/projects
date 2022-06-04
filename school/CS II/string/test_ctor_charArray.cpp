// String Test Program
//
// Tests:  char[] constructor and << operator.
// Uses:   ==
//
//

#include "string.hpp"
#include <cassert>

//==============================================================
int main() {
  {
    // Test
    String s1("abc");

    // Varify
    assert(s1 == "abc");
    std::cout << "abc == "
	      << s1
	      << std::endl;
  }
}
