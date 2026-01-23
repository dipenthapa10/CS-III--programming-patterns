// Dipen Thapa
// Lab 1
// Procedural Diff

#include <iostream>
#include <fstream>
#include <string>

using std::cout;
using std::endl;
using std::getline;
using std::ifstream;
using std::string;

int main(int argc, char *argv[])
{
    // argument check

    if (argc != 3)
    {
        cout << "Error: Try writing ./main file1_name file2_name" << endl;
        return 1;
    }

    ifstream inFile1(argv[1]);
    ifstream inFile2(argv[2]);

    if (!inFile1 || !inFile2)
    {
        cout << "Error opening file" << endl;
        return 1;
    }

    string file1, file2;
    int lineNo = 1;

    while (true)
    {
        bool read1 = (bool)getline(inFile1, file1);
        bool read2 = (bool)getline(inFile2, file2);

        if (!read1 && !read2)
            break;
        if (!read1)
            file1 = "";
        if (!read2)
            file2 = "";

        if (file1 != file2)
        {
            cout << argv[1] << ": " << lineNo << ": " << file1 << endl;
            cout << argv[2] << ": " << lineNo << ": " << file2 << endl;

            // creating the space same as the first file so that we can get the exact location of the error
            int position = 0;
            while (position < file1.length() && position < file2.length() && file1[position] == file2[position])
            {
                position++;
            }

            string space = string(argv[1]) + ": " + std::to_string(lineNo) + ": ";

            // proper space create for caret
            string caret = string(space.length(), ' ');

            if (position >= 0)
            {
                caret = caret + string(position, ' ') + '^';
            }

            cout << caret << endl;
        }

        lineNo++;
    }

    return 0;
}
