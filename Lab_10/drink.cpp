#include "drink.hpp"
#include <iostream>
#include <vector>
using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;
#include <cstdlib>
#include <ctime>

int main()
{
    srand(time(nullptr));
    // chain of resp.
    Manager *manager = new Manager();
    SeniorBarista *senior = new SeniorBarista(manager);
    JuniorrBarista *junior = new JuniorrBarista(senior);

    vector<Customer *> customers;

    for (int i = 0; i < 5; ++i)
    {

        char size;
        cout << "Welcome to Coffee Shack, can I get you [l]arge, [m]edium, or [s]mall coffee? ";
        cin >> size;

        Drink *drink;
        if (size == 's')
            drink = new Drink(DrinkType::small);
        else if (size == 'm')
            drink = new Drink(DrinkType::medium);
        else
            drink = new Drink(DrinkType::large);

        char choice;
        while (true)
        {

            cout << "Would you like to add [s]ugar, [c]ream, [h]oney, or [d]one? ";
            cin >> choice;

            drink = junior->handleCoffee(choice, drink);
            if (choice == 'd')
            {
                break;
            }
        }
        // decide who prepared the drink
        string nameStr = drink->getName();

        if (nameStr.find("honey") != string::npos)
        {
            drink->prepare("Manager");
        }
        else if (nameStr.find("cream") != string::npos ||
                 nameStr.find("sugar") != string::npos)
        {
            drink->prepare("SeniorBarista");
        }
        else
        {
            drink->prepare("JuniorBarista");
        }

        string name;
        cout << "Can I get your name, Please? ";
        cin >> name;
        Customer *customer = new Customer(name, drink);
        customers.push_back(customer);
        junior->registerCustomer(customer);

        cout << "Please wait, " << name << "." << endl;
        cout << endl;

        // random notify
        if (rand() % 2 == 0)
        {
            int index = rand() % customers.size();
            Drink *readyDrink = customers[index]->getDrink();

            junior->notifyEveryone(readyDrink);
        }
    }

    // notify remaining
    for (auto c : customers)
    {
        junior->notifyEveryone(c->getDrink());
    }

    return 0;
}