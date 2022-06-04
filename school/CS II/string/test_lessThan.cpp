// Tests File for String
//
// Tests:  <
//
//

#include "string.hpp"
#include <cassert>

//===============================================
int main() {
  {
    // Test
    String s1("abc");
    String s2("xyz");

    // Verify
    assert(s1 < s2);
    std::cout << s1 << " < " << s2 << std::endl;
  }
}
