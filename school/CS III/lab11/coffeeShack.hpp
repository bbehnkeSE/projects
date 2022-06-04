// drink class to be used in Coffee Shack lab
// Mikhail Nesterenko, Brian Behnke
// 11/17/2021

#ifndef COFFEESHACK_HPP
#define COFFEESHACK_HPP

#include <string>

enum class DrinkType {small, medium, large};

class Drink
{
public:
    Drink() {}

    virtual bool        getStatus() const { return false; }
    virtual double      getPrice()  const { return 0.; }
    virtual DrinkType   getType()   const { return DrinkType::small; }
    virtual std::string getAdds()   const = 0;

    virtual std::string setAdds (std::string) { return ""; }
    virtual void        addPrice(double) {}
    virtual void        complete() {}
};


class Coffee: public Drink 
{
public:
    Coffee(DrinkType type = DrinkType::small) : type_(type)
    {
        if(type_ == DrinkType::small)  { price_ = 1.; }
        if(type_ == DrinkType::medium) { price_ = 2.; }
        if(type_ == DrinkType::large)  { price_ = 3.; }
    }

    bool        getStatus() const override { return finished_; }
    double      getPrice()  const override { return price_; }
    DrinkType   getType()   const override { return type_; }
    std::string getAdds()   const override { return adds_; }
    std::string getName()   const          { return name_; }

    std::string setAdds (std::string adds) override { return adds_ += adds; }
    void        complete()                 override { finished_ = true; }
    void        setName (std::string name)          { name_ = name; }
    void        addPrice(double price)              { price_ += price; }
    void        setType (DrinkType type)            { type_ = type; }

private:
    bool finished_;
    double price_ = 0;
    DrinkType type_;

    std::string name_;
    std::string adds_ = "";
};


// Sprinkle decorator
class Sprinkle : public Drink
{
public:
    Sprinkle(Drink* d) : d_(d) {}
    std::string getAdds() const override 
    {
        d_->addPrice(.5);
        return d_->setAdds("sprinkles, ");
    }

private:
    Drink* d_;
};


// Milk foam decorator
class MilkFoam : public Drink
{
public:
    MilkFoam(Drink* d) : d_(d) {}
    std::string getAdds() const override 
    {
        d_->addPrice(.4);
        return d_->setAdds("foam, ");
    }

private:
    Drink* d_;
};


#endif  // COFFEESHACK_HPP