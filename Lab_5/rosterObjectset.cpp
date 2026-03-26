// vector and list algorithms with objects in containers
// Mikhail Nesterenko
// 9/10/2018

#include <fstream>
#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <cstdlib>
#include <set>

using std::cout;
using std::endl;
using std::getline;
using std::ifstream;
using std::list;
using std::move;
using std::set;
using std::string;
using std::vector;

class Student
{
public:
   Student(string firstName, string lastName) : firstName_(firstName), lastName_(lastName) {}

   // force generation of default copy constructor
   Student(const Student &org) = default;

   string print() const { return firstName_ + ' ' + lastName_; }

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

private:
   string firstName_;
   string lastName_;
};

// reading a list from a fileName
void readRoster(set<Student> &roster, string fileName);
// printing a list out
void printRoster(const set<Student> &roster);

int main(int argc, char *argv[])
{

   if (argc <= 1)
   {
      cout << "usage: " << argv[0]
           << " list of courses, dropouts last" << endl;
      exit(1);
   }

   // // vector of courses of students
   // vector <list<Student>> courseStudents;

   // for(int i=1; i < argc-1; ++i){
   //    list<Student> roster;
   //    readRoster(roster, argv[i]);
   //    cout << "\n\n" << argv[i] << "\n";
   //    printRoster(roster);
   //    courseStudents.push_back(move(roster));
   // }

   // set
   set<Student> studentEntries;
   for (int i = 1; i < argc - 1; ++i)
   {
      string courseFile = argv[i];
      set<Student> roster;
      readRoster(roster, courseFile);

      string courseName = courseFile.substr(0, courseFile.find("."));

      for (auto &student : roster)
      {
         studentEntries.insert(student);
      }
   }

   set<Student> dropouts;
   readRoster(dropouts, argv[argc - 1]);
   for (auto &drop : dropouts)
   {
      auto it = studentEntries.find(drop);
      if (it != studentEntries.end())
      {
         studentEntries.erase(it);
      }
   }

   printRoster(studentEntries);

   // // reading in dropouts
   // list<Student> dropouts;
   // readRoster(dropouts, argv[argc-1]);
   // cout << "\n\n dropouts \n"; printRoster(dropouts);

   // list<Student> allStudents;  // master list of students

   // for(auto& lst : courseStudents)
   //   allStudents.splice(allStudents.end(),lst);

   // cout << "\n\n all students unsorted \n";
   //         printRoster(allStudents);

   // allStudents.sort(); // sorting master list
   // cout << "\n\n all students sorted \n"; printRoster(allStudents);

   // allStudents.unique(); // eliminating duplicates
   // cout << "\n\n all students, duplicates removed \n"; printRoster(allStudents);

   // for (const auto& str : dropouts)  // removing individual dropouts
   //    allStudents.remove(str);
   // cout << "\n\n all students, dropouts removed \n"; printRoster(allStudents);
}

void readRoster(set<Student> &roster, string fileName)
{
   ifstream course(fileName);
   string first, last;
   while (course >> first >> last)
      roster.insert(Student(first, last));
   course.close();
}

// printing a list out
void printRoster(const set<Student> &roster)
{
   for (const auto &student : roster)
      cout << student.print() << endl;
}
