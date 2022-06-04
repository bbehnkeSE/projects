// Observer design pattern example using Coffee Shack
// Brian Behnke
// 11/17/2021

#include "barista.hpp"
#include <iostream>
#include <ctime>


int main()
{
    srand(time(nullptr));
    Barista* bar;

    do
    {
        bar->takeOrder();
        if(rand() % 2 != 0)
        {
            bar->takeOrder();
        }
        else
        {
            bar->completeOrder(bar->getOrder());
        }

    } while (!bar->noCustomers());

    if(bar->noCustomers())
    {
        std::cout << "No more customers.\n";
    }
    
    return 0;
}