// Test File for String
//
// Tests:  findstr()
//
//

#include "string.hpp"
#include <cassert>

//=====================================================
int main() {
  {
    // Test
    String s1("Please work.");
    std::cout << "find str s1 = " << s1 << std::endl;

    // Verify
    std::cout << s1.findstr(0, "work") << std::endl;
    //assert(s1.findstr(0, "work") == 6);
  }
}
