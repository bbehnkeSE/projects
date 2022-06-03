// bigint Test Program
//
// Tests:  times_10, uses ==
//
// NEED TO IMPLEMENT
//
#include <iostream>
#include <cassert>
#include "bigint.hpp"

//===========================================================================
int main () {
        //------------------------------------------------------
        // Setup fixture
        bigint bi(3);
	bigint b2("555555555555555555");
	bigint b3("2222222222222222222222222222222222222222222222233322222222222222222122222222222222222222232123");
	bigint b4(1);

        // Test 
        bi = bi.times_digit(1);

        // Verify
        assert(bi == 3);
	
        // Test
        b2 = b2.times_digit(2);

        // Verify
        assert(b2 == "1111111111111111110");

        // Test
        b2 = b2.times_digit(0);

        // Verify
        assert(b2 == 0);

        // Test
        bi = bi.times_digit(3);

        // Verify
        assert(bi == 9);

        // Test
        b3 = b3.times_digit(3);

        // Verify
        assert(b3 == "6666666666666666666666666666666666666666666666699966666666666666666366666666666666666666696369");

        // Test
        b4 = b4.times_digit(0);

        // Verify
        assert(b4 == 0);

  std::cout << "Done testing bigint * digit" << std::endl;
}


    //Add test cases as needed.
    

