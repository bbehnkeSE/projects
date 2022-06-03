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
	bigint b2(123456789);
	bigint b3(2);
	bigint b4(987654321);
	bigint b0(5);

        // Test 
        bi = bi.times_10(1);

        // Verify
        assert(bi == 30);  
    
        // Test
        b2 = b2.times_10(3);

        // Verify
        assert(b2 == "123456789000");

        // Test
        b3 = b3.times_10(20);

        // Verify
        assert(b3 == "200000000000000000000");

        // Test
        b4 = b4.times_10(50);

        // Verify
        assert(b4 == "98765432100000000000000000000000000000000000000000000000000");

        // Test
        b0 = b0.times_10(0);

        // Verify
        assert(b0 == 5);

    //Add test cases as needed.

    std::cout << "Done testing times_10" << std::endl;
}

