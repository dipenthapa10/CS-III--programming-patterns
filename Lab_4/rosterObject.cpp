// vector and list algorithms with objects in containers
// Mikhail Nesterenko
// 9/10/2018

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
             (left.lastName_ == right.lastName_ &&
              left.firstName_ < right.firstName_);
   }

   // move construtor
   Student(Student &&org) noexcept
   {
      firstName_ = move(org.firstName_);
      lastName_ = move(org.lastName_);
      course_ = move(org.course_);
   }

   void addCourse(string &courseName)
   {
      course_.push_back(courseName);
   }

private:
   string firstName_;
   string lastName_;
   list<string> course_;
};

// reading a list from a fileName
void readRoster(list<Student> &roster, string fileName);
// printing a list out
void printRoster(const list<Student> &roster);

int main(int argc, char *argv[])
{

   if (argc <= 1)
   {
      cout << "usage: " << argv[0]
           << " list of courses, dropouts last" << endl;
      exit(1);
   }

   list<Student> studentEntries;
   for (int i = 1; i < argc - 1; ++i)
   {
      string courseFile = argv[i];
      list<Student> roster;
      readRoster(roster, courseFile);
      string courseName = courseFile.substr(0, courseFile.find("."));

      for (auto &student : roster)
      {
         bool found = false;
         // to check if student exist already
         for (auto &entry : studentEntries)
         {
            if (entry == student)
            {
               found = true;
               entry.addCourse(courseName);
               break;
            }
         }
         if (!found) // if it doesn't exicst
         {

            Student newStudent = move(student);
            newStudent.addCourse(courseName);
            studentEntries.push_back(move(newStudent));
         }
      }
   }

   list<Student> dropouts;
   readRoster(dropouts, argv[argc - 1]);
   for (auto &drop : dropouts)
   {
      for (auto searchName = studentEntries.begin(); searchName != studentEntries.end();)
      {
         if (*searchName == drop)
         {
            searchName = studentEntries.erase(searchName);
         }
         else
         {
            searchName++;
         }
      }
   }

   studentEntries.sort();
   printRoster(studentEntries);
}

void readRoster(list<Student> &roster, string fileName)
{
   ifstream course(fileName);
   string first, last;
   while (course >> first >> last)
      roster.push_back(Student(first, last));
   course.close();
}

// printing a list out
void printRoster(const list<Student> &roster)
{
   for (const auto &student : roster)
   {
      cout << student.print() << endl;
   }
}
