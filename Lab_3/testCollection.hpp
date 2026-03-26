#ifndef TESTCOLLECTION_HPP
#define TESTCOLLECTION_HPP

#include <iostream>
#include "list.hpp"
using std::cin;
using std::cout;
using std::endl;

// specific template
// forward class defination
template <typename T>
class Collection;

// forward function defination
template <typename T>
bool equal(const Collection<T> &, const Collection<T> &);

template <typename T>
class Collection
{

public:
    Collection();                                                       // constructor
    ~Collection();                                                      // deconstructtor
    Collection(const Collection &);                                     // copy constructor
    Collection &operator=(const Collection &);                          // overload assignment
    void add(const T &);                                                // add function
    void remove(const T &);                                             // remove function
    T last() const;                                                     // get last function
    void print();                                                       // print function
    friend bool equal<T>(const Collection<T> &, const Collection<T> &); // friend equal function

private:
    node<T> *head;
};

template <typename T>
Collection<T>::Collection() // constructor
{
    head = nullptr;
}

template <typename T>
Collection<T>::~Collection() // deconstructor
{
    while (head != nullptr)
    {
        node<T> *temp = head;
        head = head->getNext();
        delete temp;
    }
}

template <typename T>
Collection<T>::Collection(const Collection<T> &rhs) // copy constructoor
{
    head = nullptr;
    node<T> *temp = rhs.head;
    while (temp != nullptr)
    {
        add(temp->getData());
        temp = temp->getNext();
    }
}

template <typename T>
Collection<T> &Collection<T>::operator=(const Collection<T> &rhs) // assignment overload
{
    if (this != &rhs)
    {
        // deleteing the already existing
        while (head != nullptr)
        {
            node<T> *temp = head;
            head = head->getNext();
            delete temp;
        }
        // deep coopy
        node<T> *newNode = rhs.head;
        while (newNode != nullptr)
        {
            add(newNode->getData());
            newNode = newNode->getNext();
        }
    }
    return *this;
}

template <typename T>
void Collection<T>::add(const T &value) // add function
{
    node<T> *newNode = new node<T>; // created node dynamically
    newNode->setData(value);        // stored the data
    newNode->setNext(head);         // set the head
    head = newNode;                 // making the head point to the new node
}

template <typename T>
void Collection<T>::remove(const T &value)
{
    if (head == nullptr)
    {
        return;
    }
    // remove for beginning
    while (head != nullptr && head->getData() == value)
    {
        node<T> *temp = head;
        head = head->getNext();
        delete temp;
    }

    // remove from middle or end
    node<T> *current = head;

    while (current != nullptr && current->getNext() != nullptr)
    {
        node<T> *newNode = head->getNext(); // this is to stor next node
        if (newNode->getData() == value)
        {
            node<T> *temp = current->getNext();
            current->setNext(temp->getNext());
            delete temp;
        }
        else
        {
            current = current->getNext();
        }
    }
}

template <typename T>
T Collection<T>::last() const
{

    return head->getData();
}

template <typename T>
void Collection<T>::print()
{
    if (head == nullptr)
    {
        cout << "list is empty";
        return;
    }
    node<T> *newNode = head;
    while (newNode != nullptr)
    {
        cout << newNode->getData() << " | ";
        newNode = newNode->getNext();
    }
    cout << endl;
}

template <typename T>
bool equal(const Collection<T> &lhs, const Collection<T> &rhs)
{
    node<T> *first = lhs.head;
    node<T> *second = rhs.head;

    while (first != nullptr && second != nullptr)
    {
        if (first->getData() != second->getData())
        {
            return false;
        }
        first = first->getNext();
        second = second->getNext();
    }

    return first == nullptr && second == nullptr;
}

#endif