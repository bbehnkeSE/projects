// Brian Behnke
// cs23001
// reads/multiplies bigints from a file

#include "bigint.hpp"

int main() {
  std::ifstream multFile("data1-2.txt");
  if(!multFile.is_open()) {
    std::cout << "Unable to open file." << std::endl;
    return 1;
  }
  bigint b1, b2, b3, b4, b5, b6, b7, b8, b9, b10;
  multFile >> b1;
  multFile >> b2;
  multFile >> b3;
  multFile >> b4;
  multFile >> b5;
  multFile >> b6;
  multFile >> b7;
  multFile >> b8;
  multFile >> b9;
  multFile >> b10;

  std::cout << "bigint #1 = "  << b1          << std::endl
            << "bigint #2 = "  << b2          << std::endl
            << "bigint #3 = "  << b3          << std::endl
            << "bigint #4 = "  << b4          << std::endl
            << "bigint #5 = "  << b5          << std::endl
            << "bigint #6 = "  << b6          << std::endl
            << "bigint #7 = "  << b7          << std::endl
            << "bigint #8 = "  << b8          << std::endl
            << "bigint #9 = "  << b9          << std::endl
            << "bigint #10 = " << b10         << std::endl
            << "bigint 1 * 2 = "  << b1 * b2  << std::endl
            << "bigint 3 * 4 = "  << b3 * b4  << std::endl
            << "bigint 5 * 6 = "  << b5 * b6  << std::endl
            << "bigint 7 * 8 = "  << b7 * b8  << std::endl
            << "bigint 9 * 10 = " << b9 * b10 << std::endl;
  multFile.close();
  return 0;
}
