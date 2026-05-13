// needed for lab
// Mikhail Nesterenko
// 3/18/2022

#include <iostream>
#include <vector>
#include <cstdlib>
#include "CarFactory.hpp"

using std::cout;
using std::endl;
using std::vector;

class CarLot
{
public:
   CarLot();
   // Car *testDriveCar()
   // {
   //    return car4sale_;
   // }

   // if a car is bought, requests a new one
   Car *buyCar()
   {

      Car *bought = car4sale_[currentCar_];
      car4sale_[currentCar_] = factories_[rand() % factories_.size()]->requestCar();
      return bought;
   }

   int lotSize()
   {
      return maxLotSize;
   }
   Car *nextCar()
   {
      Car *car = car4sale_[currentCar_];
      currentCar_ = (currentCar_ + 1) % maxLotSize;
      return car;
   }

private:
   // Car *car4sale_; // single car for sale at the lot
   vector<CarFactory *> factories_;

   vector<Car *> car4sale_;
   int currentCar_;
   int maxLotSize = 8;
};

CarLot::CarLot()
{
   // creates 2 Ford factories and 2 Toyota factories
   factories_.push_back(new FordFactory());
   factories_.push_back(new ToyotaFactory());
   factories_.push_back(new FordFactory());
   factories_.push_back(new ToyotaFactory());

   // gets the first car for sale
   // car4sale_ = factories_[rand() % factories_.size()]->requestCar();
   for (int i = 0; i < maxLotSize; ++i)
   {
      car4sale_.push_back(factories_[rand() % factories_.size()]->requestCar());
   }
}

CarLot *carLotPtr = nullptr; // global pointer instantiation

// test-drives a car
// buys it if Toyota
void toyotaLover(int id)
{
   if (carLotPtr == nullptr)
      carLotPtr = new CarLot();

   // Car *toBuy = carLotPtr->testDriveCar();

   // cout << "Jill Toyoter" << id << endl;
   // cout << "test driving "
   //      << toBuy->getMake() << " "
   //      << toBuy->getModel();

   // if (toBuy->getMake() == "Toyota")
   // {
   //    cout << " love it! buying it!" << endl;
   //    carLotPtr->buyCar();
   // }
   // else
   //    cout << " did not like it!" << endl;

   cout << "Jill Toyoter" << id << endl;
   for (int i = 0; i < carLotPtr->lotSize(); ++i)
   {
      Car *buy = carLotPtr->nextCar();
      cout << " test driving "
           << buy->getMake() << " "
           << buy->getModel();
      if (buy->getMake() == "Toyota")
      {
         cout << " love it! buying it!" << endl;
         carLotPtr->buyCar();
         return;
      }
      else
         cout << " did not like it!" << endl;
   }
   cout << "Didn't like the car left without buying anything!" << endl;
}

// test-drives a car
// buys it if Ford
void fordLover(int id)
{
   if (carLotPtr == nullptr)
      carLotPtr = new CarLot();

   // Car *toBuy = carLotPtr->testDriveCar();

   // cout << "Jack Fordman " << id << endl;
   // cout << " test driving "
   //      << toBuy->getMake() << " "
   //      << toBuy->getModel();

   // if (toBuy->getMake() == "Ford")
   // {
   //    cout << " love it! buying it!" << endl;
   //    carLotPtr->buyCar();
   // }
   // else
   //    cout << " did not like it!" << endl;
   cout << "Jack Fordman " << id << endl;
   for (int i = 0; i < carLotPtr->lotSize(); ++i)
   {
      Car *buy = carLotPtr->nextCar();
      cout << " test driving "
           << buy->getMake() << " "
           << buy->getModel();
      if (buy->getMake() == "Ford")
      {
         cout << " love it! buying it!" << endl;
         carLotPtr->buyCar();
         return;
      }
      else
         cout << " did not like it!" << endl;
   }
   cout << "Didn't like the car left without buying anything!" << endl;
}

int main()
{
   srand(time(nullptr));

   const int numBuyers = 20;
   for (int i = 0; i < numBuyers; ++i)
      if (rand() % 2 == 0)
         toyotaLover(i);
      else
         fordLover(i);
}
