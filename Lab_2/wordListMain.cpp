// Dipen Thapa
//  Lab 2 - word count

#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include "WordList.hpp"

using std::cin;
using std::cout;
using std::endl;
using std::ifstream;
using std::string;

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        cout << "Try again using two arguments" << endl;
        return 1;
    }
    ifstream inFile(argv[1]);

    if (!inFile)
    {
        cout << "Error openning files. TRY AGAIN" << endl;
        return 1;
    }
    WordList allWord;
    string word;
    char letter;
    while (inFile.get(letter))
    {
        if (isalnum(letter)) // check if the character is alphanumeric or not
        {
            word = word + letter;
        }
        else
        {
            if (!word.empty()) // if the word is not empty
            {
                allWord.addWord(word);
                word.clear();
            }
        }
    }
    allWord.print();
    inFile.close();
}
