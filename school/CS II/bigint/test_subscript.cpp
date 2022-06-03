// bigint Test Program
//
// Tests:  subscript, uses ==
//
// NEED TO IMPLEMENT
//
#include <iostream>
#include <cassert>
#include "bigint.hpp"

//===========================================================================
int main () {
    
    {
        // Setup
        bigint bi(1234567890);

        // Test 
        int digit  = bi[0];
	int digit2 = bi[7];
	
        // Verify
        assert(bi      == 1234567890);
	assert(digit   == 0);
	assert(bi[1]   == 9);
	assert(bi[2]   == 8);
        assert(bi[3]   == 7);
        assert(bi[4]   == 6);
        assert(bi[5]   == 5);
        assert(bi[6]   == 4);
        assert(digit2  == 3);
        assert(bi[8]   == 2);
        assert(bi[9]   == 1);
    }

    //Add test cases!!

    std::cout << "Done testing subscript." << std::endl;
}

