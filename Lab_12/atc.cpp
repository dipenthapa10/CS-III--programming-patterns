// mediator-based air traffic control
// Mikhail Nesterenko
// 11/30/2022

#include <iostream>
#include <set>
#include <vector>
#include <string>
#include <cstdio>
#include <ctime>
#include <algorithm>
#include <map>

// for timed sleep
#include <thread>
#include <chrono>

using std::cin;
using std::cout;
using std::endl;
using std::map;
using std::string;

// abstract mediator
class Controller
{
public:
   virtual void join(class Flight *) = 0;
   virtual void leave(class Flight *) = 0;
   virtual void broadcast() = 0;
   virtual void observe() = 0;
};

// Flyweight D P

class Logo
{
public:
   Logo(const string &name)
   {
      airLineUpper_ = name;
      std::transform(airLineUpper_.begin(), airLineUpper_.end(), airLineUpper_.begin(), ::toupper);
   }
   string getName()
   {
      return airLineUpper_;
   }
   void printTakeOff();
   void printLandind();

private:
   string airLineUpper_; // intrinsic shared state
};

// Flyweight factory
class LogoFactory
{
private:
   static map<string, Logo *> pool_;

public:
   static Logo *getLogo(const string &name)
   {
      if (pool_.find(name) == pool_.end())
      {
         pool_[name] = new Logo(name);
      }
      return pool_[name];
   }
};
map<string, Logo *> LogoFactory::pool_;

// concrete mediator
// tower, runway clearance
class Tower : public Controller
{
public:
   void join(class Flight *) override;
   void leave(class Flight *) override;
   void broadcast() override;
   void observe() override;

private:
   std::set<class Flight *> waiting_;
};

// abstract colleague
class Flight
{
public:
   Flight(Controller *controller) : controller_(controller),
                                    status_(Status::waiting)
   {
      task_ = rand() % 2 ? Task::taxiing : Task::approaching;
      controller_->join(this);
   }
   void receive(const string &msg)
   {
      flightNo_ = airline_ + number_;
      if (msg.find(number_) != string::npos || msg.find("all") != string::npos) // used number_ to avoid crash mayday
      {
         if (msg.find("clear") != string::npos)
         {
            cout << flightNo_ << " roger that, ";
            cout << (task_ == Task::taxiing ? "taking off" : "landing") << endl;
            status_ = Status::cleared;
         }
         else if (msg.find("status") != string::npos)
         {
            cout << flightNo_
                 << (status_ == Status::waiting ? " waiting to " : " cleared to ")
                 << (task_ == Task::taxiing ? "take off" : "land") << endl;
         }
         else
            cout << "Tower, this is " << flightNo_ << " please repeat." << endl;
      }
   }
   bool isCleared() const { return status_ == Status::cleared; }
   void proceed()
   {
      std::this_thread::sleep_for(std::chrono::seconds(rand() % 3 + 1)); // wait a while
      // cout << flightNo_
      //      << (task_ == Task::taxiing ? " took off" : " landed")
      //      << ". Have a good day!" << endl;
      // controller_->leave(this);

      cout << "..." << logo_->getName() << number_ << (task_ == Task::taxiing ? " took off..." : " lands...") << endl;
      controller_->leave(this);
   }

protected:
   Controller *controller_;
   enum class Task
   {
      taxiing,
      approaching
   };
   Task task_;
   enum class Status
   {
      waiting,
      cleared
   };
   Status status_;
   Logo *logo_; // shared
   // separeted logo into airline and number
   string airline_;
   string number_;
   string flightNo_;
};

// concrete colleagues
class Airbus : public Flight
{
public:
   Airbus(Tower *tower) : Flight(tower)
   {
      static const std::vector<string> companies =
          {"AirFrance", "KLM", "Aeroflot", "Lufthansa"};

      // flightNo_ = companies[rand() % companies.size()] +
      //     std::to_string(rand() % 1000);
      airline_ = companies[rand() % companies.size()];

      logo_ = LogoFactory::getLogo(airline_);
      number_ = std::to_string(rand() % 1000); // serparretted with number
      auto flightNo = airline_ + number_;
      cout << flightNo << " requesting "
           << (task_ == Task::taxiing ? "takeoff" : "landing") << endl;
   }
};

class Boeing : public Flight
{
public:
   Boeing(Tower *tower) : Flight(tower)
   {
      static const std::vector<string> companies =
          {"Delta", "Alaskan", "Spirit"};
      // airline_ = companies[rand() % companies.size()] +
      //            std::to_string(rand() % 1000);

      airline_ = companies[rand() % companies.size()];
      logo_ = LogoFactory::getLogo(airline_); // gets flywright logo
      number_ = std::to_string(rand() % 1000);
      auto flightNo = airline_ + number_;
      cout << flightNo << " requesting "
           << (task_ == Task::taxiing ? "takeoff" : "landing") << endl;
   }
};

// member functions for Tower
void Tower::broadcast()
{
   cout << "Tower: ";
   string msg;
   getline(cin, msg);
   if (!msg.empty())
      for (auto f : waiting_)
         f->receive(msg);
}

void Tower::observe()
{
   auto findCleared = [](Flight *f)
   { return f->isCleared(); };

   auto toProceed = std::find_if(waiting_.begin(), waiting_.end(), findCleared);

   while (toProceed != waiting_.end())
   { // found a cleared flight
      (*toProceed)->proceed();
      toProceed = std::find_if(waiting_.begin(), waiting_.end(), findCleared);
      if (toProceed != waiting_.end())
         // more than a single flight cleared
         cout << "MAYDAY! MAYDAY! MAYDAY! " << endl;
   }
}

void Tower::join(Flight *f)
{
   waiting_.insert(f);
}

void Tower::leave(Flight *f)
{
   waiting_.erase(f);
   delete f;
}

int main()
{
   srand(time(nullptr));
   Tower jfk;

   new Boeing(&jfk);
   new Airbus(&jfk);
   new Boeing(&jfk);
   new Airbus(&jfk);

   while (true)
   {
      jfk.broadcast();
      jfk.observe();
      if (rand() % 2)
      {
         if (rand() % 2)
            new Boeing(&jfk);
         else
            new Airbus(&jfk);
      }
   }
}
