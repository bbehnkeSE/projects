#ifndef WORDLIST_HPP
#define WORDLIST_HPP

#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>

class WordOccurrence {
public:
    WordOccurrence(const std::string& word="", int num=0);
    
    bool matchWord(const std::string& word) { return word_ == word; }; // returns true if word matches stored
    void increment()                        { ++num_; };               // increments number of occurrences
    std::string getWord() const             { return word_; }; 
    int getNum()          const             { return num_; };

private:
    std::string word_;
    int num_;
};

class WordList{
public:
    // add copy constructor, destructor, overloaded assignment
    WordList  (int size = 0);
    WordList  (const WordList&);
    ~WordList ();

    WordList& operator=(WordList);
    void swap(WordList&);

    void addWord(const std::string&);
    void print();

    // implement comparison as friend
    friend void sortArray  (const WordList&);   // Uses std::sort()
    friend bool comparison (const WordOccurrence&, const WordOccurrence&);
    friend bool equal      (const WordList&, const WordList&);

private:
    WordOccurrence *wordArray_; // a dynamically allocated array of WordOccurrences
                                // may or may not be sorted
    int size_;
};

#endif