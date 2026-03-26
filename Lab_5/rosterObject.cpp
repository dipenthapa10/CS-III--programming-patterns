// vector and list algorithms with objects in containers
// Mikhail Nesterenko
// 9/10/2018

#include <fstream>
#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <cstdlib>
#include <map>

using std::cout;
using std::endl;
using std::getline;
using std::ifstream;
using std::list;
using std::map;
using std::move;
using std::string;
using std::vector;

class Student
{
public:
   Student(string firstName, string lastName) : firstName_(firstName), lastName_(lastName) {}

   // force generation of default copy constructor
   Student(const Student &org) = default;

   string print() const
   {
      string full = firstName_ + " " + lastName_ + ":";
      for (auto &course : course_)
      {
         full = full + course + " ";
      }
      return full;
   }

   // needed for unique() and for remove()
   friend bool operator==(Student left, Student right)
   {
      return left.lastName_ == right.lastName_ &&
             left.firstName_ == right.firstName_;
   }

   // needed for sort()
   friend bool operator<(Student left, Student right)
   {
      return left.firstName_ < right.firstName_ ||
             (left.firstName_ == right.firstName_ &&
              left.lastName_ < right.lastName_);
   }

   // add funtion
   void addCourse(string const &courseName)
   {
      course_.push_back(courseName);
   }

private:
   string firstName_;
   string lastName_;
   list<string> course_;
};

// reading a list from a fileName
void readRoster(map<Student, list<string>> &roster, string fileName);
// printing a list out
void printRoster(const map<Student, list<string>> &roster);

int main(int argc, char *argv[])
{

   if (argc <= 1)
   {
      cout << "usage: " << argv[0]
           << " list of courses, dropouts last" << endl;
      exit(1);
   }

   map<Student, list<string>> studentEntries;
   for (int i = 1; i < argc - 1; ++i)
   {
      string courseFile = argv[i];
      map<Student, list<string>> roster;
      readRoster(roster, courseFile);
      string courseName = courseFile.substr(0, courseFile.find("."));

      for (auto &student : roster)
      {

         studentEntries[student.first].push_back(courseName);
      }
   }

   // reading in dropouts
   map<Student, list<string>> dropouts;
   readRoster(dropouts, argv[argc - 1]);
   for (auto &dropName : dropouts)
   {
      studentEntries.erase(dropName.first);
   }

   printRoster(studentEntries);
}

void readRoster(map<Student, list<string>> &roster, string fileName)
{
   ifstream course(fileName);
   string first, last;
   while (course >> first >> last)
   {
      Student name(first, last);
      roster[name];
   }

   course.close();
}

// printing a list out
void printRoster(const map<Student, list<string>> &roster)
{
   for (const auto &student : roster)
   {
      cout << student.first.print();
      for (const auto &course : student.second)
      {
         cout << course << " ";
      }
      cout << endl;
   }
}
