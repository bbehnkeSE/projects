// Customer pattern, pull method
// Mikhail Nesterenko
// 11/11/2014

#include <unordered_set>
#include <iostream>
#include <string>


using std::string;
// using std::set;
using std::cout; using std::endl;

//
// abstract classes describing the mechanism 
// of subscription and notification
// 

// class Barista; // forward class declaration

class Customer{
public:
   Customer(class Barista* s);
   virtual void notify() const = 0;
};


class Barista{
public: 
   void registerCustomer(Customer *o) {views_.insert(o);}
   void deregisterCustomer(Customer *o) {views_.erase(o);}
   void notifyCustomers() const {
      for(auto e: views_) e->notify();
   }
private:
   std::unordered_set <Customer *> views_;
};


Customer::Customer(Barista *s){
   s->registerCustomer(this);
}


//
// concrete classes describing the content 
// of Barista/Customer
//

class ConcreteBarista;

class ConcreteCustomer: public Customer {
public:
   ConcreteCustomer(const string &, ConcreteBarista*);
   void notify() const override;
private:
   string name_;
   ConcreteBarista *s_;
};

class ConcreteBarista: public Barista {
public:
   ConcreteBarista(const string &name): name_(name) {}
   void changeName(const string &name) {name_=name; notifyCustomers();}
   const string& getName() const {return name_;}
private:
   string name_;
};

ConcreteCustomer::ConcreteCustomer
      (const string &name, ConcreteBarista* s): name_(name), s_(s),
						Customer(static_cast<Barista*>(s)){}

void ConcreteCustomer::notify() const {
   cout << "Customer " << name_ << " reports "
	<< "Barista changed name to: " 
	<< s_->getName() 
	<< endl;
}


int main() {
   ConcreteBarista subj("Billy");
   ConcreteCustomer obOne("Joe", &subj), 
                    obTwo("Jane", &subj);

   subj.changeName("Will");

   subj.deregisterCustomer(&obOne);
   subj.changeName("Bill");

   subj.deregisterCustomer(&obTwo);
   subj.registerCustomer(&obOne);
   subj.changeName("William");
}