// Test file for Stack
//
// Tests assignment operator/swap()
//

#include <iostream>
#include <cassert>
#include "string.hpp"
#include "stack.hpp"

int main() {
  {

    // Test
    stack<int> s1;
    s1.push(10);

    stack<int> s2 = s1;

    // Verify
    assert(!s2.empty());
    assert(s2.top() == 10);

  }

  {

    // Test
    stack<int> s1;
    s1.push(5);
    s1.push(6);

    stack<int> s2;
    s2 = s1;
    
    // Verify
    assert(!s2.empty());
    assert(s2.top() == 6);
    assert(s2.pop() == 6);
    assert(s2.top() == 5);
    assert(s2.pop() == 5);
    assert(s2.empty());

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

    stack<char> s2 = s1;

    // Verify
    assert(!s2.empty());
    assert(s2.top() == 'd');
    assert(s2.pop() == 'd');
    assert(s2.top() == 'l');
    assert(s2.pop() == 'l');
    assert(s2.pop() == 'r');
    assert(s2.pop() == 'o');
    assert(s2.pop() == 'W');
    assert(s2.pop() == ' ');
    assert(s2.pop() == 'o');
    assert(s2.pop() == 'l');
    assert(s2.pop() == 'l');
    assert(s2.pop() == 'e');
    assert(s2.pop() == 'H');
    assert(s2.empty());

  }

  {

    // Test
    stack<String> s1;
    s1.push("Hello");
    s1.push("World");

    stack<String> s2 = s1;

    // Verify
    assert(!s2.empty());
    assert(s2.top() == "World");
    assert(s2.pop() == "World");
    assert(s2.top() == "Hello");
    assert(s2.pop() == "Hello");
    assert(s2.empty());

  }
  std::cout << "Done testing assign/swap()" << std::endl;
  return 0;
}
