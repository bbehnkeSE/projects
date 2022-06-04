// vector and list algorithms
// Mikhail Nesterenko, Brian Behnke
// 9/28/2021

#include <fstream>
#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <cstdlib>
#include <algorithm>

// reading a std::list from a fileName
void readRoster(std::vector<std::list<std::string>>& roster, std::string fileName);  

// checks in student is already in roster
int checkRoster(const std::vector<std::list<std::string>>&, const std::string&);

// printing a std::list out
void printRoster(const std::list<std::string>& roster);

int main(int argc, char* argv[]) {
   if (argc <= 1) { 
      std::cout << "usage: " << argv[0] 
      << " list of courses, dropouts last" 
      << std::endl; exit(1);
   }
   std::vector<std::list<std::string>> studentEntries;

   // Fill studentEntries with names from files.
   for(int i = 1; i < argc - 1; ++i) {
      readRoster(studentEntries, argv[i]);
   }

   // Print all students, including dropouts
   std::cout << "All students\n" << "first name, last name: courses enrolled\n";
   for(auto students: studentEntries) {
      printRoster(students);
   }
   std::cout << std::endl;

   // Removes dropouts
   std::vector<std::list<std::string>> dropouts;
   readRoster(dropouts, argv[argc - 1]);
   for(int i = 0; i < dropouts.size(); ++i) {
      int dropoutLoc = checkRoster(studentEntries, dropouts[i].front());
      if(dropoutLoc != -1) {
         studentEntries.erase(studentEntries.begin() + dropoutLoc);
      }
   }

   // Print all students, excluding dropouts
   std::cout << "All students, dropouts removed and sorted\n" << "first name, last name: courses enrolled\n";
   std::sort(studentEntries.begin(), studentEntries.end());
   for(auto students: studentEntries) {
      printRoster(students);
   }

   return 0;   
}

// Function definitions
// reading in a file of names into a list of strings
void readRoster(std::vector<std::list<std::string>>& roster, std::string fileName) {
   std::ifstream course(fileName);
   if(!course.is_open()) {
      std::cout << "Unable to open file: " << fileName << ". Exiting..." << std::endl;
      exit(1);
   }
   std::string courseName = fileName.substr(0, fileName.find('.'));
   std::string first, last;

   while(course >> first >> last) {
      std::string studentName(move(first + " " + last));
      int nameLoc = checkRoster(roster, studentName);    // Will equal -1 if student isn't in roster.
      if(nameLoc == -1) {
         std::list<std::string> newEntry;
         newEntry.push_back(studentName);
         newEntry.push_back(courseName);
         roster.push_back(newEntry);
      }
      else {
         roster[nameLoc].push_back(courseName);
      }
   }
   course.close();
}


// Checks vector for student. If found, returns index, else returns -1.
int checkRoster(const std::vector<std::list<std::string>>& roster, const std::string& studentName) {
   for(int i = 0; i < roster.size(); ++i) {
      if(roster[i].front() == studentName) {
         return i;
      }
   }
   return -1;
}


// printing a list out
void printRoster(const std::list<std::string>& roster) {
   for(auto it = roster.begin(); it != roster.end(); ++it) {
      if(*it == roster.front()) {
         std::cout << *it << ": ";
      }
      else {
         std::cout << *it << " ";
      }
   }
   std::cout << std::endl;
}