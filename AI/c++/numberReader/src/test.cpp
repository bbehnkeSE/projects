#include "headers/trainNetwork.hpp"

int main()
{
    Convolutional test(std::make_tuple(3, 3, 3), 2, 2);

    test.debugPrint();
}