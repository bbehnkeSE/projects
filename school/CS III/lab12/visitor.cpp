// demonstrates Visitor Design Pattern and double dispatch
// Mikhail Nesterenko
// 11/29/2014

#include <iostream> 
#include <string> 
#include <vector> 

using std::cout; using std::endl;
using std::string;
using std::vector;

// abstract element
class CarPart{
public:
   virtual void accept(class CarPartVisitor*) = 0;
};


// abstract visitor
class CarPartVisitor{
public:
   virtual void visit(class Engine*) =0;
   virtual void visit(class Transmission*) =0;
   virtual void visit(class Wheel*) =0;
};


// concrete elements

class Engine: public CarPart {
public:
   void accept(CarPartVisitor *v) override {
      v->visit(this);
   }
};

class Transmission: public CarPart {
   void accept(CarPartVisitor *v) override {
      v->visit(this);
   }
};

// stateful element
class Wheel : public CarPart {
public:
   Wheel(const string &place) : place_(place), rotations_(0) {}
   const string &getPlace() const {return place_;}
   void rotate(){++rotations_;}
   int getRotations()const{return rotations_;}
   void accept(CarPartVisitor *v) override {
      v->visit(this);
   }
private:
   const string place_;
   int rotations_;
};

// simple concrete visitor
class Inspector : public CarPartVisitor {
public:
   void visit(Engine *e) override {
      cout << "Inspector checks engine" << endl; 
   }
   void visit(Transmission *t) override { 
      cout << "Inspector checks transmission" << endl; 
   }
   void visit(Wheel *w) override { 
      cout << "Inspector checks "
	   << w->getPlace() << " wheel" 
	   << endl; 
   }
};

// stateful concrete visitor
class Operator : public CarPartVisitor {
public:
   Operator(): ops_(0) {}
   void visit(Engine *e) override { 
      cout << "Operator starts engine; so far ops: " << 
	   ++ops_ << endl;
   }
   void visit(Transmission *t) override {
      cout << "Operator shifts transmission; so far ops: " 
	   << ++ops_ << endl;
   }
   void visit(Wheel *w) override {  
      w->rotate();
      cout << "Operator turns " << w->getPlace() << " wheel " << endl;
      cout << "it was turned " << w->getRotations() << " times" << endl;
      cout << "so far ops: " << ++ops_ << endl;
   }

private:
   int ops_; // number of operations performed
};


int main(){
   vector <CarPart *> parts = {new Transmission,
			       new Engine, 
			       new Wheel("front center"),
			       new Wheel("rear right"),
			       new Wheel("rear left"),
                               new Wheel("steering")};

   vector <CarPartVisitor *> visitors = {new Inspector, new Operator, new Operator};

   for(auto e: parts){
      for(auto v: visitors)
	 e->accept(v); // method is dispatched on 
                       // the basis of types of 
                       // both "e" and "v"
      cout << endl;
   }
}