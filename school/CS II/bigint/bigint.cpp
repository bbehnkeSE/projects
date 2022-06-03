// Brian Behnke
// cs23001
// bigint


#include "bigint.hpp"

// bigint methods

bigint::bigint() {
  for(int i = 0; i < CAPACITY; ++i)
    intArr[i] = 0;
}

bigint::bigint(int num) : bigint() {
  int digit;
  int arrayEnd = CAPACITY;
  while(num > 0) {
    digit = num % 10;
    num = num / 10;
    intArr[arrayEnd - 1] = digit;
    --arrayEnd;
  }
}

bigint::bigint(const char a[]) : bigint() {
  int charSize = 0;
  int arrayEnd = CAPACITY;
  while(a[charSize] != 0) { ++charSize; }
  for(int i = charSize - 1; i >= 0; --i) {
    intArr[arrayEnd - 1] = a[i] - int('0');
    --arrayEnd;
  }  
}

bigint bigint::times_10(int exponent) const {
  bigint tmp;
  bigint moveLeft;
  tmp = *this;
  if(exponent != 0) {
    for(int j = 0; j < exponent; ++j) {
      for(int i = CAPACITY - 2; i >= 0; --i) {
        moveLeft.intArr[i] = tmp.intArr[i + 1];
      }
      tmp = moveLeft;
    }
    return moveLeft;
  }
  else
    return tmp;
}

bigint bigint::times_digit(int a) const {
  int num = 0;
  int digit;
  bigint product = *this;
  for(int i = CAPACITY - 1; i > 0; --i) {
    product.intArr[i] = product.intArr[i] * a + num;
    num = 0;
    if(product.intArr[i] >= 10) {
      digit = product.intArr[i] % 10;
      num = product.intArr[i] / 10;
      product.intArr[i] = digit;
    }
  }
  return product;
}
  
void bigint::debugPrint(std::ostream&) const {
  bool printBar = false;
  for(int i = CAPACITY - 1; i >= 0; --i) {
    if(printBar == true){ std::cout << "|"; }
    std::cout << intArr[i];
    printBar = true;
  }
  std::cout << std::endl;
}

// Operator overloads

std::istream& operator>>(std::istream& in, bigint& rhs) {
  char bigtmp[CAPACITY];
  char tmp = 'a';
  int i = 0;
  while((tmp != ';') && !in.eof()) {
    in >> tmp;
    bigtmp[i] = tmp;
    ++i;
  }
  bigtmp[i - 1] = '\0';
  rhs = bigint(bigtmp);
  return in;
}

std::ostream& operator<<(std::ostream& out, const bigint& rhs) {
  int endOfLine = 0;
  bool pLeadingZero = false;
  for(int i = 0; i < CAPACITY; ++i) {
    if(rhs.intArr[i] != 0) pLeadingZero = true;
    if(pLeadingZero){
      if(endOfLine == 80) {
	out << std::endl;
	endOfLine = 0;
      }
      out << rhs.intArr[i];
      ++endOfLine;
    }
  }
  return out;
}

bool bigint::operator==(const bigint& rhs) const {
  for(int i = 0; i < CAPACITY; ++i)
    if(intArr[i] != rhs.intArr[i]) { return false; }
  return true;
}

bigint bigint::operator+(const bigint& rhs) const {
  int num = 0;
  int digit;
  bigint sum;
  for(int i = CAPACITY; i > 0; --i) {
    sum.intArr[i] = intArr[i] + rhs.intArr[i] + num;
    num = 0;
    if(sum.intArr[i] >= 10) {
      digit = sum.intArr[i] % 10;
      num = sum.intArr[i] / 10;
      sum.intArr[i] = digit;
    }
  }
  return sum;
}

bigint bigint::operator*(const bigint& rhs) const {
  bigint tmp;
  bigint lhs = *this;
  bigint product = 0;
  for(int i = CAPACITY - 1; i > 0; --i) {
    tmp = lhs.times_digit(rhs.intArr[i]);
    product = product + tmp.times_10(CAPACITY - (i + 1));
  }
  return product;
}

int bigint::operator[](int index) const {
  assert(index >= 0);
  assert(index <= CAPACITY);
  return intArr[(CAPACITY - 1) - index];
}
