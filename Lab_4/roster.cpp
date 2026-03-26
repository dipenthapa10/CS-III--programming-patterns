// vector and list algorithms
// Mikhail Nesterenko
// 3/11/2014

#include <fstream>
#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <cstdlib>

using std::cout;
using std::endl;
using std::getline;
using std::ifstream;
using std::list;
using std::move;
using std::string;
using std::vector;

// reading a list from a fileName
void readRoster(list<string> &roster, string fileName);

// printing a list out
void printRoster(const list<list<string>> &roster);

int main(int argc, char *argv[])
{

   if (argc <= 1)
   {
      cout << "usage: " << argv[0]
           << " list of courses, dropouts last"
           << endl;
      exit(1);
   }

   list<list<string>> studentEntries;
   for (int i = 1; i < argc - 1; ++i) // each course file
   {
      string courseFile = argv[i];
      list<string> roster;
      readRoster(roster, courseFile);

      string courseName = courseFile.substr(0, courseFile.find('.'));

      for (auto &studentName : roster) // process each student in roaster
      {
         bool found = false;

         for (auto &entry : studentEntries) // searching if student already exist
         {
            if (entry.front() == studentName) // here we know student exist in studnetentries
            {
               entry.push_back(courseName);
               found = true;
               break;
            }
         }
         if (!found) // if it doesn't exit create a new entry and send it to studententries
         {
            list<string> newEntry;
            newEntry.push_back(studentName);
            newEntry.push_back(courseName);
            studentEntries.push_back(newEntry);
         }
      }
   }

   list<string> dropouts;
   readRoster(dropouts, argv[argc - 1]);
   for (auto &dropName : dropouts)
   {
      for (auto search = studentEntries.begin(); search != studentEntries.end();)
      {
         if (search->front() == dropName)
         {
            search = studentEntries.erase(search);
         }
         else
         {
            ++search;
         }
      }
   }
   studentEntries.sort();
   printRoster(studentEntries);
}

// reading in a file of names into a list of strings
void readRoster(list<string> &roster, string fileName)
{
   ifstream course(fileName);
   string first, last;
   while (course >> first >> last)
      roster.push_back(first + ' ' + last);
   course.close();
}

// printing a list out
void printRoster(const list<list<string>> &roster)
{
   for (const auto &student : roster)
   {
      cout << student.front() << ": ";
      auto iter = student.begin();
      ++iter;
      for (; iter != student.end(); ++iter)
      {
         cout << *iter << " ";
      }
      cout << endl;
   }
}
