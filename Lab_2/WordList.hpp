#ifndef WORDLIST_HPP
#define WORDLIST_HPP

#include <string>

using std::string;

class WordOccurrence
{
public:
    WordOccurrence(const string &word = "", int num = 0);
    bool matchWord(const string &); // returns true if word matches stored
    void increment();               // increments number of occurrences
    string getWord() const;
    int getNum() const;
    bool operator<(const WordOccurrence &) const;

private:
    string word_;
    int num_;
};

class WordList
{
public:
    // add copy constructor, destructor, overloaded assignment
    WordList(); // construcotr

    ~WordList(); // destructor

    WordList &operator=(const WordList &); // overload assignment
    WordList(const WordList &);            // copy construcotr

    // implement comparison as friend
    friend bool equal(const WordList &, const WordList &);

    void addWord(const string &);
    void print();

    // Only use for testing purposes
    WordOccurrence *getWords() const { return wordArray_; };
    int getSize() const { return size_; };

private:
    WordOccurrence *wordArray_; // a dynamically allocated array of WordOccurrences
                                // may or may not be sorted
    int size_;                  // number of words stored
};
#endif