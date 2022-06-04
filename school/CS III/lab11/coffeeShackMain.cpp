// Coffee Shack
// Brian Behnke
// 11/17/2021

#include "coffeeShack.hpp"

#include <iostream>
#include <iomanip>


std::string getName();
void shack(const DrinkType&, const std::string&);
void print(const Coffee&, const std::string&, const std::string&);


int main()
{
    char size;
    std::cout << "Welcome to Coffee Shack, can I get you [l]arge, [m]edium, or [s]mall coffee? ";
    std::cin >> size;
    std::cout << std::endl;

    if(size == 'l') { shack(DrinkType::large, "large"); }
    if(size == 'm') { shack(DrinkType::medium, "medium"); }
    if(size == 's') { shack(DrinkType::small, "small"); }
    
    return 0;
}


void shack(const DrinkType& type, const std::string& size)
{
    char adds;
    Coffee c(type);

    while(adds != 'n')
    {
        std::cout << "Would you like to add [s]prinkles, milk [f]oam, or [n]ot? ";
        std::cin >> adds;

        if(adds == 's') { Sprinkle(&c).getAdds(); }
        if(adds == 'f') { MilkFoam(&c).getAdds(); }
    }
    print(c, getName(), size);
}


void print(const Coffee& c, const std::string& name, const std::string& size)
{
    std::cout << name 
              << ", your " 
              << size 
              << " coffee ";

    if(c.getAdds() != "") 
    { 
        std::cout << "with "
                  << c.getAdds();
    }

    std::cout << "is ready. It will be $" 
              << std::fixed
              << std::setprecision(2)
              << c.getPrice() 
              << ", please." 
              << std::endl;
}


std::string getName()
{
    std::string name;
    std::cout << "Can I get your name? ";
    std::cin >> name;
    std::cout << std::endl;

    return name;
}