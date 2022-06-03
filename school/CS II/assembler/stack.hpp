#ifndef CS2_STACK_HPP_
#define CS2_STACK_HPP_
////////////////////////////////////////////////////////////////////////////
//
// File: stack.hpp
//
// Programmer:
// Updated:    10/2019
//
//
// Do not change the names of the classes or methods.  Otherwise, instructor
//  tests will not work.
//

#include <new>
#include "../string/string.hpp"

////////////////////////////////////////////////////////////////////////////
//
template <typename T>
class Node {
public:
  T data;
  Node *next;
  Node() : next(0) {}
  Node(const T& x) : data(x), next(0) {}
};


////////////////////////////////////////////////////////////////////////////
// CLASS INV:
//
//    
template <typename T>
class stack {
public:
  stack     () : tos(0) {}
  stack     (const stack<T>&);
  ~stack    ();
  void      swap      (stack<T>&);
  stack<T>& operator= (stack<T> rhs) { swap(rhs); return *this; }
  bool      empty     () const { return tos == 0; }
  bool      full      () const { return false; }
  T         top       () const { return tos -> data; }
  T         pop       ();
  void      push      (const T&);

private:
  Node<T>   *tos;
};

// ctor/dtor

template<typename T>
stack<T>::~stack() {
  Node<T> *tmp;
  while(tos != 0) {
    tmp = tos;
    tos = tos -> next;
    delete tmp;
  }
}

template <typename T>
stack<T>::stack(const stack<T>& actual) : stack() {
  Node<T> *tmp = actual.tos;
  Node<T> *roboRalph;
  while(tmp != 0) {
    if(tos == 0) {
      tos = new Node<T>(tmp -> data);
      roboRalph = tos;
    } else {
      roboRalph -> next = new Node<T>(tmp -> data);
      roboRalph = roboRalph -> next;
    }
    tmp = tmp -> next;
  }
}

// Methods

template<typename T>
void stack<T>::push(const T& a) {
  Node<T> *nTop = new Node<T>(a);
  if(empty()) {
    tos = nTop;
  } else {
    nTop -> next = tos;
    tos = nTop;
  }
}

template <typename T>
T stack<T>::pop() {
  T result = tos -> data;
  Node<T> *tmp = tos;
  tos = tos -> next;
  delete tmp;
  return result;
}

template <typename T>
void stack<T>::swap(stack<T>& rhs) {
  Node<T> *tmp = tos;
  tos = rhs.tos;
  rhs.tos = tmp;
}

#endif

