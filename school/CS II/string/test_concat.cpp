// String Test File
//
// Tests:  String + String and << operator
// Uses:   ==
//
//

#include "string.hpp"
#include <cassert>

//===================================================
int main() {

  {
    // Test
    char a = 'd';
    String s1("abc");

    // Verify
    s1 = s1 + a;
    assert(s1 == "abcd");
    std::cout << "s1 + char == " << s1 << std::endl;
  }

  {
    // Test
    String s1("abc");
    String s2("xyz");
    String s3;

    // Verify
    s3 = s1 + s2;
    assert(s3 == "abcxyz");
    std::cout << "s1 + s2 == " << s3 << std::endl;
  }

  {
    // Test
    String s1("abc");
    String s2("xyz");

    // Verify
    s1 += s2;
    //assert(s1 == "abcxyz");
    std::cout << "+= Version:" << std::endl;
    std::cout << "s1 + s2 == " << s1 << std::endl;
  }

  {
    // Test
    String s1("abc");
    char a = 'x';
    char b = 'y';

    // Verify
    s1 += a;
    s1 += b;
    assert(s1 == "abcxy");
    std::cout << "+= Version:" << std::endl;
    std::cout << "s1 + a == " << s1 << std::endl;
  }
}
