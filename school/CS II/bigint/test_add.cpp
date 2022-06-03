// bigint Test Program
//
// Tests:  int constructor, uses ==
//
// NEED TO IMPLEMENT
//
#include <iostream>
#include <cassert>
#include "bigint.hpp"


//===========================================================================
int main () {
    {

        // VERY INCOMPLETE set of tests.


        //------------------------------------------------------
        // Setup fixture
        bigint left(0);
        bigint right(0);
        bigint result;

        // Test 
        result = left + right;

        // Verify
        assert(left   == 0);
        assert(right  == 0);
        assert(result == 0);
    }

    {
      //------------------------------------------------------
      // Setup fixture
      bigint left(1);
      bigint right(0);
      bigint result;

      // Test
      result = left + right;

      // Verify
      assert(left   == 1);
      assert(right  == 0);
      assert(result == 1);
    }
    {
      //------------------------------------------------------
      // Setup fixture
      bigint left(1);
      bigint right(1);
      bigint result;

      // Test
      result = left + right;

      // Verify
      assert(left   == 1);
      assert(right  == 1);
      assert(result == 2);
    }

    //assert(1 == 2); //WRONG. This will fail, of course.
                    //You need to add more test cases here. Remove this assert.
    {
      // Setup fixture
      bigint left(199);
      bigint right(1);
      bigint result;

      // Test
      result = left + right;

      // Verify
      assert(left   == 199);
      assert(right  == 1);
      assert(result == 200);
    }
    {
      //------------------------------------------------------
      // Setup fixture
      bigint left(297);
      bigint right(4);
      bigint result;

      // Test
      result = left + right;

      // Verify
      assert(left   == 297);
      assert(right  == 4);
      assert(result == 301);
    }
    {
      //------------------------------------------------------
      // Setup fixture
      bigint left("9223372036854775807");
      bigint right(204);
      bigint result;

      // Test
      result = left + right;

      // Verify
      assert(left   == "9223372036854775807");
      assert(right  == 204);
      assert(result == "9223372036854776011");
    }
    {
      //------------------------------------------------------
      // Setup fixture
      bigint left(5);
      bigint right(5);
      bigint result;

      // Test
      result = left + right;

      // Verify
      assert(left   == 5);
      assert(right  == 5);
      assert(result == 10);
    }
    {
      //------------------------------------------------------
      // Setup fixture
      bigint left("999999999999999999999999999999999999999999");
      bigint right(1);
      bigint result;

      // Test
      result = left + right;

      // Verify
      assert(left   == "999999999999999999999999999999999999999999");
      assert(right  == 1);
      assert(result == "1000000000000000000000000000000000000000000");
    }
    {
      //------------------------------------------------------
      // Setup fixture
      bigint left(238);
      bigint right(231);
      bigint result;

      // Test
      result = left + right;

      // Verify
      assert(left   == 238);
      assert(right  == 231);
      assert(result == 469);
    }
    {
      //------------------------------------------------------
      // Setup fixture
      bigint left("5555555555555555555");
      bigint right("4444444444444444445");
      bigint result;

      // Test
      result = left + right;

      // Verify
      assert(left   == "5555555555555555555");
      assert(right  == "4444444444444444445");
      assert(result == "10000000000000000000");
    }
    {
      //------------------------------------------------------
      // Setup fixture
      bigint left("65461346145413648148265269527192972197821597638296397821941693276532974621972915293471");
      bigint right(0);
      bigint result;

      // Test
      result = left + right;

      // Verify
      assert(left   == "65461346145413648148265269527192972197821597638296397821941693276532974621972915293471");
      assert(right  == 0);
      assert(result == "65461346145413648148265269527192972197821597638296397821941693276532974621972915293471");
    }
    {
      //------------------------------------------------------
      // Setup fixture
      bigint left(24);
      bigint right(77);
      bigint result;

      // Test
      result = left + right;

      // Verify
      assert(left   == 24);
      assert(right  == 77);
      assert(result == 101);
    }
    {
      //------------------------------------------------------
      // Setup fixture
      bigint left(50);
      bigint right(50);
      bigint result;

      // Test
      result = left + right;

      // Verify
      assert(left   == 50);
      assert(right  == 50);
      assert(result == 100);
    }

    {
      //------------------------------------------------------
      // Setup fixture
      bigint left(50);
      bigint right(50);
      bigint result;

      // Test
      result = left + right;

      // Verify
      assert(left   == 50);
      assert(right  == 50);
      assert(result == 100);
    }
    {
      //------------------------------------------------------
      // Setup fixture
      bigint left(456);
      bigint right(654);
      bigint result;

      // Test
      result = left + right;

      // Verify
      assert(left   == 456);
      assert(right  == 654);
      assert(result == 1110);
    }


    //Add test cases as needed.

    
    
    std::cout << "Done with testing addition." << std::endl;
}

