// implementation basic hashmap (unordered container)
// Mikhail Nesterenko, Brian Behnke: adapted from Proc C++
// 4/15/2014

#ifndef HASHMAP_HPP
#define HASHMAP_HPP

#include <iostream>
#include <algorithm>
#include <cstddef>
#include <utility>
#include <functional>
#include <vector>
#include <list>


//////////////////////////////////////////
// hash function implemented as a class
//////////////////////////////////////////

// any Hash Class must provide 
// two methods: hash() and numBuckets().
template <typename T>
class DefaultHash {
public:
    DefaultHash(size_t numBuckets = defaultNumBuckets);
    size_t hash(const T& key) const;
    size_t numBuckets() const { return numBuckets_; }

private:
    // default number of buckets in the hash
    static const size_t defaultNumBuckets = 101; 
    size_t numBuckets_;
};

template <typename T>
DefaultHash<T>::DefaultHash(size_t numBuckets): numBuckets_(numBuckets) {}


// uses the division method for hashing.
// treats the key as a sequence of bytes, sums the ASCII
// values of the bytes, and mods the total by the number
// of buckets.
// note, this function does not work for C++ strings
template <typename T>
size_t DefaultHash<T>::hash(const T& key) const {
    size_t res = 0;
    for (size_t i = 0; i < sizeof(key); ++i) {
        const unsigned char b = 
        *(reinterpret_cast<const unsigned char *>(&key) + i);
        res += b;
    }
    return res % numBuckets_;
}


////////////////////////////////////////////////
// container class
////////////////////////////////////////////////

template <typename Key, typename Value, 
    typename Compare = std::equal_to<Key>,
    typename Hash = DefaultHash<Key>>
class hashmap{

public:
    typedef std::pair<const Key, Value> Element;

    // constructor
    // invokes constructors for comparison and hash objects
    hashmap(const Compare& comp = Compare(), 
        const Hash& hash = Hash());

    Element* find(const Key& x);                            // returns pointer to element with key x,
                                                            // nullptr if not found
    std::pair<Element*, bool> insert(const Element& x);     // inserts the key/value pair 
    std::pair<Element*, bool> erase(const Key& x);          // erases element with key x, if exists
    Value& operator[] (const Key& x);                       // returns reference on value of
                                                            // element with key, inserts if does not exist

    size_t getNumBuckets() { return hash_.numBuckets(); }
    void rehash(size_t);

private:

    // helper function for various searches
    typename std::list<Element>::iterator findElement(const Key& x, const size_t bucket);

    size_t size_;   // number of elements in the container
    Compare comp_;  // comparison functor, equal_to by default
    Hash hash_;     // hash functor 

    // hash contents: vector of buckets
    // each bucket is a list containing key->value pairs
    std::vector<std::list<Element>> elems_;
};


////////////////////////////////////////////////
// container member functions
////////////////////////////////////////////////

// Construct elems_ with the number of buckets.
template <typename Key, typename Value, typename Compare, typename Hash>
hashmap<Key, Value, Compare, Hash>::hashmap(
const Compare& comp, const Hash& hash):
    size_(0), comp_(comp), hash_(hash) {
        elems_ = std::vector<std::list<Element>>(hash_.numBuckets());
}


// helper function
template <typename Key, typename Value, 
        typename Compare, typename Hash>
typename std::list<std::pair<const Key, Value>>::iterator // return type
hashmap<Key, Value, Compare, Hash>::findElement(const Key& x, size_t bucket){

    // look for the key in the bucket
        for (auto it = elems_[bucket].begin(); it != elems_[bucket].end(); ++it) {
            if (comp_(it->first, x)) {
                return it;
            }
        }

    return elems_[bucket].end(); // element not found
}


// returns a pointer to the element with key x
// returns nullptr if no element with this key
template <typename Key, typename Value, typename Compare, typename Hash>
typename hashmap<Key, Value, Compare, Hash>::Element* // return value type
hashmap<Key, Value, Compare, Hash>::find(const Key& x) {

    size_t bucket = hash_.hash(x);
    auto it=findElement(x, bucket);    // use the findElement() helper   

    if (it != elems_[bucket].end())
        // found the element. Return a pointer to it.
        return &(*it);  // dereference the iterator to list 
                        // then take the address of list element

    else // didn't find the element -- return nullptr
        return nullptr;
}


// finds the element with key x, inserts an
// element with that key if none exists yet. Returns a reference to
// the value corresponding to that key.
template <typename Key, typename Value, typename Compare, typename Hash>
std::pair<typename hashmap<Key, Value, Compare, Hash>::Element*, bool>   // Return type
hashmap<Key, Value, Compare, Hash>::insert(const Element& x) {

    std::pair<Element*, bool> result;
    size_t bucket = hash_.hash(x.first);   
    auto it = find(x.first);    // try to find the element

    // if not found, insert a new one.
    if (it == nullptr) {
        ++size_;
        elems_[bucket].push_back(x);
        result.first = &(*it);
        result.second = true;
        return result;
    }
    result.first = &(*it);
    result.second = false;
    return result;
}


// removes the Element with key x, if it exists
template <typename Key, typename Value, typename Compare, typename Hash>
std::pair<typename hashmap<Key, Value, Compare, Hash>::Element*, bool>   // Return type
hashmap<Key, Value, Compare, Hash>::erase(const Key& x) {

    std::pair<Element*, bool> result;
    size_t bucket = hash_.hash(x);
    auto it = findElement(x, bucket);    // try to find the element

    if(it != elems_[bucket].end()) {     // element found
        it = elems_[bucket].erase(it);
        --size_;

        if(it != elems_[bucket].end()) { // another elem in bucket
            result.first = &(*it);
            result.second = true;
            return result;
        }

        // checks elems_ for next nonempty bucket
        auto vecIt = std::find_if(elems_.begin() + (bucket + 1), elems_.end(), [](std::list<Element> elem) {
            return !elem.empty();
        });

        if(vecIt != elems_.end()) {     // found another nonempty bucket
            bucket = vecIt - elems_.begin();
            it = elems_[bucket].begin();
            result.first = &(*it);
            result.second = true;
            return result;
        }

        // no other buckets
        result.first = nullptr;
        result.second = true;
        return result;
    }
    // element not found
    result.first = nullptr;
    result.second = false;
    return result;
}


// returns reference to value of element with key x,
// inserts if does not exist
template <typename Key, typename Value, typename Compare, typename Hash>
Value& hashmap<Key, Value, Compare, Hash>::operator[] (const Key& x) {

    std::pair<Element*, bool> newPair = insert(std::make_pair(x, Value()));

    newPair.first = find(x);
    return newPair.first->second;
}


template <typename Key, typename Value, typename Compare, typename Hash>
void hashmap<Key, Value, Compare, Hash>::rehash(size_t n) {
    if(n > hash_.numBuckets()) {
        hash_ = n;
        std::vector<std::list<Element>> tmp = elems_;

        std::for_each(tmp.begin(), tmp.end(), [&](std::list<Element> it) {
            std::for_each(it.begin(), it.end(), [&](Element el) {
                insert(el);
            });
        });
    }
    else {
        std::cout << "n must be greater than current number of buckets.";
        exit(1);
    }
}

#endif // HASHMAP_HPP