// Brian Behnke
// cs23001
// String ADT

#include "string.hpp"
#include <cassert>

// Constructors

String::String() {
  str = new char[1];
  str[0] = 0;
  stringSize = 1;
}

String::String(char ch) {
  str = new char[2];
  str[0] = ch;
  str[1] = 0;
  stringSize = 2;
}

String::String(const char ch[]) {
  stringSize = 0;
  while(ch[stringSize] != 0) { ++stringSize; }
  ++stringSize;
  str = new char[stringSize];
  str[stringSize - 1] = 0;
  int i = 0;
  while(ch[i] != 0) { 
    str[i] = ch[i];
    ++i;
  }
}

String::String(const String& actual) {
  stringSize = actual.stringSize;
  str = new char[stringSize];
  for(int i = 0; i < stringSize; ++i)
    str[i] = actual.str[i];
}

/*
String::String(String&& actual) {  // Move constructor // Avoids copies, saves clock cycles
  str = actual.str;
  stringsize = actual.stringsize;
  actual.str = 0;
  actual.stringsize = 0;
}
*/

String::~String() {
  if(str != nullptr)
    delete [] str; 
}

String::String(int i) {
  str = new char[i];
  str[0] = 0;
  stringSize = i;
}

String::String(int a, const char ch[]) {
  stringSize = a;
  str = new char[stringSize];
  int i = 0;
  while(ch[i] != 0) {
    str[i] = ch[i];
    ++i;
  }
  str[i] = 0;
}

// Methods

int toInt(const String& s) {
  int result = 0;
  int i = 0;
  while(i < s.length()) {
    result *= 10;
    result = s[i] - '0';
    ++i;
  }
  return result;
}

std::vector<String> String::split(char ch) const {
  std::vector<String> v;
  int i = 0;
  int j = findch(i, ch);
  if(j == -1){
    v.push_back(*this);
    return v;
  }
  while(j != -1) {
    j = findch(i, ch);
    if(j != -1) {
      v.push_back(substr(i, j - 1));
      i = j + 1;
    }
  }
  v.push_back(substr(i, length() - 1));
  return v;
}

void String::swap(String& rhs) {
  char *tmp = str;
  str = rhs.str;
  rhs.str = tmp;
  int tmpStringSize = stringSize;
  stringSize = rhs.stringSize;
  rhs.stringSize = tmpStringSize;
}

void String::resetCapacity(int a) {
  char *tmp = new char[a];
  int smaller = stringSize;
  if(a < stringSize) smaller = a;
  for(int i = 0; i < smaller; ++i)
    tmp[i] = str[i];
  stringSize = a;
  delete [] str;
  str = tmp;
}

int String::capacity() const { return stringSize - 1; }
int String::length  () const {
  int result = 0;
  while(str[result] != 0) ++result;
  return result;
}

int String::findch(int start, char ch) const {
  if((start < 0) || (start >= length())) return -1;
  int i = start;
  while(str[i] != 0) {
    if(str[i] == ch) return i;
    ++i;
  }
  return -1;
}

int String::findstr(int start, const String& s) const {
  if((start < 0) || (start > length() - s.length())) return -1;
  if(length() < s.length()) return -1;
  int slength = s.length();
  int i = start;
  while((str[i] != 0) && (i <= length() - slength)) {
    if(s == substr(i, i + slength - 1)) return i;
    ++i;
  }
  return -1;
}

String String::substr(int start, int end) const {
  String result;
  if(start <  0)        return String();
  if(start >  end)      return String();
  if(end  >= length()) { 
    for(int i = start; i < length(); ++i) 
      result = result + str[i];
  }
  else {
    for(int i = start; i <= end; ++i) 
      result = result + str[i];
  }
  return result;
}

// String operator overloads


String& String::operator=(String rhs) {
  swap(rhs);
  return *this;
}

/*
// Move semantics only pay off when constructors call "new"

String& String::operator=(const String &rhs) {  // Copy assignment
  if(str == rhs.str) return *this;  // Protect against self-assignment
  delete [] str;
  stringsize = rhs.stringsize;
  str = new char[stringsize];
  int i = 0;
  while(str.str[i] != 0) {
    str[i] = rhs.str[i];
    ++i;
  }
  str[i] = 0;
  return *this;
}

// R-value reference so copy constructor isn't called
String& String::operator=(String &&rhs) {  // Move assignment 
  swap(rhs);
  return *this;
}
*/

bool String::operator==(const String& rhs) const {
  int i = 0;
  while((str[i] != 0) && (str[i] == rhs.str[i])) ++i;
  return str[i] == rhs.str[i];
}

String String::operator+(const String& rhs) const {
  String result(capacity() + rhs.capacity() + 1, str);
  int offset = result.length();
  int i = 0;
  while(rhs.str[i] != 0) {
    result.str[offset] = rhs.str[i];
    ++offset;
    ++i;
  }
  result.str[offset] = 0;
  return result;
}

String& String::operator+=(const String& rhs)  {
  int offset = length();
  int i = 0;
  while(rhs.str[i] != 0) {
    str[offset] = rhs.str[i];
    ++i;
    ++offset;
  }
  str[offset] = 0;
  return *this;
}

bool String::operator<(const String& rhs) const {
  int i = 0;
  while((str[i] != 0) && (rhs.str[i] != 0) && (str[i] == rhs.str[i])) ++i;
  return str[i] < rhs.str[i];
}

char String::operator[](int index) const {
  assert(index >= 0);
  assert(index < length());
  return str[index];
}

char& String::operator[](int index) {
  assert(index >= 0);
  assert(index < length());
  return str[index];
}

// Friend functions

std::ostream& operator<<(std::ostream& out, const String& rhs) {
  for(int i = 0; i < rhs.length(); ++i)
    out << rhs.str[i];
  return out;
}

std::istream& operator>>(std::istream& in, String& rhs) {
  char buf[500];
  if(!in.eof())
    in.getline(buf, 500);
  else
    buf[0] = 0;
  rhs = String(buf);
  return in;
} 

// Free functions

bool   operator>= (const String& lhs, const String& rhs) { return !(lhs < rhs); }
bool   operator>  (const String& lhs, const String& rhs) { return  rhs < lhs;   }
bool   operator!= (const String& lhs, const String& rhs) { return !(lhs        == rhs);}
bool   operator== (const char ch [] , const String& rhs) { return  String(ch)  == rhs ;}
bool   operator== (      char ch    , const String& rhs) { return  String(ch)  == rhs ;}
bool   operator<  (const char lhs[] , const String& rhs) { return  String(lhs) <  rhs ;}
bool   operator<  (      char lhs   , const String& rhs) { return  String(lhs) <  rhs ;}
String operator+  (const char lhs[] , const String& rhs) { return  String(lhs) +  rhs ;}
String operator+  (      char lhs   , const String& rhs) { return  String(lhs) +  rhs ;}
bool   operator<= (const String& lhs, const String& rhs) { return  (lhs < rhs) || (lhs == rhs); }

