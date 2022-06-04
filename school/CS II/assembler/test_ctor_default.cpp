// Test file for Stack
//
// Tests default constructor
//

#include <iostream>
#include <cassert>
#include "stack.hpp"

int main() {
 
  {

  // Test
  stack<int> s1;
  
  // Verify
  assert(s1.empty());

  }
  
  {

   // Test
   stack<char> s1;

   // Verify
   assert(s1.empty());

  }

  {

   // Test
   stack<String> s1;

   // Verify
   assert(s1.empty());
  
  }
  
  std::cout << "Done testing default constructor" << std::endl;
  return 0;
}
