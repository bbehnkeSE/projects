// Brian Behnke
// bigint
// cs23001

// Allows storage of integers larger than int can hold

#ifndef  BIGINT_HPP
#define  BIGINT_HPP

#include <iostream>
#include <cassert>
#include <fstream>

const int CAPACITY  = 400;

class bigint {
public:
  bigint();
  bigint(int);
  bigint(const char[]);

  void   debugPrint (std::ostream&)     const;
  bigint times_digit(int)               const;
  bigint times_10   (int)               const;

  bigint operator*  (const bigint&)     const;
  bigint operator+  (const bigint&)     const;
  bool   operator== (const bigint&)     const;
  int    operator[] (int)               const;

  friend std::ostream& operator<<(std::ostream& out, const bigint& rhs);

private:
  int intArr[CAPACITY];
};

std::istream& operator>>(std::istream&, bigint&);

#endif
