#include "WordList.hpp"

// WordOccurrence class functions
WordOccurrence::WordOccurrence(const std::string& word, int num) {
    word_ = word;
    num_ = num;
}


// WordList class functions
WordList::WordList(int size) {
    size_ = size;
    wordArray_ = size_ > 0 ? new WordOccurrence[size_] : nullptr;
}

WordList::WordList(const WordList& rhs) {
    size_ = rhs.size_;
    wordArray_ = size_ > 0 ? new WordOccurrence[size_] : nullptr;

    for(int i = 0; i < size_; ++i) {
        wordArray_[i] = rhs.wordArray_[i];
    }
}

WordList::~WordList() {
    delete[] wordArray_;
}

WordList& WordList::operator=(WordList rhs) {
    swap(rhs);
    return(*this);
}

void WordList::swap(WordList& rhs) {
    WordOccurrence *tmp = wordArray_;
    wordArray_ = rhs.wordArray_;
    rhs.wordArray_ = tmp;

    int tmpSize = size_;
    size_ = rhs.size_;
    rhs.size_ = tmpSize;
}

void WordList::addWord(const std::string& word) {
    for(int i = 0; i < size_; ++i) {
        if(wordArray_[i].getWord() == word) {
            wordArray_[i].increment();
            return;
        }
    }
    WordOccurrence wordObj(word);
    wordObj.increment();
    
    WordOccurrence *tmp = new WordOccurrence[size_ + 1];
    for(int i = 0; i < size_; ++i) {
        tmp[i] = wordArray_[i];
    }
    delete[] wordArray_;
    tmp[size_] = wordObj;
    wordArray_ = tmp;
    ++size_;
}

void WordList::print() {
    for(int i = 0; i < size_; ++i) {
        std::cout << wordArray_[i].getWord() << ": " << wordArray_[i].getNum() << std::endl;
    }
}

bool comparison(const WordOccurrence& lhs, const WordOccurrence& rhs) {
    return lhs.getNum() < rhs.getNum();
}

void sortArray(const WordList& words) {
    std::sort(words.wordArray_, words.wordArray_ + words.size_, comparison);
}

bool equal(const WordList& lhs, const WordList& rhs) {
    if(lhs.size_ != rhs.size_) {
        return false;
    }
    for(int i = 0; i < lhs.size_; ++i) {
        if(!lhs.wordArray_[i].matchWord(rhs.wordArray_[i].getWord())) {
            return false;
        }
    }
    return true;
}