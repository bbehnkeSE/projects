// vector and list algorithms with objects in containers
// Mikhail Nesterenko, Brian Behnke
// 9/28/2021

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <string>
#include <list>
#include <map>


class Student {
public:
   Student(std::string firstName, std::string lastName): 
      firstName_(firstName), lastName_(lastName) {}
 
   // move constructor, not really needed, generated automatically
   Student(Student && org):
      firstName_(move(org.firstName_)),
      lastName_(move(org.lastName_))
   {}
  
   // force generation of default copy constructor
   Student(const Student & org) = default;
   
   std::string print() const { return firstName_ + " " + lastName_; }

   // Checks if student is alread in roster. If so, adds course to student.
   friend bool checkRoster(const std::map<Student, std::list<std::string>>&, const Student&);

   // needed for unique() and for remove()
   friend bool operator== (Student left, Student right){
      return left.lastName_ == right.lastName_ &&
	   left.firstName_ == right.firstName_;
   }

   // needed for sort()
   friend bool operator< (Student left, Student right){
      return left.firstName_ < right.firstName_ ||
	     (left.firstName_ == right.firstName_ && 
	      left.lastName_ < right.lastName_);
   }
private:
   std::string firstName_;
   std::string lastName_;
};


// reading a list from a fileName
void readRoster(std::map<Student, std::list<std::string>>& roster, std::string fileName);  
// printing a list out
void printRoster(const std::map<Student, std::list<std::string>>& roster);


int main(int argc, char* argv[]){
   if (argc <= 1) { 
      std::cout << "usage: " << argv[0] 
      << " list of courses, dropouts last" 
      << std::endl; exit(1);
   }
   std::map<Student, std::list<std::string>> studentEntries;
   
   for(int i = 1; i < argc - 1; ++i) {
      readRoster(studentEntries, argv[i]);
   }

   std::cout << "All students\n" << "first name, last name: courses enrolled\n"; 
   printRoster(studentEntries);
   std::cout << std::endl;

   std::cout << "All students, dropouts removed and sorted\n" << "first name, last name: courses enrolled\n";
   std::map<Student, std::list<std::string>> dropouts;
   readRoster(dropouts, argv[argc - 1]);
   for(const auto& dropout: dropouts) {
      studentEntries.erase(dropout.first);
   }

   printRoster(studentEntries);

   return 0;
}


void readRoster(std::map<Student, std::list<std::string>>& roster, std::string fileName){
   std::ifstream course(fileName);
   if(!course.is_open()) {
      std::cout << "Unable to open file: " << fileName << ". Exiting..." << std::endl;
      exit(1);
   }
   std::string first, last, courseName(fileName.substr(0, fileName.find('.')));
   while(course >> first >> last) {
      Student newStudent(first, last);
      auto it = roster.find(newStudent);

      if(it == roster.end()) {
         std::list<std::string> courses;
         courses.push_back(courseName);
         roster.insert(std::make_pair(newStudent, courses));
      }
      else {
         it->second.push_back(courseName);
      }
   }
   course.close();
}


// printing a map out
void printRoster(const std::map<Student, std::list<std::string>>& roster) {
   for(const auto& student: roster) {
      std::cout << student.first.print() << ": ";
      for(const auto& course: student.second) {
         std::cout << course << " ";
      }
      std::cout << std::endl;
   }
}