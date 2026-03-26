// jamming peaches
// non STL-algorithm code to be replaced by algorthms
// Mikhail Nesterenko
// 10/7/2025

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <deque>
#include <string>
#include <numeric>

using std::cin;
using std::cout;
using std::deque;
using std::endl;
using std::string;
using std::vector;
using namespace std::placeholders;

struct Peaches
{
   double weight; // oz
   bool ripe;     // ripe or not
   void print() const { cout << (ripe ? "ripe" : "green") << ", " << weight << endl; }
};

int main()
{
   srand(time(nullptr));
   const double minWeight = 3.;
   const double maxWeight = 8.;

   cout << "Input basket size: ";
   int size;
   cin >> size;

   vector<Peaches> basket(size);

   // assign random weight and ripeness peaches in the basket
   // replace with generate()
   // for (auto it = basket.begin(); it != basket.end(); ++it)
   // {
   //    it->weight = minWeight +
   //                 static_cast<double>(rand()) / RAND_MAX * (maxWeight - minWeight);
   //    it->ripe = rand() % 2;
   // }

   std::generate(basket.begin(), basket.end(), [=]
                 {
                    Peaches peach;
                    peach.weight = minWeight + static_cast<double>(rand()) / RAND_MAX * (maxWeight - minWeight);
                    peach.ripe = rand() % 2;
                    return peach; });

   // for_each() possibly
   cout << "all peaches" << endl;
   // for (const auto &e : basket)
   // {
   //    e.print();
   // }

   std::for_each(basket.begin(), basket.end(), [](const Peaches &peach)
                 { peach.print(); });

   // moving all the ripe peaches from basket to peck
   // remove_copy_if() with back_inserter()/front_inserter() or equivalents
   // remove()/erase() on the original algorithm
   deque<Peaches> peck;
   // for (auto it = basket.begin(); it != basket.end();)
   //    if (it->ripe)
   //    {
   //       peck.push_front(std::move(*it));
   //       it = basket.erase(it);
   //    }
   //    else
   //       ++it;

   std::remove_copy_if(basket.begin(), basket.end(), std::front_inserter(peck), [](const Peaches &peach)
                       { return !peach.ripe; }); // skip non ripe !peach.ripe
   basket.erase(std::remove_if(basket.begin(), basket.end(), [](const Peaches &peach)
                               { return peach.ripe; }),
                basket.end());

   // for_each() possibly
   cout
       << "peaches remainng in the basket" << endl;
   // for (const auto &e : basket)
   // {
   //    e.print();
   // }
   std::for_each(basket.begin(), basket.end(), [](const Peaches &peach)
                 { peach.print(); });

   cout << endl;

   // for_each() possibly
   cout << "peaches moved to the peck" << endl;
   // for (const auto &e : peck)
   // {
   //    e.print();
   // }
   std::for_each(peck.begin(), peck.end(), [](const Peaches &peach)
                 { peach.print(); });

   // prints every "space" peach in the peck
   const int space = 3;
   cout << "\nevery " << space << "\'d peach in the peck" << endl;

   // replace with advance()/next()/distance()
   // no explicit iterator arithmetic
   // auto it = peck.cbegin();
   // int i = 1;
   // while (it != peck.cend())
   // {
   //    if (i == space)
   //    {
   //       it->print();
   //       i = 0;
   //    }
   //    ++i;
   //    ++it;
   // }

   auto it = peck.cbegin();
   if (std::distance(it, peck.cend()) >= space)
   {
      std::advance(it, space - 1);
      while (it != peck.end())
      {
         it->print();
         if (std::distance(it, peck.cend()) >= space)
         {
            std::advance(it, space);
         }
         else
            break;
      }
   }

   // putting all small ripe peaches in a jam
   // use a binder to create a functor with configurable max weight
   // accumulate() or count_if() then remove_if()
   const double weightToJam = 10.0;
   double jamWeight = 0;
   // for (auto it = peck.begin(); it != peck.end();)
   //    if (it->weight < weightToJam)
   //    {
   //       jamWeight += it->weight;
   //       it = peck.erase(it);
   //    }
   //    else
   //       ++it;

   auto smallPeach = std::bind(std::less<double>(), _1, weightToJam);
   jamWeight = std::accumulate(peck.begin(), peck.end(), 0, [=](double sum, const Peaches &peach)
                               {
      if(peach.weight < weightToJam)
      {
         return sum += peach.weight;
      }
      else return sum += 0; });

   cout
       << "Weight of jam is: " << jamWeight << endl;
}
