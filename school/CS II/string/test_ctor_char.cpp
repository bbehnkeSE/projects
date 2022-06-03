// String Test Program
//
// Tests:  char constructor and << operator.
// Uses:   ==
//
//

#include "string.hpp"
#include <cassert>

//==============================================================

int main() {
  {
    // Test
    String s1('a');

    // Verify
    assert(s1 == 'a');
    std::cout << "a == "
	      << s1
	      << std::endl;
  }
}
