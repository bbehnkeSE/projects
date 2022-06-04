//
//
// File:        logentry.cpp  
//       
// Version:     1.0
// Date:        
// Author:      
//
// Description: Class implementation for a log entry.
//
//

////////////////////////////////////////////////////////////
#include <iostream>
#include <vector>

#include "string.hpp" 
#include "logentry.hpp"

//////////////////////////////////////////////////////////
// REQUIRES:
// ENSURES:
//
Time::Time(String s) {
    std::vector<String> hms = s.split(':');
    hour   = s.toInt(hms[0]);
    minute = s.toInt(hms[1]);
    second = s.toInt(hms[2]);
}

//////////////////////////////////////////////////////////
// REQUIRES:
// ENSURES:
//
Date::Date(String s) {
    std::vector<String> dmy = s.split('/');
    day   = dmy[0];
    month = dmy[1];
    year  = s.toInt(dmy[2]);
}

////////////////////////////////////////////////////////// 
// REQUIRES:  
// ENSURES: 
//
LogEntry::LogEntry(String s) {
    std::vector<String> vec = s.split(' ');
    if(vec.size() < 10) {
      String dati;
      String req = vec[5] + vec[6] + vec[7];
      host            = vec[0];
      dati            = vec[3];
      request         = req;
      status          = vec[8];
      number_of_bytes = s.toInt(vec[9]);
      Date da(dati.substr(0, dati.findch(0, ':')));
      Time ti(dati.substr(dati.findch(0, ':'), dati.findch(0, ' ')));
    }
}

////////////////////////////////////////////////////////// 
// REQUIRES:  
// ENSURES: 
//
std::vector<LogEntry> parse(std::istream& in) {
    char tmp[300];
    std::vector<LogEntry> result;
    while(!in.eof()) {
      in.getline(tmp, 300);
      if(!in.eof()) {
        result.push_back(String(tmp));
      }
    }
    return result;
}

//////////////////////////////////////////////////////////
// REQUIRES:
// ENSURES:
//
std::ostream& operator<<(std::ostream& out, const LogEntry& rhs) {
  out << "Host: "    << rhs.host            << std::endl;
  out << "Date: "    << rhs.date            << std::endl;
  out << "Time: "    << rhs.time            << std::endl;
  out << "Request: " << rhs.request         << std::endl;
  out << "Status: "  << rhs.status          << std::endl;
  out << "Bytes: "   << rhs.number_of_bytes << std::endl;
  return out;
} 

////////////////////////////////////////////////////////// 
// REQUIRES:  
// ENSURES: 
//
void output_all(std::ostream& out, const std::vector<LogEntry>& vec) {
  int i = 0;
  while(i != vec.size() + 1) {
    out << vec[i];
    ++i;
  }
  std::cout << '\n';
}

////////////////////////////////////////////////////////// 
// REQUIRES:  
// ENSURES: 
//
void by_host(std::ostream& out, const std::vector<LogEntry>& vec) {
  int i = 0;
  while(i != vec.size() + 1) {
    out << vec[i].host;
    ++i;
  }
  std::cout << '\n';
}

////////////////////////////////////////////////////////// 
// REQUIRES:  
// ENSURES: 
//
int byte_count(const std::vector<LogEntry> &) {
    
    return 0;
}

