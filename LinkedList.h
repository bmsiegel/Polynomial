#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "Node.hpp"
#include "ListInterface.h"

template<typename T>
class LinkedList : public ListInterface<T>
{
private:
  Node<T>* head;
  int count;
public:
  LinkedList(const LinkedList<T> &L);
  LinkedList& operator=(LinkedList L);
  bool isEmpty() const;
  int getLength() const;
  bool insert(int newPosition, const T &newEntry);
  bool remove(int position);
  void clear();
  T getEntry(int position) const;
  T replace(int loc, const T &newEntry);
  void swap(LinkedList<T> &lhs, LinkedList<T> &rhs)
};

#endif
