// Test File for String
//
// Tests []
//
//

#include "string.hpp"
#include <cassert>

//=============================================================
int main() {
  {
    // Test
    String s1("abc");

    // Verify
    assert(s1[1] == 'b');
    std::cout<< "s1 == "    << s1    << std::endl 
             << "s1[1] == " << s1[1] << std::endl;
  }
}
