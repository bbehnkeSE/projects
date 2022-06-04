// Test File for String
//
// Tests:  length() and capacity() functions
//
//

#include "string.hpp"
#include <cassert>

//=====================================================
int main() {
  {
    // Test
    String s1("abcdefg");
 
    // Verify
    assert(s1.capacity() ==   7);
    assert(s1.length()   ==   7);
    std::cout << "s1 == " << s1 << std::endl
	      << "s1 length == " << s1.length() << std::endl
	      << "s1 capacity == " << s1.capacity() << std::endl; 
  }
}
