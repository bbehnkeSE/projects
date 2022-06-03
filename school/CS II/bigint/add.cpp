// Brian Behnke
// cs23001
// reads/adds a bigint from a file

#include "bigint.hpp"

int main() {
  std::ifstream addFile("data1-1.txt");
  if(!addFile.is_open()) {
    std::cout << "Unable to open file." << std::endl;
    return 1;
  }
  bigint b1, b2, b3, b4, b5, b6;
  addFile >> b1;
  addFile >> b2;
  addFile >> b3;
  addFile >> b4;
  addFile >> b5;
  addFile >> b6;
  std::cout << "bigint #1 = " << b1         << std::endl
	    << "bigint #2 = " << b2         << std::endl
	    << "bigint #3 = " << b3         << std::endl
	    << "bigint #4 = " << b4         << std::endl
	    << "bigint #5 = " << b5         << std::endl
	    << "bigint #6 = " << b6         << std::endl
	    << "bigint 1 + 2 = " << b1 + b2 << std::endl
	    << "bigint 3 + 4 = " << b3 + b4 << std::endl
	    << "bigint 5 + 6 = " << b5 + b6 << std::endl;
  addFile.close();
  return 0;
}
