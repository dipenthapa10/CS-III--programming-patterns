// drink class to be used in Coffee Shack lab
// Mikhail Nesterenko
// 11/7/2022

#include <string>
#include <iostream>
#include <vector>
using std ::cout;
using std::endl;
using std::string;
using std::vector;
enum class DrinkType
{
   small,
   medium,
   large
};

// decorator
class Drink
{
public:
   Drink(DrinkType type = DrinkType::small, int price = 0) : type_(type), price_(price) {}
   virtual int getPrice() const
   {
      if (type_ == DrinkType::small)
         return 5;
      else if (type_ == DrinkType::medium)
         return 7;
      else
         return 10;
   }
   virtual std::string getName() const
   {
      if (type_ == DrinkType::small)
         return "small coffee with ";
      else if (type_ == DrinkType::medium)
         return "medium coffee with ";
      else
         return "large coffee withc";
   }
   virtual void prepare(string baristaName)
   {
      preparer_ = baristaName;
   }
   virtual string getPreparer() const { return preparer_; }

private:
   int price_;
   DrinkType type_;
   string preparer_;
};

//  decorator

class Sugar : public Drink
{
public:
   Sugar(Drink *d) : wrapped_(d) {}
   int getPrice() const override
   {
      return wrapped_->getPrice() + 1;
   }
   string getName() const override
   {
      return wrapped_->getName() + "sugar";
   }
   void prepare(string name) override
   {
      wrapped_->prepare(name);
   }
   string getPreparer() const override
   {
      return wrapped_->getPreparer();
   }

private:
   Drink *wrapped_;
};

class Cream : public Drink
{
public:
   Cream(Drink *d) : wrapped_(d) {};
   int getPrice() const override
   {
      return wrapped_->getPrice() + 2;
   }
   string getName() const override
   {
      return wrapped_->getName() + "cream";
   }
   void prepare(string name) override
   {
      wrapped_->prepare(name);
   }
   string getPreparer() const override
   {
      return wrapped_->getPreparer();
   }

private:
   Drink *wrapped_;
};

class Honey : public Drink
{
public:
   Honey(Drink *d) : wrapped_(d) {};
   int getPrice() const override
   {
      return wrapped_->getPrice() + 3;
   }
   string getName() const override
   {
      return wrapped_->getName() + "honey";
   }
   void prepare(string name) override
   {
      wrapped_->prepare(name);
   }
   string getPreparer() const override
   {
      return wrapped_->getPreparer();
   }

private:
   Drink *wrapped_;
};

// observer

class Customer
{
public:
   Customer(const string &name, Drink *drink) : name_(name), drink_(drink) {}
   void notify(Drink *drinkReady)
   {

      if (drinkReady == drink_)
      {
         cout << name_ << ", your " << drink_->getName() << " is ready. It will be $" << drink_->getPrice() << " please. " << " It is prepared by " << drink_->getPreparer() << endl;
         cout << "This is " << name_ << ", I got my coffee, thank you!" << endl;
         cout << endl;
      }
   }
   Drink *getDrink() const
   {
      return drink_;
   }

private:
   string name_;
   Drink *drink_;
};

// Chain of resposibilties

class Barista
{
public:
   Barista(Barista *nextHandler = nullptr) : nextHandler_(nextHandler) {}
   virtual Drink *handleCoffee(char request, Drink *drink)
   {
      if (nextHandler_)
         return nextHandler_->handleCoffee(request, drink);
      return drink;
   }
   // observer functions
   void registerCustomer(Customer *cust)
   {
      customers_.push_back(cust);
   }

   void notifyEveryone(Drink *readyDrink)
   {
      for (auto it = customers_.begin(); it != customers_.end();)
      {
         if ((*it)->getDrink() == readyDrink)
         {
            (*it)->notify(readyDrink);
            it = customers_.erase(it); // removed so they are not notifies again
         }
         else
            ++it;
      }
   }

private:
   Barista *nextHandler_;
   vector<Customer *> customers_;
};

class JuniorrBarista : public Barista
{
public:
   JuniorrBarista(Barista *nextHandler = nullptr) : Barista(nextHandler) {}

   Drink *handleCoffee(char request, Drink *drink) override
   {
      return Barista::handleCoffee(request, drink);
   }

private:
};

class SeniorBarista : public Barista
{
public:
   SeniorBarista(Barista *nextHandler = nullptr) : Barista(nextHandler) {}

   Drink *handleCoffee(char request, Drink *drink) override
   {
      if (request == 's')
      {
         return new Sugar(drink);
      }
      else if (request == 'c')
      {
         return new Cream(drink);
      }
      else
      {
         return Barista::handleCoffee(request, drink); // invoking base class function
      }
   }

private:
};

class Manager : public Barista
{
public:
   Manager(Barista *nextHandler = nullptr) : Barista(nextHandler) {}
   Drink *handleCoffee(char request, Drink *drink)
   {
      if (request == 'h')
      {
         return new Honey(drink);
      }
      return Barista::handleCoffee(request, drink);
   }

private:
};
