// Collection class template for use with node class template
// Brian Behnke
// 9/22/2021

#ifndef COLLECTION_HPP_
#define COLLECTION_HPP_

#include <iostream>
#include "list.hpp"

template <typename T>
class Collection;

template <typename T>
bool equal(const Collection<T>&, const Collection<T>&);

template <typename T>
class Collection {
public:
    Collection();
    //Collection(const Collection&);
    //~Collection();

    void add(const T&);
    void remove(const T&);
    void print();

    T& last();

    friend bool equal<T>(const Collection&, const Collection&);
    
private:
    node<T> *head, *current;
};


template <typename T>
Collection<T>::Collection() {
    head = new node<T>;
    current = head;
}


// template <typename T>
// Collection<T>::~Collection() {
//     node<T> *tmp;
//     while(list->getNext() != nullptr) {
//         tmp = list->getNext();
//         delete list;
//         list = tmp;
//     }
// }


template <typename T>
void Collection<T>::add(const T& data) {
    node<T> *next = new node<T>;
    if(head->getNext() == nullptr) {
        current = head;
        current->setData(data);
        current->setNext(next);
    }
    else {
        next->setData(data);
        current->setNext(next);
        current = next;
    }
}


template <typename T>
void Collection<T>::remove(const T& data) {
    current = head;
    while(current != nullptr) {
        if(head->getData() == data) {
            head = head->getNext();
            delete current;
            current = head;
        }

        if(current->getNext()->getData() == data) {
            node<T> *tmp = current->getNext();
            current->setNext(current->getNext()->getNext());
            delete tmp;
            current = current->getNext();
        }
        else {
            current = current->getNext();
        }
    }
}


template <typename T>
void Collection<T>::print() {
    for(current = head; current != nullptr; current = current->getNext()) {
        std::cout << current->getData() << " ";
    }
    std::cout << std::endl;
}


template <typename T>
T& Collection<T>::last() {
    T *result;
    current = head;
    while(current->getNext() != nullptr) {
        current = current->getNext();
    }
    *result = current->getData();
    return *result;
}


template <typename T>
bool equal(const Collection<T>& lhs, const Collection<T>& rhs) {
    while(lhs.current != nullptr && rhs.current != nullptr) {
        // Check if lists are same length
        if(lhs.current->getNext() == nullptr && rhs.current->getNext() != nullptr) return false;
        if(lhs.current->getNext() != nullptr && rhs.current->getNext() == nullptr) return false;

        if(lhs.current->getData() != rhs.current->getData()) return false;

        lhs.current->setNext(lhs.current->getNext());
        rhs.current->setNext(lhs.current->getNext());
    }
    return true;
}

#endif // COLLECTION_HPP_