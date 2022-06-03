// Test file for Stack
//
// Tests push()/pop()/top()
//

#include <iostream>
#include <cassert>
#include "stack.hpp"

int main() {

  {

    // Test
    stack<int> s1;
    s1.push(10);

    // Verify
    assert(!s1.empty());
    assert(s1.top() == 10);

  }

  {

    // Test
    stack<int> s1;
    s1.push(5);
    s1.push(6);

    // Verify
    assert(!s1.empty());
    assert(s1.top() == 6);
    assert(s1.pop() == 6);
    assert(s1.top() == 5);
    assert(s1.pop() == 5);
    assert(s1.empty());

  }

  {

    // Test
    stack<char> s1;
    s1.push('H');
    s1.push('e');
    s1.push('l');
    s1.push('l');
    s1.push('o');
    s1.push(' ');
    s1.push('W');
    s1.push('o');
    s1.push('r');
    s1.push('l');
    s1.push('d');


    // Verify
    assert(!s1.empty());
    assert(s1.top() == 'd');
    assert(s1.pop() == 'd');
    assert(s1.top() == 'l');
    assert(s1.pop() == 'l');
    assert(s1.pop() == 'r');
    assert(s1.pop() == 'o');
    assert(s1.pop() == 'W');
    assert(s1.pop() == ' ');
    assert(s1.pop() == 'o');
    assert(s1.pop() == 'l');
    assert(s1.pop() == 'l');
    assert(s1.pop() == 'e');
    assert(s1.pop() == 'H');
    assert(s1.empty());

  }

  {

    // Test
    stack<String> s1;
    s1.push("Hello");
    s1.push("World");

    // Verify
    assert(!s1.empty());
    assert(s1.top() == "World");
    assert(s1.pop() == "World");
    assert(s1.top() == "Hello");
    assert(s1.pop() == "Hello");
    assert(s1.empty());

  }
  
  std::cout << "Done testing push()/pop()/top()" << std::endl;
  return 0;
}
