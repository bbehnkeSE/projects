// needed for lab
// Mikhail Nesterenko, Brian Behnke
// 11/3/2021


#include "CarFactory.hpp"

using std::vector;
using std::cout; using std::endl;

class CarLot{
public:
   CarLot();
   
   const int lotSize() { return lotSize_; }
   void nextCar() {
      car4sale_ = factories_[rand()%factories_.size()]->requestCar();
   }

   Car *testDriveCar(){ return car4sale_; }

   // if a car is bought, requests a new one
   Car *buyCar() { 
      Car *bought = car4sale_;
      car4sale_ = factories_[rand()%factories_.size()]->requestCar();
      return bought;
   }

private:
   const int lotSize_ = 10;   // Number of cars on the lot

   Car *car4sale_; // single car for sale at the lot
   // vector<Car *> cars_;
   vector<CarFactory *> factories_;
};


CarLot::CarLot() {
   // creates 2 Ford factories and 2 Toyota factories 
   factories_.push_back(new FordFactory());   
   factories_.push_back(new ToyotaFactory());
   factories_.push_back(new FordFactory());
   factories_.push_back(new ToyotaFactory());

   // gets the first car for sale
   car4sale_ = factories_[rand() % factories_.size()] -> requestCar();
}


CarLot *carLotPtr = nullptr; // global pointer instantiation

// test-drives a car
// buys it if Toyota
void toyotaLover(int id){
   if (carLotPtr == nullptr) {
      carLotPtr = new CarLot();
   }
   const std::array<std::string, 5> models = {"Corolla", "Camry", "Prius", "4Runner", "Yaris"};
   const std::string lovedModel = models[rand() % 5];

   for(int i = 0; i < carLotPtr->lotSize(); ++i) {
      Car *toBuy = carLotPtr -> testDriveCar();

      cout << endl << "Buyer " << id << " wants a Toyota " << lovedModel << endl;
      cout << "test driving " 
         << toBuy->getMake() << " "
         << toBuy->getModel();

      if (toBuy->getMake() == "Toyota" && toBuy->getModel() == lovedModel) {
         cout << " love it! buying it!" << endl;
         carLotPtr -> buyCar();
         return;
      } 
      else {
         cout << " did not like it!" << endl;
         carLotPtr->nextCar();
      }
   }
   return;  // Didn't like any car
}

// test-drives a car
// buys it if Ford
void fordLover(int id){
   if (carLotPtr == nullptr) {
      carLotPtr = new CarLot();
   }
   const std::array<std::string, 4> models = {"Focus", "Mustang", "Explorer", "F-150"};
   const std::string lovedModel = models[rand() % 4];

   for(int i = 0; i < carLotPtr->lotSize(); ++i) {
      Car *toBuy = carLotPtr -> testDriveCar();

      cout  << endl << "Buyer " << id << " wants a Ford " << lovedModel << endl;
      cout << "test driving "
         << toBuy->getMake() << " "
         << toBuy->getModel();

      if (toBuy->getMake() == "Ford" && toBuy->getModel() == lovedModel){
         cout << " love it! buying it!" << endl;
         carLotPtr -> buyCar();
         return;
      } 
      else {
         cout << " did not like it!" << endl;
         carLotPtr->nextCar();
      }
   }
   return;  // Didn't like any car
}


int main() {
   srand(time(nullptr));

   const int numBuyers=10;
   for(int i=0; i < numBuyers; ++i) {
      if(rand()% 2 == 0) {
         toyotaLover(i);
      }
      else {
         fordLover(i);
      }
   }

   return 0;
}