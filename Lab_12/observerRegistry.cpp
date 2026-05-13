// observer pattern using a signup registry
// Mikhail Nesterenko
// 4/22/2014

#include <set>
#include <map>
#include <iostream>
#include <string>
#include <algorithm>

using std::cout;
using std::endl;
using std::map;
using std::set;
using std::string;

class Observer;
class Subject;

class EventRegistry
{
public:
   static void registerObserver(const string &, Observer *);   //
   static void deregisterObserver(const string &, Observer *); //
   static void handleMessage(Subject *);

private:
   static map<string, set<Observer *>> observerMap_;
};

// initialize the static map
map<string, set<Observer *>> EventRegistry::observerMap_; // modified form subject* tto string

class Observer
{
public:
   Observer(const string &name) : name_(name) {}
   string getName() const { return name_; }
   void subscribe(const string &s) { EventRegistry::registerObserver(s, this); }
   void unsubscribe(const string &s) { EventRegistry::deregisterObserver(s, this); }
   void handleMessage(Subject *);

private:
   string name_;
};

class Subject
{
public:
   Subject(const string &name) : name_(name) {}
   string getName() const { return name_; }
   void generateMessage()
   {
      cout << name_ << " sent a message" << endl;
      EventRegistry::handleMessage(this);
   }

private:
   string name_;
};

void EventRegistry::registerObserver(const string &s, Observer *o)
{
   observerMap_[s].insert(o);
   cout << o->getName() << " subscribed to " << s << endl; // removed s-> getname
}

void EventRegistry::deregisterObserver(const string &s, Observer *o)
{
   observerMap_[s].erase(o);
   cout << o->getName() << " unsubscribed from " << s << endl; //  removed s-> getname
}

void EventRegistry::handleMessage(Subject *s)
{
   string name = s->getName();
   for (auto e : observerMap_[name])
      e->handleMessage(s);
}

void Observer::handleMessage(Subject *s)
{
   cout << name_ << " received message from " << s->getName() << endl;
}

int main()
{
   Subject sue("Subject Sue"), steve("Subject Steve");
   Observer oswald("Observer Oswald"), olga("Observer Olga");

   oswald.subscribe("Subject Sue");
   oswald.subscribe("Subject Steve");
   olga.subscribe("Subject Sue");

   cout << endl;
   sue.generateMessage();
   steve.generateMessage();
   cout << endl;

   olga.unsubscribe("Subject Sue");
   sue.generateMessage();
}
