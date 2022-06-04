// Test file for String
//
// Tests substring()
//

#include "string.hpp"
#include <cassert>

//==============================================================
int main() {
  {
    // Test
    String s1("Please work");
    
    // Verify
    std::cout << s1 << std::endl;
    std::cout << s1.substr(0, 6) << std::endl;
  }
}
