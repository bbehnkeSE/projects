// vector and list algorithms with objects in containers
// Mikhail Nesterenko, Brian Behnke
// 9/28/2021

#include <fstream>
#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <cstdlib>

class Student {
public:
   Student(std::string firstName, std::string lastName, std::string course): 
      firstName_(firstName), lastName_(lastName), courses_{course} {}
 
   // move constructor, not really needed, generated automatically
   Student(Student && org):
      firstName_(move(org.firstName_)),
      lastName_(move(org.lastName_)),
      courses_(move(org.courses_))
   {}
  
   // force generation of default copy constructor
   Student(const Student & org) = default;
   
   std::string print() const;
   std::string getCourse() const { return courses_.front(); };

   void addCourse(const std::string& course) { courses_.push_back(course); }

   // Checks if student is alread in roster. If so, adds course to student.
   friend bool checkRoster(const std::list<Student>&, const Student&);

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
   std::list<std::string> courses_;
};


// reading a list from a fileName
void readRoster(std::list<Student>& roster, std::string fileName);  
// printing a list out
void printRoster(const std::list<Student>& roster);


int main(int argc, char* argv[]){
   if (argc <= 1) { 
      std::cout << "usage: " << argv[0] 
      << " list of courses, dropouts last" 
      << std::endl; exit(1);
   }
   std::list<Student> studentEntries;
   
   for(int i = 1; i < argc - 1; ++i) {
      readRoster(studentEntries, argv[i]);
   }

   std::cout << "All students\n" << "first name, last name: courses enrolled\n"; 
   printRoster(studentEntries);
   std::cout << std::endl;

   std::cout << "All students, dropouts removed and sorted\n" << "first name, last name: courses enrolled\n";
   std::list<Student> dropouts;
   readRoster(dropouts, argv[argc - 1]);
   for(auto it = dropouts.begin(); it != dropouts.end(); ++it) {
      studentEntries.remove(*it);
   }
   studentEntries.sort();

   printRoster(studentEntries);

   return 0;
}


// Formats student data for printing
std::string Student::print() const {
   std::string fullString, courseList;
   for(auto courses: courses_) {
      courseList += courses + " ";
   }
   return fullString = firstName_ + " " + lastName_ + ": " + courseList;
}


bool checkRoster(std::list<Student>& roster, const Student& student) {
   for(auto it = roster.begin(); it != roster.end(); ++it) {
      if(*it == student) {
         it->addCourse(student.getCourse());
         return false;
      }
   }
   return true;
}


void readRoster(std::list<Student>& roster, std::string fileName){
   std::ifstream course(fileName);
   if(!course.is_open()) {
      std::cout << "Unable to open file: " << fileName << ". Exiting..." << std::endl;
      exit(1);
   }
   std::string courseName = fileName.substr(0, fileName.find('.'));
   std::string first, last;

   while(course >> first >> last) {
      Student newStudent(first, last, courseName);
      if(checkRoster(roster, newStudent)) {
         roster.push_back(newStudent);
      }
   }
   course.close();
}


// printing a list out
void printRoster(const std::list<Student>& roster){
   for(const auto& student : roster)
      std::cout << student.print() << std::endl;
}