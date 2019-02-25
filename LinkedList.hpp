//  Created by Frank M. Carrano and Timothy M. Henry.
//  Copyright (c) 2017 Pearson Education, Hoboken, New Jersey.

/** ADT list: Link-based implementation.
    Listing 9-2.
    @file LinkedList.hpp */

#ifndef LINKED_LIST_
#define LINKED_LIST_

#include <utility> //for swap

#include "ListInterface.hpp"
#include "Node.hpp"
#include "PrecondViolatedExcept.h"

/**
 * This is a LinkedList class. It uses Nodes to store data.
 */
template<class T>
class LinkedList : public ListInterface<T>
{
private:
   Node<T>* head; // Pointer to first node in the chain;
                            // (contains the first entry in the list)
   int count;           // Current count of list items

   // Locates a specified node in this linked list.
   // @pre  position is the number of the desired node;
   //       position >= 1 and position <= itemCount.
   // @post  The node is found and a pointer to it is returned.
   // @param position  The number of the node to locate.
   // @return  A pointer to the node at the given position.
   Node<T>* getNodeAt(int position) const;

public:
   LinkedList();
   /**
    * This is the copy constructor. It make a copy of the parameter.  It is also used by the operator= in the copy-swap paradigm.
    * @param rhs - the LinkedList we are copying during construction
    */
   LinkedList(const LinkedList<T>& rhs);
   virtual ~LinkedList();
   /**
    * This is the assignment operator. It uses the copy-swap paradigm to create a copy of the parameter
    * @param rhs - the LinkedList we are assigning to this
    * @return a reference to the list that was copied into, a.k.a. *this
    */
   LinkedList& operator=( LinkedList rhs );

   bool isEmpty() const;
   int getLength() const;
   bool insert(int newPosition, const T& newEntry);
   bool remove(int position);
   void clear();

   /** @throw PrecondViolatedExcept if position < 1 or
                                       position > getLength(). */
   T getEntry(int position) const ;

   /** @throw PrecondViolatedExcept if position < 1 or
                                       position > getLength(). */
   T replace(int position, const T& newEntry);

  /**
   * This is the swap method. It will swap the internals of the two lists.  Notably it is used in the operator= to implement the copy swap paradigm.  It is also used
   * by other C++ paradigms.
   * @param lhs - the LinkedList on the left...Left Hand Side (lhs)
   * @param rhs - the LinkedList on the right...Right Hand Side (rhs)
   */
  void swap( LinkedList& lhs, LinkedList& rhs );
  void output() const;
}; // end LinkedList
#endif
//implement your class here or
//#include your txx or cpp file up to the header...
//not the other way around!
template<class T>
LinkedList<T>::LinkedList()
{
  head = nullptr;
  count = 0;
}
template<class T>
LinkedList<T>::LinkedList(const LinkedList<T>& rhs)
{
  count = rhs.count;
  if (rhs.head == nullptr)
  {
    head = nullptr;
  }
  else
  {
    head = new Node<T>(rhs.head->getData());
    Node<T>*rcurrent = rhs.head;
    Node<T>*current = head;
    int a = 1;
    while (rcurrent->getNext() != nullptr)
    {
      rcurrent = rcurrent->getNext();
      current->setNext(new Node<T> (rcurrent->getData()));
      current = current->getNext();
    }
  }
}
template<class T>
LinkedList<T>::~LinkedList()
{
  clear();
}
template<class T>
LinkedList<T>& LinkedList<T>::operator=( LinkedList rhs )
{
  swap(*this,rhs);
  return *this;
}
template<class T>
Node<T>* LinkedList<T>::getNodeAt(int position) const
{
  if (position < 1 || position > count)
  {
    throw PrecondViolatedExcept("Index out of Range\n");
  }
  else
  {
    int currentLoc = 1;
    Node<T>* current = head;
    while (currentLoc < position)
    {
      current = current->getNext();
      currentLoc++;
    }
    return current;
  }
}
template<class T>
bool LinkedList<T>::isEmpty() const
{
  return (count == 0);
}
template<class T>
int LinkedList<T>::getLength() const
{
  return count;
}
template<class T>
bool LinkedList<T>::insert(int newPosition, const T& newEntry)
{
  Node<T>* data = new Node<T>(newEntry);
  if (newPosition < 1 || newPosition > count + 1)
  {
    throw PrecondViolatedExcept("Index out of Range\n");
  }
  else if (head == nullptr)
  {
    head = data;
    count++;
  }
  else
  {
    int currentLoc = 1;
    Node<T>* current = head;
    while (currentLoc < newPosition - 1 && current->getNext() != nullptr)
    {
      current = current->getNext();
      currentLoc++;
    }
    if (newPosition == count + 1)
    {
      current->setNext(data);
    }
    else if(current == head)
    {
      data->setNext(current);
      head = data;
    }
    else
    {
      data->setNext(current->getNext());
      current->setNext(data);
    }
    count++;
  }
}
template<class T>
bool LinkedList<T>::remove(int position)
{
  if (position < 1 || position > count)
  {
    throw PrecondViolatedExcept("Index out of Range\n");
  }
  else if (position == 1)
  {
    Node<T>* temp = head;
    head = head->getNext();
    delete temp;
    temp = nullptr;
    count--;
    return true;
  }
  else
  {
    Node<T>* rm = getNodeAt(position);
    getNodeAt(position - 1)->setNext(rm->getNext());
    delete rm;
    rm = nullptr;
    count--;
    return true;
  }
}
template<class T>
void LinkedList<T>::clear()
{
  Node<T>* temp = head;
  while (temp != nullptr)
  {
    head = temp->getNext();
    delete temp;
    temp = head;
  }
  count = 0;
}
template<class T>
T LinkedList<T>::getEntry(int position) const
{
  return getNodeAt(position)->getData();
}
template<class T>
T LinkedList<T>::replace(int position, const T& newEntry)
{
  T returnData = getNodeAt(position)->getData();
  getNodeAt(position)->setData(newEntry);
  return returnData;
}
template<class T>
void LinkedList<T>::output() const
{
  Node<T>* current = head;
  while (current != nullptr)
  {
    std::cout << current->getData() << '\n';
    current = current->getNext();
  }
}
template<class T>
void LinkedList<T>::swap( LinkedList& lhs, LinkedList& rhs )
{
  std::swap(lhs.count,rhs.count);
  std::swap(lhs.head, rhs.head);
}
