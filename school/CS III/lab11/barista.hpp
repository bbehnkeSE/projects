// Observer design pattern example using Coffee Shack
// Brian Behnke
// 11/17/2021

#ifndef BARISTA_HPP
#define BARISTA_HPP

#include "coffeeShack.hpp"

#include <unordered_map>
#include <iostream>
#include <iomanip>

class Barista;


class Customer
{
public:
    Customer(Barista* bar) : bar_(bar) {}

    std::string getName()  const { return name_; }
    Barista*    getBar()   const { return bar_; }
    Drink*      getOrder() const { return order_; }

    void        setName (const std::string& name) { name_ = name; }
    void        setOrder(Drink* order)            { order_ = order; }
    void        notify  (Drink*);

private:
    std::string name_;
    Barista* bar_;
    Drink* order_;
};


class Barista
{
public:
    Barista() {}

    Drink* getOrder()    { return customers_.begin()->second; }
    bool   noCustomers() { return customers_.empty(); }

    void   completeOrder(Drink* d) { d->complete(); notifyCustomers(d); }
    void   giveOrder    (Customer* c);
    void   takeOrder();

private:
    void notifyCustomers(Drink* d);

private:
    std::unordered_map<Customer*, Drink*> customers_;
};


//
// Customer definitions
//

void Customer::notify(Drink* order)
{
    if(order_ == order)
    {
        bar_->giveOrder(this);
    }
}


//
// Barista definitions
//

void Barista::takeOrder()
{
    std::cout << "Welcome to Coffee Shack, can I get you [l]arge, [m]edium, or [s]mall coffee? ";
    char size; std::cin >> size;
    std::cout << std::endl;

    Coffee cof;

    if(size == 'l') { cof.setType(DrinkType::large); }
    if(size == 'm') { cof.setType(DrinkType::medium); }
    if(size == 's') { cof.setType(DrinkType::small); }

    char adds;
    while(adds != 'n')
    {
        std::cout << "Would you like to add [s]prinkles, milk [f]oam, or [n]ot? ";
        std::cin >> adds;

        if(adds == 's') { Sprinkle(&cof).getAdds(); }
        if(adds == 'f') { MilkFoam(&cof).getAdds(); }
    }

    std::cout << "And what is the name for this order? ";
    std::string name; std::cin >> name;

    Customer cust(this);
    cust.setName(name);
    cust.setOrder(&cof);

    std::cout << "That will be $"
              << std::fixed
              << std::setprecision(2)
              << cof.getPrice()
              << ", please."
              << std::endl;

    // ***Seg fault here*** // 
    customers_.insert(std::make_pair(&cust, &cof));
}


void Barista::giveOrder(Customer* c)
{
    customers_.erase(c);
}


void Barista::notifyCustomers(Drink* d)
{
    std::string size;
    if(d->getType() == DrinkType::large)  { size = "large"; }
    if(d->getType() == DrinkType::medium) { size = "medium"; }
    if(d->getType() == DrinkType::small)  { size = "small"; }

    std::cout << size 
              << " coffee ";

    if(d->getAdds() != "") 
    { 
        std::cout << "with "
                  << d->getAdds();
    }
    std::cout << "is ready.";

    for(auto customer: customers_)
    {
        customer.first->notify(d);
    }
}


#endif  // BARISTA_HPP