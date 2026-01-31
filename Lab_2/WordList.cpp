#include <iostream>
#include <algorithm>
#include "WordList.hpp"
using std::cout;
using std::endl;
using std::string;

// Word Occurence

// constructor
WordOccurrence ::WordOccurrence(const string &word, int num)
{
    word_ = word;
    num_ = num; // number of occurence
}
bool WordOccurrence ::matchWord(const string &word) // returns true if word matches stored
{
    if (word_ == word)
    {
        return true;
    }
    else
    {
        return false;
    }
}
void WordOccurrence ::increment() // increments number of occurrences
{
    ++num_;
}
string WordOccurrence ::getWord() const
{
    return word_;
}
int WordOccurrence ::getNum() const
{
    return num_;
}

// Word List

// add copy constructor, destructor, overloaded assignment
WordList::WordList()
{
    size_ = 0;
    wordArray_ = new WordOccurrence[size_];
}
WordList ::~WordList()
{
    delete[] wordArray_;
}

WordList &WordList ::operator=(const WordList &rhs) // overload assignment
{
    if (this != &rhs)
    {
        delete[] wordArray_;
        size_ = rhs.size_;

        wordArray_ = new WordOccurrence[size_]; // allocate new memory
        for (int i = 0; i < rhs.size_; i++)     // copying
        {
            wordArray_[i] = rhs.wordArray_[i];
        }
    }
    return *this;
}

WordList ::WordList(const WordList &rhs) // copy construcotr
{
    size_ = rhs.size_;
    wordArray_ = new WordOccurrence[size_];
    for (int i = 0; i < size_; i++)
    {
        wordArray_[i] = rhs.wordArray_[i];
    }
}

// implement comparison as friend
bool equal(const WordList &lhs, const WordList &rhs)
{
    if (lhs.size_ != rhs.size_)
    {
        return false;
    }

    for (int i = 0; i < lhs.size_; i++)
    {
        if (lhs.wordArray_[i].getWord() != rhs.wordArray_[i].getWord())
        {
            return false;
        }
        if (lhs.wordArray_[i].getNum() != rhs.wordArray_[i].getNum())
        {
            return false;
        }
    }
    return true;
}

void WordList::addWord(const string &word)
{
    // if the word exist increment the count
    for (int i = 0; i < size_; ++i)
    {
        if (wordArray_[i].matchWord(word))
        {
            wordArray_[i].increment();
            return;
        }
    }
    WordOccurrence *temp = wordArray_;
    wordArray_ = new WordOccurrence[size_ + 1];
    for (int i = 0; i < size_; ++i)
    {
        wordArray_[i] = temp[i];
    }
    wordArray_[size_] = WordOccurrence(word, 1);
    delete[] temp;
    size_++;
}

void WordList::print()
{
    // sorting
    for (int i = 0; i < size_ - 1; ++i)
    {
        int maxIndex = i;
        // first sorts by counts
        for (int j = i + 1; j < size_; ++j)
        {
            if (wordArray_[j].getNum() < wordArray_[maxIndex].getNum())
            {
                maxIndex = j; // smaller count
            }

            // if count equla sorts by alphabetical
            else if (wordArray_[j].getNum() == wordArray_[maxIndex].getNum())
            {
                if (wordArray_[j].getWord() < wordArray_[maxIndex].getWord())
                {
                    maxIndex = j; // same count, alphabetical
                }
            }
        }
        // Swap

        WordOccurrence temp = wordArray_[i];
        wordArray_[i] = wordArray_[maxIndex];
        wordArray_[maxIndex] = temp;
    }

    // Print sorted array
    for (int i = 0; i < size_; ++i)
    {
        std::cout << wordArray_[i].getWord() << " " << wordArray_[i].getNum() << std::endl;
    }
}
