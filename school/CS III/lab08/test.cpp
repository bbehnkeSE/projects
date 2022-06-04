#include <iostream>
#include <ctime>

int total = 0;
int roll_;

void roll(int dice, int sides)
{
    static int x = 0;
    ++x;
    std::cout << x << std::endl;
}


int main()
{
    int i = 0;
    while(i < 5) 
    {
        roll(0, 0);
        ++i;
    }
    return 0;
}